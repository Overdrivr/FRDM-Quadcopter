/*
 * serial_protocol.c
 *
 *  Created on: Oct 22, 2014
 *      Author: B48923
 */

#include "protocol.h"

enum state
{
	IDLE,
	IN_PROCESS
};
typedef enum state state;


enum ESC_state
{
	NONE,
	NEXT
};
typedef enum ESC_state ESC_state;

uint8_t OutputBuffer[OUTPUT_BUFFER_SIZE];
uint8_t InputBuffer[INPUT_BUFFER_SIZE];
uint16_t inIndex;


//Protocol state:
state protocol_state;

//In case ESC character is received
ESC_state escape_state;

uint8_t SOF_;
uint8_t EOF_;
uint8_t ESC_;


void init_protocol()
{
	protocol_state = IDLE;
	escape_state = NONE;
	
	SOF_ = 0xF7;
	EOF_ = 0x7F;
	ESC_ = 0x7D;

	inIndex = 0;
}

void encode(uint8_t* framedata, uint16_t framesize)
{
	uint16_t i,index;
	index = 0;
	
	//Write start of frame byte
	OutputBuffer[index++] = SOF_;
	
	//Write data
	for(i = 0 ; i < framesize ; i++)
	{
		//See serial_protocols_definition.xlsx
		if(*(framedata + i) == SOF_ ||
		   *(framedata + i) == EOF_ ||
		   *(framedata + i) == ESC_)
		{
			//If data contains one of the flags, we escape it before
			OutputBuffer[index++] = ESC_;
			
		}
		OutputBuffer[index++] = framedata[i];
	}
	
	//Set EOFrame
	OutputBuffer[index++] = EOF_;

	// Send data
	UART_SendBlock(UART_DeviceData, OutputBuffer, index);
}

bool decode(uint8_t received_byte)
{
		//If a reception was in process
		if(protocol_state == IN_PROCESS)
		{
			//If the character was previously marked as pure data
			if(escape_state == NEXT)
			{
				InputBuffer[inIndex++] = received_byte;
				escape_state = NONE;
			}
			else
			{
				if(received_byte == EOF_)
				{
					protocol_state = IDLE;
					return true;
					
				}
				else if(received_byte == ESC_)
				{
					escape_state = NEXT;
				}
				else
				{
					InputBuffer[inIndex++] = received_byte;
				}
			}
		}
		else
		{
			if(received_byte == SOF_)
			{
				protocol_state = IN_PROCESS;
			}
			else
			{
				//Ignore character
			}
		}
	return false;
}


