/*
 * File:   buttons.c
 * Author: sophi
 *
 * Created on 3. Januar 2023, 15:40
 */


#include <xc.h>
#include "buttons.h"

void button_Init(){
    //Button 1 for long Sleep Timer
    DDRD &= ~(1<< DDD1);   //Button input 
    PORTD |= (1<<PORTD1); //enable pull-up 
    
    //Button 2 for Melody Change
    DDRB &= ~(1<< DDB1);   //Button input 
    PORTB |= (1<<PORTB1); //enable pull-up 
}

