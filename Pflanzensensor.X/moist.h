// This is a guard condition so that contents of this file are not included
// more than once.  
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MOIST_H
#define	MOIST_H

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <util/delay.h>
#include <avr/io.h>

// Pins and Macros
#define ANALOGIN PINC1

void moist_Init();

#endif	/* MOIST_H */



