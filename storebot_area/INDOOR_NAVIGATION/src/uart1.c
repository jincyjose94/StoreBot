//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009 Code Red Technologies Ltd. 
//
// UART example project for RDB1768 development board
//
// Software License Agreement
// 
// The software is owned by Code Red Technologies and/or its suppliers, and is 
// protected under applicable copyright laws.  All rights are reserved.  Any 
// use in violation of the foregoing restrictions may subject the user to criminal 
// sanctions under applicable laws, as well as to civil liability for the breach 
// of the terms and conditions of this license.
// 
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// USE OF THIS SOFTWARE FOR COMMERCIAL DEVELOPMENT AND/OR EDUCATION IS SUBJECT
// TO A CURRENT END USER LICENSE AGREEMENT (COMMERCIAL OR EDUCATIONAL) WITH
// CODE RED TECHNOLOGIES LTD. 
//
//*****************************************************************************


#include "LPC17xx.h"

// PCUART1
#define PCUART1_POWERON (1 << 4)

#define PCLK_UART1 8
#define PCLK_UART1_MASK (3 << 8)

#define IER_RBR		0x01
#define IER_THRE	0x02
#define IER_RLS		0x04

#define IIR_PEND	0x01
#define IIR_RLS		0x03
#define IIR_RDA		0x02
#define IIR_CTI		0x06
#define IIR_THRE	0x01

#define LSR_RDR		0x01
#define LSR_OE		0x02
#define LSR_PE		0x04
#define LSR_FE		0x08
#define LSR_BI		0x10
#define LSR_THRE	0x20
#define LSR_TEMT	0x40
#define LSR_RXFE	0x80

// ***********************
// Function to set up UART
void UART1_Init(int baudrate)
{
	int pclk;
	unsigned long int Fdiv;

	// PCLK_UART1 is being set to 1/4 of SystemCoreClock
	pclk = SystemCoreClock / 4;	
	
	// Turn on power to UART1
	LPC_SC->PCONP |=  PCUART1_POWERON;
		
	// Turn on UART1 peripheral clock
	LPC_SC->PCLKSEL0 &= ~(PCLK_UART1_MASK);
	LPC_SC->PCLKSEL0 |=  (0 << PCLK_UART1);		// PCLK_periph = CCLK/4
	
	// Set PINSEL0 and PINSEL1 so that P0.15 = TXD1, P0.16 = RXD1
	LPC_PINCON->PINSEL0 &= ~0xC0000000;
	LPC_PINCON->PINSEL0 |= 0x40000000; // Enable TxD1 P0.15
	LPC_PINCON->PINSEL1 &= ~0x00000003;
	LPC_PINCON->PINSEL1 |= 0x00000001; // Enable RxD1 P0.16
	
	LPC_UART1->LCR = 0x83;		// 8 bits, no Parity, 1 Stop bit, DLAB=1
	LPC_UART1->FDR = 0x20;
	Fdiv = ( pclk / 16 ) / baudrate ;	// Set baud rate
    LPC_UART1->DLM = Fdiv / 256;
    LPC_UART1->DLL = Fdiv % 256;
    LPC_UART1->LCR = 0x03;		// 8 bits, no Parity, 1 Stop bit DLAB = 0
    LPC_UART1->FCR = 0x07;		// Enable and reset TX and RX FIFO

}

// ***********************
// Function to send character over UART
void UART1_Sendchar(char c)
{
	while( (LPC_UART1->LSR & LSR_THRE) == 0 );	// Block until tx empty
	
			LPC_UART1->THR = c;
}

// ***********************
// Function to get character from UART
char UART1_Getchar()
{
	char c;
	while( (LPC_UART1->LSR & LSR_RDR) == 0 );  // Nothing received so just block
			c = LPC_UART1->RBR; // Read Receiver buffer register
			return c;
}



