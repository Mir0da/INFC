/* 
 * File: Display.c   
 * Author: T. Taefi
 * Comments: Based on code by Michael Behrens
 * Revision history: 1.0
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DISPLAY_H
#define	DISPLAY_H

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <util/delay.h>
#include <avr/io.h>

// Pins and Macros
#define SPI_DDR DDRB
#define CS      PINB2
#define MOSI    PINB3
#define SCK     PINB5
#define D_C		PIND2		//display: Data/Command
#define Reset	PIND3		//display: Reset


void SPI_init(void);
/**
    <p><b>void SPI_init(void):</b></p>
  
    <p><b>Summary: Setup of SPI-Display connection</b></p>

    <p><b>Description: set CS, MOSI and SCK to output. enable SPI, set as master, and clock to fosc/4 </b></p>

    <p><b>Precondition: Physical connection to Display via Shield.</b></p>

    <p><b>Parameters: None</b></p>

    <p><b>Returns: None</b></p>
 **/

void SPISend8Bit(uint8_t);
void SendCommandSeq(const uint16_t * , uint16_t );
void Display_init(void);
void sendPic(const __flash int *, int count);

#endif	/* DISPLAY_H */

