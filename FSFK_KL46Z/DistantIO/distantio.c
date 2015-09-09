/*
 * distantio.c
 *
 *  Created on: Oct 13, 2014
 *      Author: B48923
 */

#include "distantio.h"
#include "Cpu.h"
#include "crc.h"
#include "string.h"
#include "../SerialProtocol/functions.h"
#include "../SerialProtocol/protocol.h"

/*
 * WARNING : IMPLEMENTATION FOR LITTLE-ENDIAN PROCESSOR
 * TODO : HANDLE BOTH
 */

log Log;
uint32_t tmp;
uint8_t current_group_id;

void send_variable(uint16_t index);
uint16_t get_size(dio_type type);
void send_data_callback(uint8_t* data, uint16_t size);
void send_descriptor(uint16_t index);

/**
 * Inits the distant io framework
 */
void init_distantio(LDD_TDeviceData *uart_device)
{
	uint16_t i;
	char default_name[] = {"undef.  "};
	Log.amount = 0;
	for(i = 0 ; i < VARIABLES_AMOUNT ; i++)
	{
		Log.variables[i].size = 0;
		Log.variables[i].ptr = 0;
		Log.variables[i].writeable = 0;
		Log.variables[i].id = i;
		strcpy(Log.variables[i].name,default_name);
		Log.variables[i].send = 0;
	}
	tmp=0;
	current_group_id = 0;
	Log.handle = uart_device;
}

/**
 * Register a variable exchanged with the computer
 */
uint8_t register_var(void* ptr, uint16_t size, dio_type type, bool writeable, char* name)
{
	// Too many variables, aborting
	if(Log.amount >= VARIABLES_AMOUNT)
		return 1;

	Log.variables[Log.amount].ptr = ptr;
	Log.variables[Log.amount].size = get_size(type);
	Log.variables[Log.amount].writeable = writeable;
	Log.variables[Log.amount].type = type;
	Log.variables[Log.amount].groupID = current_group_id;
	strcpy(Log.variables[Log.amount].name,name);

	Log.amount++;

	return 0;
}

void start_group(char* groupname)
{

}
void stop_group()
{

}
/**
 * Send descriptor
 */

void send_descriptor(uint16_t index)
{
	if(index >= Log.amount)
		return;

	static uint8_t buffer[PAYLOAD_SIZE];
	uint8_t *temp_ptr;
	uint8_t type;

	// Respond returned-descriptor
	buffer[0] = 0x00;

	// Write id
	temp_ptr = (uint8_t*)(&index);
	buffer[1] = *(temp_ptr    );
	buffer[2] = *(temp_ptr + 1);

	// Write type & writeable

	type = (uint8_t)(Log.variables[index].type);

	if(Log.variables[index].writeable)
		type += 0xF0;

	buffer[3] = type;

	//Write name
	uint16_t i = 4;
	for(uint16_t k = 0 ; k < 8 ; k++)
	{
		if(k < strlen(Log.variables[index].name))
		{
			buffer[i] = Log.variables[index].name[k];
			i++;
		}
		else
			buffer[i++] = 0;
	}

	// Compute crc
	uint16_t crc_value = crc16(buffer,i);

	// Write crc into buffer's last byte
	buffer[i++] = (crc_value >> 8) & 0xFF;
	buffer[i++] = crc_value & 0xFF;

	// Encode frame
	encode(buffer,i,send_data_callback);
}

