/*
 * File:   Feuchtigkeit.c
 * Author: sophi
 *
 * Created on 30. November 2022, 11:08
 */


#include <xc.h>
#include <avr/interrupt.h>
#include "moist.h"

void moistInit(){
    
     sei();
     
    //ADC     
    ADMUX=0x60; 
    ADCSRA = 0xAE;
    ADCSRB = 0;
    ADCSRA |= (1<<ADSC);

}
