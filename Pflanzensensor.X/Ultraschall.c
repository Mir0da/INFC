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
#define LED_ON PORTC |= (1<<PORTC2)
#define LED_OFF PORTC &= ~(1<<PORTC2)

static volatile uint8_t triggerTime;
static volatile uint8_t listenTime;

uint16_t timerOverflow;

ISR(TIMER1_COMPA_vect){
    
    if(triggerTime!= 0){
        TRIGGER_OFF;  
        triggerTime=0;
    } 
    
    if(listenTime!= 0){
        timerOverflow++;
        listenTime=0;
    } 

    TCCR1B &= ~(1<<CS10);
    TCCR1B &= ~(1<<CS11);
    TCCR1B &= ~(1<<CS12);
    TCCR1B = 0; //Timer off
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
    
    TRIGGER_OFF;
    LED_OFF;
}


uint8_t us_listen(){
    
    static uint8_t timerStart=0;
    static uint8_t timerStop=0;
    static uint8_t count;
    static uint16_t distance;
    
    triggerTime =1;
    TRIGGER_ON;
    OCR1A=200;
    TCCR1B |= (1<<CS10); //Timer starten min 10탎
    //Trigger Signal in der ISR wieder ausschalten

    while(triggerTime !=0){}
    
    listenTime = 1;
    gotEcho=0;
    TCNT1 = 0; //Reset Timer value to measure distance
    OCR1A=100;
    TCCR1B |= (1<<CS11); //Timer starten 50탎
    
    while (ECHO_IN == 0){} //wait till ECHO Signal gets to 1
    
    timerStart = TCNT1;
    //wait for 50탎 if Echo gets a response
    while(listenTime != 0){ 
        if(ECHO_IN == 0 && gotEcho ==0) //Echo is 1 until it gets a Reflected Signal
        {
            timerStop = TCNT1;      //Save Timerticks to calculate disctance
            gotEcho=1;
        }
    }

    if( gotEcho==1){
        //distanceMS = 1/((16000000/8)/(timerStop - timerStart)) * 1000; //Timer ticks in ms
        distanceMS = (timerStop - timerStart)/2000;
        distanceCM = distanceMS*17000; 
        USART_TransmitPolling((timerStop - timerStart));
       // return distanceCM;
        
        if (distanceCM < 20)
        {
            LED_ON;
        }
        else
        {
            LED_OFF;
        }
        
        timerStart=0;
        timerStop=0;
        return 1;
    }
    else
    {
        timerStart=0;
        timerStop=0;
        return 0;
    }
    return 0;
}