/*
 * serial_protocol.h
 *
 *  Created on: Oct 22, 2014
 *      Author: B48923
 */

#ifndef SERIAL_PROTOCOL_H_
#define SERIAL_PROTOCOL_H_

#include "mqx_tasks.h"

#define INPUT_BUFFER_SIZE 	32
#define OUTPUT_BUFFER_SIZE 256

extern uint8 OutputBuffer[OUTPUT_BUFFER_SIZE];
extern uint8 InputBuffer[INPUT_BUFFER_SIZE];

void init_protocol();
/*
 * Encodes framedata with framesize into output
 */
void encode(uint8_t* framedata, uint16_t framesize);
/*
 * Add the new data. Returns true if a valid frame was detected. Valid frame is then placed into output
 */
bool decode(uint8_t data);

#endif /* SERIAL_PROTOCOL_H_ */
