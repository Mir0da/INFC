/*
 * File:   Feuchtigkeit.c
 * Author: sophi
 *
 * Created on 30. November 2022, 11:08
 */


#include <xc.h>
#include <avr/interrupt.h>
#include "moist.h"



void moist_Init(){
    
     sei();
     
    //ADC     
    ADMUX=0;
    ADMUX |= (1<<REFS0); 
    ADMUX |= (1<<ADLAR);
    ADMUX |= (1<<MUX0);//AVCC at AREF Pin, Left Adjust on, Input ADC1

    ADCSRA = 0;
    ADCSRA |= (1<<ADEN); 
    ADCSRA |= (1<<ADPS0);
    ADCSRA |= (1<<ADPS1);
    ADCSRA |= (1<<ADPS2);//ADC enable, Auto Trigger and  Interrupt disabled,Interupt Flag disabled, Prescaler 128
 
    ADCSRB = 0;
    ADCSRA |= (1<<ADSC);    //start conversion

}
