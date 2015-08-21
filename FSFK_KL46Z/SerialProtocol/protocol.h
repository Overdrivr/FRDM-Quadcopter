/*
 * serial_protocol.h
 *
 *  Created on: Oct 22, 2014
 *      Author: B48923
 */

#ifndef SERIAL_PROTOCOL_H_
#define SERIAL_PROTOCOL_H_

#include "mqx_tasks.h"

#define ENCODING_BUFFER_SIZE 64
#define DECODING_BUFFER_SIZE 256

void init_protocol();
/*
 * Encodes new data with byte stuffing algorithm to delimit frame.
 * @input framedata : the raw data to process
 * @input framesize : size of the raw data to process (amount of bytes)
 * @input callback : the callback function called when the encoding is complete
 */
void encode(uint8_t* framedata, uint16_t framesize, void (*callback)(uint8_t*,uint16_t));

/*
 * Append new byte to current decoding sequence. If a valid frame is detected,
 * the callback function is called and the valid frame is sent as parameter
 * @input received_byte : the new byte to add to the current decoding sequence
 * @input callback : the callback function called when a complete frame has been decoded
 */
void decode(uint8_t received_byte, void (*callback)(uint8_t*,uint16_t));

#endif /* SERIAL_PROTOCOL_H_ */
