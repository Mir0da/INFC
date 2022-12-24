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

#define TRIGGER PINB0
#define ECHO PINB4

#define TRIGGER_ON PORTB |= (1<<TRIGGER)
#define TRIGGER_OFF PORTB &= ~(1<<TRIGGER)
#define ECHO_IN ((PINB & (1<<ECHO)))

//void ultrasonic_Init(void);
//uint8_t us_listen();
void ultrasonic_Init2(void);
void ultrasonic_state_machine();

#endif	/* ULTRASONIC_H */

