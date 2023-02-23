/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BUZZER_H
#define	BUZZER_H

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <xc.h> // include processor files - each processor file is guarded.  

#define H3 127
#define C2 120  //freq  523
#define D2 106
#define E2 95
#define F2 90
#define G2 80
#define A2 71
#define H2 63
#define C1 60

// Pins and Macros
#define BUZZER PIND5

void buzzer_Init();
void play_sound(uint8_t melodyPicker);

void play_melody();

#endif	/* BUZZER_H */

