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

log Log;
uint32_t tmp;
uint8_t current_group_id;

void send_variable(uint16_t index);
void send_descriptor(uint16_t index);
uint16_t get_size(dio_type type);

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
	uint16_t octets = 0;

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
	if(index > Log.amount)
		return;

	static uint8_t buffer[FRAME_SIZE + 5];
	uint8_t *temp_ptr;
	uint8_t type;

	// Respond to send-descriptor 0x02
	buffer[0] = 0x02;

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
		if(k < strlen(Log.variables[i].name))
			buffer[i++] = Log.variables[i].name[k];
		else
			buffer[i++] = 0;
	}

	// Compute crc
	uint8_t crc_value = crc8(buffer,i);

	// Write crc into buffer's last byte
	buffer[i++] = crc_value;

	// Send frame
	sendBytes(Log.handle,buffer,i);
}

void distantio_decode(uint8* data,uint16_t datasize)
{
	// First check data size
	// 1 byte cmd + 2 bytes id + 1 byte type + FRAME_SIZE + 1 byte CRC
	if(datasize != FRAME_SIZE + 5)
		return;

	// Second, check CRC
	uint8_t crc_value = crc8(data,FRAME_SIZE);
	if(crc_value != data[FRAME_SIZE + 4])
		return;
	
	// Process frame
	// First, identify command
	uint8_t command = data[0];
	
	// Second, identify ID
	uint8_t a = data[2];
	uint16_t ID = data[1] + (a << 8);
	
	// Third, identify data type
	uint8_t type = data[3];

	switch(command)
	{
		// User requested variable read
		case 0:
			if(ID >= Log.amount)
				return;

			Log.variables[ID].send = 1;
			break;

		// User provided value to write
		case 1:
			if(ID >= Log.amount)
				return;

			if(!Log.variables[ID].writeable)
				return;

			if(Log.variables[ID].type != type)
				return;

			// Write 8 byte data
			// Write 4 byte data
			// Write 2 byte data
			// Write 1 byte data
			/*
			bytes[0] = InputBuffer[i++];
			bytes[1] = InputBuffer[i++];
			bytes[2] = InputBuffer[i++];
			bytes[3] = InputBuffer[i++];

			if(Log.variables[id].type == 0x00)
			{
				to_float = (float *)(&bytes[0]);

				ptr = (void *)(Log.variables[id].ptr);
				tmp_float = (float *)(ptr);

				*tmp_float = *to_float;
			}
			else if(Log.variables[id].type == 0x06)
			{
				//TODO : Use void ptr
				to_int = (int32_t*)(&bytes[0]);

				ptr = (void *)(Log.variables[id].ptr);
				tmp_uint32 = (uint32_t*)(ptr);

				*tmp_uint32 = *to_int;
			}*/
			break;
		
		// User requested all descriptors
		case 2:
			for(uint16_t i = 0 ; i < Log.amount ; i++)
			{
				send_descriptor(i);
			}
			break;

		// User requested stop variable read
		case 3:
			if(ID >= Log.amount)
				return;
			Log.variables[ID].send = 0;
			break;
		
		// User requested stop all variable read
		case 4:
			for(uint16_t i = 0 ; i < Log.amount ; i++)
			{
				Log.variables[i].send = 0;
			}
			break;
	}
}

void send_variables()
{
	uint16_t i;
	uint16_t interval = 1;

	//Send variables
	for(i = 0 ; i < Log.amount ; i++)
	{
		if(Log.variables[i].send == 0)
			continue;

		send_variable(i);
	}
}


void send_variable(uint16_t index)
{
	if(index > Log.amount)
		return;

	static uint8_t buffer[FRAME_SIZE + 5];

	// Responding to cmd 0x00
	buffer[0] = 0x00;
	
	// Write variable ID
	uint8_t* temp_ptr = (uint8_t*)(&index);
	
	buffer[1] = *(temp_ptr  );
	buffer[2] = *(temp_ptr+1);
	
	// Write variable type
	buffer[3] = Log.variables[index].type;

	uint16_t i = 4;

	// Write data
	for(uint16_t k = 0 ; k < FRAME_SIZE ; k++)
	{
		// Fill buffer with data
		if(k < Log.variables[index].size)
		{
			temp_ptr = Log.variables[index].ptr + k;
			buffer[i++] = *temp_ptr;
		}
		// Fill remaining bits with 0
		else
		{
			buffer[i++] = 0;
		}
	}
	
	// Compute crc
	uint8_t crc_value = crc8(buffer,i);

	// Write crc into buffer's last byte
	buffer[i++] = crc_value;

	// Send frame
	sendBytes(Log.handle,buffer,i);
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
