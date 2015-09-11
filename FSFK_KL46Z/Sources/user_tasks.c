// Copyright (c) 2014, Freescale Semiconductor, Inc.
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Freescale Semiconductor, Inc. nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL FREESCALE SEMICONDUCTOR, INC. BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// If you want to take a simplistic approach of using the existing templates
// as your starting point, simply adding your code for startup, sampling task (eg. 200Hz)
// and fusion tasks (eg. 25Hz), then this is the file for you.  Just put your code
// where ever you see "PUT YOUR CODE HERE"
//
#include "Cpu.h"
#include "Events.h"
#include "mqx_tasks.h"
#include "UART.h"
#include "include_all.h"

#include "../SerialProtocol/functions.h"
#include "../SerialProtocol/protocol.h"
#include "../DistantIO/distantio.h"
#include "RNG1.h"
#include "string.h"

static UART_Desc deviceData;

void on_protocol_decoded_frame(uint8_t* data, uint16_t datasize);
void on_protocol_encoded_frame(uint8_t* data, uint16_t datasize);

static uint32_t counter;
static float counter_float;
static uint8 counter_uint8;

void UserStartup(void)
{
	// Init serial
	RNG1_Init();

	deviceData.handle = UART_Init(&deviceData);
	deviceData.rxChar = '\0';
	deviceData.rxCallback = RNG1_Put;

	// Configure receive function
	UART_ReceiveBlock(deviceData.handle, (LDD_TData *)&(deviceData.rxChar), sizeof(deviceData.rxChar));

	// Init serial protocol and distant io
	init_protocol(on_protocol_encoded_frame,on_protocol_decoded_frame);
	init_distantio();
	counter = 0;

	// Register variables
	register_var((void*)&counter, sizeof(counter), dio_type_UINT32, TRUE, "COUNTER");
	start_group("TYPETEST");
	register_var((void*)&counter_float, sizeof(counter_float), dio_type_FLOAT, TRUE, "FLOAT");
	register_var((void*)&counter_uint8, sizeof(counter_uint8), dio_type_UINT8, FALSE, "UINT8");

}

void UserHighFrequencyTaskInit(void)
{
	// User code to be executed ONE TIME the first time the high frequency task is run.
	//
	// PUT YOUR CODE HERE
	//
	return;
}

void UserMediumFrequencyTaskInit(void)
{
	// User code to be executed ONE TIME the first time the medium frequency task is run
	//
	// PUT YOUR CODE HERE
	//
	return;
}


void UserHighFrequencyTaskRun(void)
{
	// The default frequency at which this code runs is 200Hz.
	// This code runs after sensors are sampled.
	// In general, try to keep "high intensity" code out of UserHighFrequencyTaskRun.
	// The high frequency task also has highest priority.
	//
	// PUT YOUR CODE HERE
	//
	return;
}

void UserMediumFrequencyTaskRun(void)
{
	static uint32_t alive_counter = 0;
	static uint32_t send_variables_counter = 0;

	counter++;
	counter_float += 0.3f;

	// Send alive signal
	if(alive_counter >= 20)
	{
		send_alive();
		alive_counter = 0;
	}
	else
		alive_counter++;

	// Send variables
	if(send_variables_counter >= 5)
	{
		send_variables();
		send_variables_counter = 0;
	}
	else
		send_variables_counter++;


	// Process RX data
	if(RNG1_NofFreeElements() > 0)
	{
		while (RNG1_NofElements()!=0)
		{
		  unsigned char ch;
		  RNG1_Get(&ch);
		  decode(ch);
		}
	}
}

void on_protocol_decoded_frame(uint8_t* data, uint16_t datasize)
{
	distantio_decode(data,datasize);
}

void on_protocol_encoded_frame(uint8_t* data, uint16_t datasize)
{
	sendBytes(deviceData.handle,data,datasize);
}



