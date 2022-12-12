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

#define C2 239
#define D2 213
#define E2 190
#define F2 179
#define G2 159
#define A2 142
#define H2 126


void buzzer_Init();
void buzzer_on();

void play_melody();

#endif	/* BUZZER_H */

