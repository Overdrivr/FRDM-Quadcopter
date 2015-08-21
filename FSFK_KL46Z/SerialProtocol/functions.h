/*
 * functions.h
 *
 *  Created on: Aug 14, 2015
 *      Author: B48923
 */

#ifndef SOURCES_FUNCTIONS_H_
#define SOURCES_FUNCTIONS_H_

#include "PE_Types.h"

typedef struct {
    LDD_TDeviceData *handle; /* LDD device handle */
    uint8_t rxChar; /* single character buffer for receiving chars */
    uint8_t (*rxCallback)(uint8_t); /* callback to put received character into buffer */
  } UART_Desc;


void sendByte(LDD_TDeviceData *handle, uint8_t* ch);
void sendBytes(LDD_TDeviceData *handle, unsigned char* data, uint16_t size);

#endif /* SOURCES_FUNCTIONS_H_ */
