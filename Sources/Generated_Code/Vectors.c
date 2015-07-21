/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : Vectors.c
**     Project     : Sources
**     Processor   : MKL26Z128VMC4
**     Version     : Component 01.006, Driver 01.04, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-07-08, 17:02, # CodeGen: 1
**     Abstract    :
**
**     Settings    :
**
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file Vectors.c                                                  
** @version 01.04
** @brief
**
*/         
/*!
**  @addtogroup Vectors_module Vectors module documentation
**  @{
*/         

  #include "Cpu.h"
  #include "AD1.h"
  #include "Events.h"


  /* ISR prototype */
  extern uint32_t __SP_INIT;
  extern
  #ifdef __cplusplus
  "C"
  #endif
  void __thumb_startup( void );
  
  
  /*lint -esym(765,__vect_table) Disable MISRA rule (8.10) checking for symbols (__vect_table). Definition of the interrupt vector table placed by linker on a predefined location. */
  /*lint -save  -e926 -e927 -e928 -e929 Disable MISRA rule (11.4) checking. Need to explicitly cast pointers to the general ISR for Interrupt vector table */
  
  __attribute__ ((section (".vectortable"))) const tVectorTable __vect_table = { /* Interrupt vector table */
  
    /* ISR name                             No. Address      Pri Name                          Description */
    &__SP_INIT,                        /* 0x00  0x00000000   -   ivINT_Initial_Stack_Pointer   used by PE */
    {
    (tIsrFunc)&__thumb_startup,        /* 0x01  0x00000004   -   ivINT_Initial_Program_Counter used by PE */
    (tIsrFunc)&Cpu_INT_NMIInterrupt,   /* 0x02  0x00000008   -2   ivINT_NMI                     used by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x03  0x0000000C   -1   ivINT_Hard_Fault              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x04  0x00000010   -   ivINT_Reserved4               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x05  0x00000014   -   ivINT_Reserved5               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x06  0x00000018   -   ivINT_Reserved6               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x07  0x0000001C   -   ivINT_Reserved7               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x08  0x00000020   -   ivINT_Reserved8               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x09  0x00000024   -   ivINT_Reserved9               unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0A  0x00000028   -   ivINT_Reserved10              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0B  0x0000002C   -   ivINT_SVCall                  unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0C  0x00000030   -   ivINT_Reserved12              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0D  0x00000034   -   ivINT_Reserved13              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0E  0x00000038   -   ivINT_PendableSrvReq          unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0F  0x0000003C   -   ivINT_SysTick                 unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x10  0x00000040   -   ivINT_DMA0                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x11  0x00000044   -   ivINT_DMA1                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x12  0x00000048   -   ivINT_DMA2                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x13  0x0000004C   -   ivINT_DMA3                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x14  0x00000050   -   ivINT_Reserved20              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x15  0x00000054   -   ivINT_FTFA                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x16  0x00000058   -   ivINT_LVD_LVW                 unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x17  0x0000005C   -   ivINT_LLW                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x18  0x00000060   -   ivINT_I2C0                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x19  0x00000064   -   ivINT_I2C1                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1A  0x00000068   -   ivINT_SPI0                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1B  0x0000006C   -   ivINT_SPI1                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1C  0x00000070   -   ivINT_UART0                   unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1D  0x00000074   -   ivINT_UART1                   unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1E  0x00000078   -   ivINT_UART2                   unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1F  0x0000007C   -   ivINT_ADC0                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x20  0x00000080   -   ivINT_CMP0                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x21  0x00000084   -   ivINT_TPM0                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x22  0x00000088   -   ivINT_TPM1                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x23  0x0000008C   -   ivINT_TPM2                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x24  0x00000090   -   ivINT_RTC                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x25  0x00000094   -   ivINT_RTC_Seconds             unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x26  0x00000098   -   ivINT_PIT                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x27  0x0000009C   -   ivINT_I2S0                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x28  0x000000A0   -   ivINT_USB0                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x29  0x000000A4   -   ivINT_DAC0                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2A  0x000000A8   -   ivINT_TSI0                    unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2B  0x000000AC   -   ivINT_MCG                     unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2C  0x000000B0   -   ivINT_LPTimer                 unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2D  0x000000B4   -   ivINT_Reserved45              unused by PE */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2E  0x000000B8   -   ivINT_PORTA                   unused by PE */
    (tIsrFunc)&Cpu_Interrupt           /* 0x2F  0x000000BC   -   ivINT_PORTC_PORTD             unused by PE */
    }
  };
  /*lint -restore Enable MISRA rule (11.4) checking. */
  

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
