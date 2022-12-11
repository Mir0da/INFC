/*
 * File:   buzzer.c
 * Author: sophi
 *
 * Created on 07. Dezember 2022, 22:58
 */

#include <xc.h>
#include <avr/io.h>
#include "buzzer.h"

void buzzer_Init(){
    //Use timer 1 & 2 for PWM and soundlength controll
    DDRD |= (1<<DDD3);
    
    //Clear Registers
    TCCR2A = 0;
    TCCR2B = 0;
    
    //Frequenzy (1kHz)
    OCR2A = 125;
    //Volume
    OCR2B = 120;
    
    TCCR2A |= (1<<COM2B1) | (1<<COM2B0);
    
    //Fast PWM
    TCCR2A |= (1<<WGM21)|(1<<WGM20);
    TCCR2B |= (1<<WGM22);
    
    
    //Soundlegth
    TCCR0A = 0;
    TCCR0A |= (1<<WGM01);   //CTC Mode
    
    TCCR0B=0;
    TCCR0B |= (1<<CS02)|(1<<CS00); //Prescaler 1024
    TCCR0B |= (1<<FOC0A); // force output compare match
    OCR0A = 250; //16ms -> ca61 overflows für 1sec
    
    TIMSK0 = (1<<OCIE0A);
}

void buzzer_on(){
    //Presclaer 1/128
   OCR2A = C2; //test
    TCCR2B |= (1<<CS22)|(1<<CS20);
}


void play_melody() {
    /* Replace with your application code */
    volatile uint8_t counter = 0;
    uint8_t tones[8]={C2,D2, E2, F2, G2,A2,H2};
    OCR2A = tones[counter];
    
    counter++; 
    if(counter >6){
        counter =0;
    }
}
