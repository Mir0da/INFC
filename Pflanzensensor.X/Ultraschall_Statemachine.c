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

//uint16_t timerOverflow;
uint8_t step=1;

ISR(TIMER1_COMPA_vect){
    
    triggerTime=0;
    TRIGGER_OFF; 
    TCCR1B &= ~(1<<CS10);
    TCCR1B &= ~(1<<CS11);
    TCCR1B &= ~(1<<CS12);
    TCCR1B = 0; //Timer off
}
ISR(TIMER1_OVF_vect)
{
	//timerOverflow++;	/* Increment Timer Overflow count */
}

void ultrasonic_Init2(void) {
    
    DDRB |= (1<<TRIGGER);     //set as output
    DDRB &= ~(1<<ECHO);     //set as input
    PORTB |= (1<<PORTB0); //enable pull-up 
    
    DDRC |= (1<<DDC2); //Test LED
    
    sei();   //enable global interrupts
   
    TRIGGER_OFF;
    LED_OFF;
}

void timerStart1()
{
    //start timer for 10us trigger signal
    
    //Timer 1 Controll
    TCCR1A = 0;
    TCCR1B |= (1<<WGM12);
    TIMSK1 |= (1<<OCIE1A); //input Compare interupt enable
    OCR1A=200;
    TCCR1B |= (1<<CS10); //Timer starten, min 10µs warten, prescaler 1, Timerticks min 160
}

void timerStart2()
{
    TCNT1 = 0;	// Clear Timer counter
    TCCR1A = 0;
	TCCR1B = 0;	
    TCCR1B |= (1<<ICES1);// Capture on rising edge,                  
    TCCR1B |= (1<<CS10);// No prescaler
	TIFR1 = 1<<ICF1;	// Clear ICP flag (Input Capture flag)
	TIFR1 = 1<<TOV1;	// Clear Timer Overflow flag
    
    TIMSK1 = (1 << TOIE1); // Enable Timer1 overflow interrupts
}

void ultrasonic_state_machine(){

    static double distanceCM;
    static uint16_t count;
    
    switch(step) {
    case 1:
        triggerTime =1;
        TRIGGER_ON;
        timerStart1();
        //Trigger Signal in der ISR wieder ausschalten
        step=2;
        break;

    case 2:
     
        if(triggerTime != 0)
        {
            break;
        }
        
        TRIGGER_OFF;
        timerStart2();
        step=3;
        break;

    case 3:
       if((TIFR1 & (1 << ICF1)) == 0) //Wait for rising Edge
        {
            break;
        }
        TCNT1 = 0;	/* Clear Timer counter */
        TCCR1B = 0x01;	/* Capture on falling edge, No prescaler */
		TIFR1 = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
		TIFR1 = 1<<TOV1;	/* Clear Timer Overflow flag */
		//timerOverflow = 0;/* Clear Timer overflow count */
       step = 4;
       break;
       
    case 4:
        
        if((TIFR1 & (1 << ICF1)) == 0) //Wait for falling Edge
        {
            break;
        }
        
        step= 5; 
        
        break;
        
    case 5:
        
        //count = ICR1 + (65535 * timerOverflow);	/* Take count */
		/* 16MHz Timer freq, sound speed =343 m/s */
        
		distanceCM = (double)count / 932.94;
        if (distanceCM < 20)
        {
            LED_ON;
        }
        else
        {
            LED_OFF;
        }

        step = 1;
        break;
    
    }
}
    
