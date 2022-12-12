/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ULTRASONIC_H
#define	ULTRASONIC_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define TRIGGER PINB4
#define ECHO PINB5

#define TRIGGER_ON PORTD |= (1<<PORTB4)
#define TRIGGER_OFF PORTD &= ~(1<<PORTB4)

void ultrasonic_Init(void);
uint8_t us_listen();

#endif	/* ULTRASONIC_H */

