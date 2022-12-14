/*
 * File:   buzzer.c
 * Author: sophi
 *
 * Created on 07. Dezember 2022, 22:58
 */

#define F_CPU 16000000UL
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>  // Generates a Blocking Delay
#include "buzzer.h"
#include<avr/interrupt.h>

uint8_t tones[7] = {C2,D2,E2,F2,G2,A2,H2};
uint8_t melody1[10] = {E2,0,E2,0,E2,C2,G2,0,0,0};


void buzzer_Init(){
    //Activate OC0B Port as Output
    DDRD |= (1<<DDD5);
    
    //Use timer 0 & 2 for PWM and soundlength controll
    //Clear Registers
    TCCR0A = 0;
    TCCR0B = 0;
    //Volume
    OCR0B = 2;
    //Connect OC2B Port
    TCCR0A |= (1<<COM0B1) | (1<<COM0B0);
    
    //Fast PWM
    TCCR0A |= (1<<WGM01)|(1<<WGM00);
    TCCR0B |= (1<<WGM02);
    
    //Soundlegth
    TCCR2A = 0;
    TCCR2A |= (1<<WGM21);   //CTC Mode
    
    TCCR2B =0;
    TCCR2B |= (1<<CS22)|(1<<CS21)|(1<<CS20); //Prescaler 1024
    TCCR2B |= (1<<FOC2A); // force output compare match
    OCR2A = 250; //16ms -> ca61 overflows für 1sec
    
    //Timer/Counter0 Output Compare Match A Interrupt Enable
    TIMSK2 = (1<<OCIE2A);
    
    //activate interrupts
    sei();
}

void buzzer_on(){
    //Presclaer 1/128, start Timer
    TCCR0B |= (1<<CS22)|(1<<CS20);
}

void play_melody() {
    /* Replace with your application code */
    static volatile uint8_t counter = 0;
    TCCR0B &= ~(1<<CS22);
    TCCR0B &= ~(1<<CS20);
    OCR0A = melody1[counter];
    TCCR0B |= (1<<CS22)|(1<<CS20);
    counter = counter+1; 
    
    if(counter >9){
        counter =0;
    }
}
