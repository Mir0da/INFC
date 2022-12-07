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
    ADMUX=0x61; //AVCC at AREF Pin, Left Adjust on, Input ADC1
   // ADCSRA = 0x86;        //ohne Autotrigger, Prescaler 64
    ADCSRA = 0xA6; //ADC enable, Auto Trigger and  Interrupt disabled,Interupt Flag disabled, Prescaler 64
    //ADCSRA = 0xAE; //ADC enable, Auto Trigger and  Interrupt enabled,Interupt Flag disabled, Prescaler 64
    ADCSRB = 0;
    ADCSRA |= (1<<ADSC);    //start conversion

}