void distantio_decode(uint8* data,uint16_t datasize)
{
	// First check data size
	// 1 byte cmd + 2 bytes id + 1 byte type + FRAME_SIZE + 2 byte CRC
	if(datasize != PAYLOAD_SIZE)
		return;

	// Second, check CRC
	uint16_t crc_value = crc16(data,PAYLOAD_SIZE-2);
	uint16_t crc_rx = ((uint16_t)data[PAYLOAD_SIZE-2] << 8) | data[PAYLOAD_SIZE-1];

	if(crc_value != crc_rx)
		return;
	
	// Process frame
	// First, identify command
	uint8_t command = data[0];
	
	// Second, identify ID
	uint8_t a = data[2];
	uint16_t ID = data[1] + (a << 8);
	
	// Third, identify data type
	uint8_t type = data[3];
	uint16_t amount = Log.amount;

	switch(command)
	{
		// User requested descriptors
		case 0x02:
			for(uint16_t i = 0 ; i < Log.amount ; i++)
				send_descriptor(i);
			break;

		// User provided value to write
		case 0x04:
			if(ID >= Log.amount)
				return;

			if(Log.variables[ID].writeable == FALSE)
				return;

			if(Log.variables[ID].type != type)
				return;

			uint16_t start_address = 4 + DATA_SIZE - 1;

			// Copy contents directly into variable
			for(uint16_t i = 0 ; i < Log.variables[ID].size ; i++)
			{
				// Packet is big-endian, convert to little-endian
				uint8_t offset = start_address - i;
				*(Log.variables[ID].ptr + i) = *(data + offset);
			}
			break;

		// User requested variable read
		case 0x05:
			if(ID >= Log.amount)
				return;

			Log.variables[ID].send = 1;
			break;

		// User requested stop variable read
		case 0x06:
			if(ID >= Log.amount)
				return;
			Log.variables[ID].send = 0;
			break;
		
	}
}

void send_variables()
{
	for(uint16_t i = 0 ; i < Log.amount ; i++)
	{
		if(Log.variables[i].send == 0)
			continue;

		send_variable(i);
	}
}


void send_variable(uint16_t index)
{
	if(index >= Log.amount)
		return;

	static uint8_t buffer[PAYLOAD_SIZE];

	// Response code 0x01
	buffer[0] = 0x01;
	
	// Write variable ID
	uint8_t* temp_ptr = (uint8_t*)(&index);
	
	buffer[1] = *(temp_ptr  );
	buffer[2] = *(temp_ptr+1);
	
	// Write variable type
	buffer[3] = Log.variables[index].type;
	//TODO writeable

	uint16_t i = 4;

	// Write data
	for(uint16_t k = 0 ; k < DATA_SIZE ; k++)
	{
		uint16_t off = DATA_SIZE - 1 - k;

		// Fill buffer with data
		if(off < Log.variables[index].size)
		{
			temp_ptr = Log.variables[index].ptr + off ;
			buffer[i++] = *temp_ptr;
		}
		// Fill remaining bits with 0
		else
		{
			buffer[i++] = 0;
		}
	}
	
	// Compute crc
	uint16_t crc_value = crc16(buffer,i);

	// Write crc into buffer's last byte
	buffer[i++] = (crc_value >> 8) & 0xFF;
	buffer[i++] = crc_value & 0xFF;

	// Encode frame
	encode(buffer,i,send_data_callback);
}

void send_alive()
{
	static uint8_t buffer[PAYLOAD_SIZE] = {0x03,0x00,0x00,0x00,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x00,0x00};


	// Compute crc
	uint16_t crc_value = crc16(buffer,PAYLOAD_SIZE - 2);

	// Write crc into buffer's last byte
	buffer[PAYLOAD_SIZE - 1] = crc_value & 0xFF;
	buffer[PAYLOAD_SIZE - 2] = (crc_value >> 8) & 0xFF;

	// Send frame to encoding
	encode(buffer,PAYLOAD_SIZE,send_data_callback);
}


/**
 * Returns the size in byte for each variable
 */

uint16_t get_size(dio_type type)
{
	switch(type)
	{
		case dio_type_FLOAT:
		case dio_type_UINT32:
		case dio_type_INT32:
			return 4;

		case dio_type_UINT16:
		case dio_type_INT16:
			return 2;

		case dio_type_UINT8:
		case dio_type_INT8:
		default:
			return 1;
	}
}

void send_data_callback(uint8_t* data, uint16_t size)
{
	// Send encoded frame
	sendBytes(Log.handle,data,size);
}
