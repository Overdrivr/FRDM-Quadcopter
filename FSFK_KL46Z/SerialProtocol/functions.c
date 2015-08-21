/*
 * functions.c
 *
 *  Created on: Aug 14, 2015
 *      Author: B48923
 */

#include "functions.h"
#include "AS1.h"

void sendByte(LDD_TDeviceData *handle, uint8_t* ch)
{
	AS1_SendBlock(handle, ch, sizeof(*ch));
	while(! AS1_GetTxCompleteStatus(handle));
}

void sendBytes(LDD_TDeviceData *handle, unsigned char* data, uint16_t size)
{
	AS1_SendBlock(handle, data, size);
	while(! AS1_GetTxCompleteStatus(handle));
}
