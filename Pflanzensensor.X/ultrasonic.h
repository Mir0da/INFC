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

#define TRIGGER PINC3
#define ECHO PINB0

#define TRIGGER_ON PORTC |= (1<<TRIGGER)
#define TRIGGER_OFF PORTC &= ~(1<<TRIGGER)
#define ECHO_IN ((PINB & (1<<ECHO)))

void sonic_Init();
uint8_t sonic_burst(void);

#endif	/* ULTRASONIC_H */

