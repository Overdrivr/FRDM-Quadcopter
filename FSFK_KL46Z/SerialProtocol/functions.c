/*
 * functions.c
 *
 *  Created on: Aug 14, 2015
 *      Author: B48923
 */

#include "functions.h"
#include "UART.h"

void sendByte(LDD_TDeviceData *handle, uint8_t* ch)
{
	UART_SendBlock(handle, ch, 1);
	while(! UART_GetTxCompleteStatus(handle));
}

void sendBytes(LDD_TDeviceData *handle, uint8_t* data, uint16_t size)
{
	UART_SendBlock(handle, data, size);
	while(! UART_GetTxCompleteStatus(handle));
}
