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
    //Activate OC2B Port as Output
    DDRD |= (1<<DDD3);
    
    //Use timer 1 & 2 for PWM and soundlength controll
    //Clear Registers
    TCCR2A = 0;
    TCCR2B = 0;
    //Volume
    OCR2B = 120;
    //Connect OC2B Port
    TCCR2A |= (1<<COM2B1) | (1<<COM2B0);
    
    //Fast PWM
    TCCR2A |= (1<<WGM21)|(1<<WGM20);
    TCCR2B |= (1<<WGM22);
    
    //Soundlegth
    TCCR0A = 0;
    TCCR0A |= (1<<WGM01);   //CTC Mode
    
    TCCR0B =0;
    TCCR0B |= (1<<CS02)|(1<<CS00); //Prescaler 1024
    TCCR0B |= (1<<FOC0A); // force output compare match
    OCR0A = 250; //16ms -> ca61 overflows für 1sec
    
    //Timer/Counter0 Output Compare Match A Interrupt Enable
    TIMSK0 = (1<<OCIE0A);
    
    //activate interrupts
    sei();
}

void buzzer_on(){
    //Presclaer 1/128, start Timer
    TCCR2B |= (1<<CS22)|(1<<CS20);
}

void play_melody() {
    /* Replace with your application code */
    static volatile uint8_t counter = 0;
    TCCR2B &= ~(1<<CS22);
    TCCR2B &= ~(1<<CS20);
    OCR2A = melody1[counter];
    TCCR2B |= (1<<CS22)|(1<<CS20);
    counter = counter+1; 

    if(counter >9){
        counter =0;
    }
}
