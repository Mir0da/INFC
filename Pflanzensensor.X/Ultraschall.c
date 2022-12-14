/*
 * File:   Ultraschall.c
 * Author: sophi
 *
 * Created on 7. Dezember 2022, 12:44
 */


#include <xc.h>
#include "ultrasonic.h"
#include <stdio.h>
#include<avr/interrupt.h>

#define LED_TOGGLE PORTC ^= (1<<PORTC2)

uint8_t triggerTime;
uint8_t listenTime;

ISR(TIMER1_COMPA_vect){

    if(triggerTime!= 0){
        triggerTime= 0;
        TRIGGER_OFF;  
        TCCR1B = 0; //Timer off
    } 
    
    if(listenTime!= 0){
        listenTime= 0; 
        TCCR1B = 0; //Timer off
    } 
    
}

void ultrasonic_Init(void) {
    
    DDRB |= (1<<TRIGGER);     //set as output
    DDRB &= ~(1<<ECHO);     //set as input
    
    DDRC |= (1<<DDC2); //Test LED

    //Timer 1 Controll
    TCCR1A = 0;
    TCCR1B |= (1<<WGM12);
    //10탎 warten, prescaler 1, Timerticks 160
    TCCR1B = 0;
    TIMSK1 |= (1<<OCIE1A); 
    sei();
}


uint8_t us_listen(){
    
    uint8_t timerStart;
    uint8_t timerStop;
    uint8_t gotEcho;
    
    TRIGGER_ON;
    triggerTime =1;
    OCR1A=160;
    TCCR1B |= (1<<CS10); //Timer starten min 10탎
    //Trigger Signal in der ISR wieder ausschalten

    listenTime = 1;
    gotEcho=0;
    TCCR1B |= (1<<CS10); //Timer starten 50탎
    OCR1A=800;
    //wait for 50탎 if Echo gets set to 0
    while(listenTime != 0){        
        if(ECHO == 1)
        {
           timerStart = TCNT1; 
        }

        if(ECHO == 0)
        {
            timerStop = TCNT1;
            gotEcho=1;
            LED_TOGGLE;
        }
    }
    if( gotEcho==1){
        //distanceMS = (timerStop -timerStart);
        //distanceCM = distanceMS/58; 
        //USART_TransmitPolling(distanceCM);
       // return distanceCM;
        return 1;
    }
    else
    {
        return 0;
    }
    return 0;
}