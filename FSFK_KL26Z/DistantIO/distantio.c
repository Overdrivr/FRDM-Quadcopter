/*
 * distantio.c
 *
 *  Created on: Oct 13, 2014
 *      Author: B48923
 */

#include "distantio.h"
#include "Cpu.h"

log Log;
uint32_t tmp;
uint8_t current_group_id;


uint32_t distantio_encode_variable(uint16_t i);

/**
 * Inits the distant io framework
 */
void init_distantio()
{
	uint16_t i;
	char default_name[] = {"undefined"};
	Log.amount = 0;
	for(i = 0 ; i < 128 ; i++)
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
}

/**
 * Register a variable exchanged with the computer
 */
uint8_t register_var(void* ptr, uint16_t size, dio_type type, bool writeable, char* name)
{
	uint16_t octets = 0;

	// Too many variables, aborting
	if(Log.amount >= 31)
		return 1;

	//Limited to 1024 octets per variable, should be enough for now
	if(octets > 1024)
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

	uint32_t i;
	uint8_t *temp_ptr;
	uint8_t type;
	uint8_t buffer[64] = {0};

	//Return table command
	buffer[i++] = 0x02;

	type = (uint8_t)(Log.variables[i].type);

	if(Log.variables[i].writeable == 1)
		type += 0xF0;

	buffer[i++] = type;

	//Data id
	temp_ptr = (uint8_t*)(&i);
	buffer[i++] = *temp_ptr;
	buffer[i++] = *(temp_ptr+1);

	temp_ptr = (uint8_t*)(&(Log.variables[i].size));
	buffer[i++] = *temp_ptr;
	buffer[i++] = *(temp_ptr+1);

	//Write name
	uint32_t k = 0;

	for(k = 0 ; k < 32 ; k++)
	{
		if(k < strlen(Log.variables[i].name))
			buffer[i++] = Log.variables[i].name[k];
		else
			buffer[i++] = 0;
	}

	// Send frame
	encode(buffer,i-1);
}

void distantio_decode(uint8 InputBuffer[],uint16_t size)
{
	uint8_t byte1,byte2;
	uint16_t id;

	void* ptr;
	
	float* tmp_float;
	uint32_t* tmp_uint32;
	
	float* to_float;
	int32_t* to_int;
	
	uint8_t bytes[4];
	
	uint16_t i = 1;
	//If command is send a variable
	if(InputBuffer[0] == 0x00 && size >= (2+1))
	{
		byte1 = InputBuffer[i++];
		byte2 = InputBuffer[i++];
		
		id = byte1 + (byte2<<8);
		
		if(id < Log.amount)
		{
			Log.variables[id].send = 1;
		}
	}
	//If command is write variable value
	else if(InputBuffer[0] == 0x01)
	{
		byte1 = InputBuffer[i++];
		byte2 = InputBuffer[i++];
		
		id = byte1 + (byte2<<8);
		
		if(id < Log.amount)
		{
			if(Log.variables[id].writeable && size >= (4+3))
			{
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
				}
			}
		}
	}
	//If command is return table to master
	else if(InputBuffer[0] == 0x02)
	{
		for(uint16_t i = 0 ; i < Log.amount ; i++)
		{
			distantio_send_descriptor(i);
		}
	}
	//If command is stop sending variable
	else if(InputBuffer[0] == 0x03 && size >= (2+1))
	{
		byte1 = InputBuffer[i++];
		byte2 = InputBuffer[i++];
		
		id = byte1 + (byte2<<8);
		
		if(id < Log.amount)
		{
			Log.variables[id].send = 0;
		}
	}
	//If command is stop sending all variables
	else if(InputBuffer[0])
	{
		for(id = 0 ; id < Log.amount ; id++)
		{
			Log.variables[id].send = 0;
		}
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

		distantio_encode_variable(i);
	}
}


void send_variable(uint16_t i)
{
	uint16_t j,k;
	uint8_t *temp_ptr;
	uint8_t buffer[64];
	j = 0;
	
	//Write command
	buffer[j++] = 0x00;
	
	//Write variable ID
	temp_ptr = (uint8_t*)(&i);
	
	buffer[j++] = *temp_ptr;
	buffer[j++] = *(temp_ptr+1);
	
	//Write time
	temp_ptr = (uint8_t*)(&tmp);
		
	buffer[j++] = *temp_ptr;
	buffer[j++] = *(temp_ptr+1);
	buffer[j++] = *(temp_ptr+2);
	buffer[j++] = *(temp_ptr+3);

	//Write data
	for(k = 0 ; k < Log.variables[i].size ; k++)
	{
		temp_ptr = Log.variables[i].ptr + k;
		
		buffer[j++] = *temp_ptr;
	}
	
	// Send frame
	encode(buffer,i-1);
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
