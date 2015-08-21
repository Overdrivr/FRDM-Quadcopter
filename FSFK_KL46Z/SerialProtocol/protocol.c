/*
 * serial_protocol.c
 *
 *  Created on: Oct 22, 2014
 *      Author: B48923
 */

#include "protocol.h"
#include "functions.h"

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

uint16_t decodingIndex;
state protocol_state;
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

	decodingIndex = 0;
}

void encode(uint8_t* framedata, uint16_t framesize, void (*callback)(uint8_t*,uint16_t))
{
	// If frame size is superior than maximum allowed, abort
	if(framesize > ENCODING_BUFFER_SIZE)
		return;

	// Actual buffer size is twice the data size (for worst case byte stuffing) + SOF + EOF
	static uint8_t encodingBuffer[ENCODING_BUFFER_SIZE * 2 + 2];

	uint16_t index = 0, i = 0;
	
	//Write start of frame / end of frame byte
	encodingBuffer[index++] = SOF_;
	
	//Write data
	for(i = 0 ; i < framesize ; i++)
	{
		//See serial_protocols_definition.xlsx
		if(*(framedata + i) == SOF_ ||
		   *(framedata + i) == EOF_ ||
		   *(framedata + i) == ESC_)
		{
			//If data contains one of the flags, we escape it before
			encodingBuffer[index++] = ESC_;
		}
		encodingBuffer[index++] = framedata[i];
	}
	
	encodingBuffer[index++] = EOF_;

	// Operation is done, call function callback
	callback(encodingBuffer,index);
}

void decode(uint8_t received_byte, void (*callback)(uint8_t*,uint16_t))
{
	static uint8_t decodingBuffer[DECODING_BUFFER_SIZE];

	// If a reception was in process
	if(protocol_state == IN_PROCESS)
	{
		// If the character was previously marked as pure data
		if(escape_state == NEXT)
		{
			// If max buffer size was reached, cancel reception to avoid overflowing buffer
			if(decodingIndex + 1 >= DECODING_BUFFER_SIZE)
			{
				decodingIndex = 0;
				protocol_state = IDLE;
				escape_state = NONE;
			}
			else
			{
				decodingBuffer[decodingIndex++] = received_byte;
				escape_state = NONE;
			}
		}
		else
		{
			// End of frame
			if(received_byte == EOF_)
			{
				protocol_state = IDLE;
				// Call the function callback for end of frame
				callback(decodingBuffer,decodingIndex);
			}
			else if(received_byte == ESC_)
			{
				escape_state = NEXT;
			}
			else
			{
				// If max buffer size was reached, cancel reception to avoid overflowing buffer
				if(decodingIndex + 1 >= DECODING_BUFFER_SIZE)
				{
					decodingIndex = 0;
					protocol_state = IDLE;
					escape_state = NONE;
				}
				else
				{
					decodingBuffer[decodingIndex++] = received_byte;
					escape_state = NONE;
				}
			}
		}
	}
	else
	{
		if(received_byte == SOF_)
		{
			protocol_state = IN_PROCESS;
			decodingIndex = 0;
			escape_state = NONE;
		}
		else
		{
			//Received character outside a valid frame, ignore it
		}
	}
}


