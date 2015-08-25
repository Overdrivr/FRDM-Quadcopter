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
// This is a Processor-Expert generated file which is then updated with custom
// code on an application-specific basic.  It contains various functions invoked
// from hardware interrupt handlers.  This also includes the UART input command
// interpreter.
//
#include "Cpu.h"
#include "Events.h"
#include "mqx_tasks.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "include_all.h"
#include "../SerialProtocol/functions.h"
#include "RNG1.h"


// called on NMI
void Cpu_OnNMIINT(void)
{
	// Disable NMI pin (some boards do not have pullups)
    SIM_SCGC5 |= (uint32_t)SIM_SCGC5_PORTA_MASK; /* NMI and PORTA clock gate enable */
    PORTA_PCR4 &= PORT_PCR_MUX_MASK;
    /* enable input with pull up enable not NMI */
    PORTA_PCR4 |= PORT_PCR_MUX(01) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	return;
}

void FTM_OnCounterRestart(LDD_TUserData *UserDataPtr)
{
	// this function is called (typically at 200Hz) by the hardware clock interrupt and drives the sensor
	// read function and indirectly the fusion and magnetic calibration functions which
	// are software locked to the sensor read process

	// always enable the sensor read task
	// update time stamp counter
	mqxglobals.FTMTimestamp += (uint32)mqxglobals.FTMReload;
	// enable the (typically 200Hz) sensor read event FSL_SAMPLING_EVENT
	// with a mask of 1 (least significant bit set)
	_lwevent_set(&(mqxglobals.SamplingEventStruct), 1);

	return;
}


void UART_OnBlockSent(LDD_TUserData *UserDataPtr)
{
	// return with no action
	return;
}

void I2C_OnMasterBlockSent(LDD_TUserData *UserDataPtr)
{
	// set the I2C data sent flag
	mqxglobals.I2C_Status |= I2C_SENT_FLAG;

	return;
}


void I2C_OnMasterBlockReceived(LDD_TUserData *UserDataPtr)
{
	// set the I2C data received flag
	mqxglobals.I2C_Status |= I2C_RCVD_FLAG;

	return;
}

void I2C_OnError(LDD_TUserData *UserDataPtr)
{
	// return with no action
	return;
}

void UART_OnTxComplete(LDD_TUserData *UserDataPtr)
{
#ifdef DEEPSLEEP
	SCB_SCR |= SCB_SCR_SLEEPDEEP_MASK; // Enable full STOP mode
#endif
	return;
}

void UART_OnBlockReceived(LDD_TUserData *UserDataPtr)
{
	UART_Desc *ptr = (UART_Desc*)UserDataPtr;
	RNG1_Put(ptr->rxChar);
	UART_ReceiveBlock(ptr->handle, (LDD_TData *)&(ptr->rxChar), sizeof(ptr->rxChar));
}
