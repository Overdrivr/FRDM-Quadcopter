/*
 * distantio.h
 *
 *  Created on: Oct 13, 2014
 *      Author: B48923
 */

#ifndef DISTANTIO_H_
#define DISTANTIO_H_

#include "mqx_tasks.h"

typedef enum dio_type dio_type;
enum dio_type
{
	dio_type_FLOAT = 0x00,
	dio_type_UINT8 = 0x01,
	dio_type_UINT16 = 0x02,
	dio_type_UINT32 = 0x03,
	dio_type_INT8 = 0x04,
	dio_type_INT16 = 0x05,
	dio_type_INT32 = 0x06,
};

typedef struct variable variable;
struct variable
{
	uint8_t* ptr;
	uint16_t size;
	bool writeable;
	uint16_t id;
	dio_type type;
	char name[32];
	uint8_t send;
	uint8_t groupID;
};

typedef struct log log;
struct log
{
	variable variables[32];
	uint16_t amount;
};


void init_distantio();

uint8_t register_var(void* ptr, uint16_t size, dio_type type, bool writeable, char* name);
void start_group(char* groupname);
void stop_group();

void send_variable(uint16_t i);
void send_variables();
void send_descriptor(uint16_t index);

void distantio_decode(uint8 InputBuffer[],uint16_t size);

uint16_t get_size(dio_type type);


#endif /* DISTANTIO_H_ */
