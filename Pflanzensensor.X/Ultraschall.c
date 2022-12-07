/*
 * File:   Ultraschall.c
 * Author: sophi
 *
 * Created on 7. Dezember 2022, 12:44
 */


#include <xc.h>
#include "ultrasonic.h"

void ultrasonic_Init(void) {
    
    DDRB |= (1<<TRIGGER);     //set as output
    DDRB &= ~(1<<ECHO);     //set as input

    //Timer Controll
    TCCR0A = 0;
    TCCR0A |= (1<<WGM01);
    //10µs warten, prescaler 8, Timerticks 20
    TCCR0B = 0;
    TCCR0B |= (1<<CS01);
    
}


uint8_t measure(){
    TRIGGER_ON;
    OCR0A = 20; //Start Timer
    
    //wait for Timer match
  
    TRIGGER_OFF;
    
    //wait for 50µs if Echo gets set to 1
    if(ECHO == 1)
    {
       return 1; 
    }
    else
        return 0;
}