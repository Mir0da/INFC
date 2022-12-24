/*
 * File:   Ultraschall_Statemachine.c
 * Author: sophi
 *
 * Created on 24. Dezember 2022, 16:39
 */


#include <xc.h>
#include "uart.h"
#include "ultrasonic.h"
#include <stdio.h>
#include<avr/interrupt.h>

#define LED_TOGGLE PORTC ^= (1<<PORTC2)
#define LED_ON PORTC |= (1<<PORTC2)
#define LED_OFF PORTC &= ~(1<<PORTC2)

static volatile uint8_t triggerTime;
static volatile uint8_t listenTime;

uint8_t step=1;

ISR(TIMER1_COMPA_vect){
    
    triggerTime=0;

    listenTime=0;

    TCCR1B &= ~(1<<CS10);
    TCCR1B &= ~(1<<CS11);
    TCCR1B &= ~(1<<CS12);
    TCCR1B = 0; //Timer off
}
void ultrasonic_Init2(void) {
    
    DDRB |= (1<<TRIGGER);     //set as output
    DDRB &= ~(1<<ECHO);     //set as input
    
    DDRC |= (1<<DDC2); //Test LED

    //Timer 1 Controll
    TCCR1A = 0;
    TCCR1B |= (1<<WGM12);
    //10µs warten, prescaler 1, Timerticks 160
    TCCR1B = 0;
    TIMSK1 |= (1<<OCIE1A); 
    sei();
    
    TRIGGER_OFF;
    LED_OFF;
}


void ultrasonic_state_machine(){
    
    static uint8_t timerStart=0;
    static uint8_t timerStop=0;
    static uint8_t gotEcho;
    static uint16_t distanceMS;
    static uint16_t distanceCM;
    
    switch(step) {
    case 1:
        triggerTime =1;
        TRIGGER_ON;
        OCR1A=200;
        TCCR1B |= (1<<CS10); //Timer starten min 10µs
        //Trigger Signal in der ISR wieder ausschalten
        step=2;
        break;

    case 2:
     
        if(triggerTime != 0)
        {
            break;
        }
        
        TRIGGER_OFF;
        listenTime = 1;
        gotEcho=0;
        TCNT1 = 0; //Reset Timer value to measure distance
        OCR1A=100;
        TCCR1B |= (1<<CS11); //Timer starten 50µs
        step=3;
        break;

    case 3:
       if((ECHO_IN == 0))
        {
            break;
        }
       timerStart = TCNT1;
       step = 4;
       break;
       
    case 4:
        
        if(listenTime != 0){ 
            if(ECHO_IN == 0 && gotEcho ==0) //Echo is 1 until it gets a Reflected Signal
            {
                timerStop = TCNT1;      //Save Timerticks to calculate disctance
                gotEcho=1;
            }
        }
        else
        {
           step= 5; 
        }
        break;
        
    case 5:
        
        if( gotEcho==1){
            //distanceMS = 1/((16000000/8)/(timerStop - timerStart)) * 1000; //Timer ticks in ms
            distanceMS = (timerStop - timerStart)/2000;
            distanceCM = distanceMS*17000; 
            USART_TransmitPolling((timerStop - timerStart));
            USART_TransmitPolling(0);
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
        }
        else
        {
            timerStart=0;
            timerStop=0;
        }

        step = 1;
        break;
    
    }
}
    
