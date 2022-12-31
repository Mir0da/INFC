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

uint8_t melodyArray[3][10] = {{E2,0,E2,0,E2,C2,G2,0,0,0},{G2,C2,E2,0,E2,0,E2,0,0,0},{G2,G2,A2,G2,C3,H2,0,0,0}};
uint8_t melodyPick;

ISR(TIMER2_COMPA_vect){
     
     static volatile uint8_t overflowCounter = 0;
   
     if(overflowCounter > 20)
     {
        play_melody(); 
        overflowCounter =0;
     }
     
     overflowCounter++; 
}


void buzzer_Init(){
    //Activate OC0B Port as Output
    DDRD |= (1<<BUZZER);
    
    //Use timer 0 & 2 for PWM and soundlength controll
    //Clear Registers
    TCCR0A = 0;
    TCCR0B = 0;
    //Volume
    OCR0B = 1;
    //Connect OC2B Port
    TCCR0A |= (1<<COM0B1) | (1<<COM0B0);
    
    //Fast PWM
    TCCR0A |= (1<<WGM01)|(1<<WGM00);
    TCCR0B |= (1<<WGM02);
    
    //Soundlegth
    
    TCCR2A |= (1<<WGM21);   //CTC Mode
    TCCR2B |= (1<<FOC2A); // force output compare match
    OCR2A = 250; //16ms -> ca61 overflows für 1sec
    
    //Timer/Counter0 Output Compare Match A Interrupt Enable
    TIMSK2 = (1<<OCIE2A);
    
    //activate interrupts
    sei();
}

void play_sound(uint8_t melodyPicker){
    
    melodyPick = melodyPicker;
    //start both timers
    //Presclaer 1/256, start Timer
    TCCR0B |= (1<<CS02);
    TCCR2B |= (1<<CS22)|(1<<CS21)|(1<<CS20); //Prescaler 1024
}

void play_melody() {
 
    static volatile uint8_t counter = 0;
    TCCR0B &= ~(1<<CS02);
    OCR0A = melodyArray[melodyPick][counter];
    _delay_us(200); //to seperate 2 tones from each other
    TCCR0B |= (1<<CS02);
    counter++; 
    
    if(counter > 9){
        //Turn both timers off
        TCCR0B &= ~(1<<CS02);
        TCCR2B &= ~(1<<CS22);
        TCCR2B &= ~(1<<CS21);
        TCCR2B &= ~(1<<CS20);
        counter = 0;
    }
    
}
