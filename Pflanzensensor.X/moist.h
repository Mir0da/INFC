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
//Die LED Bank kann nicht verwendet werden da sonst jeder ADC Eingang des Mikrocontrollers schon belegt wäre
//entweder mit einer LED oder dem POTI, dadurch enstehen Spannungsteiler die es unmöglich machen akurate Spannungspegel an 
//den ADC Eingängen zu erhalten.

void moist_Init();

#endif	/* MOIST_H */



