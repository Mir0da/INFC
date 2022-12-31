/*
 * File:   newSonic.c
 * Author: sophi
 *
 * Created on 28. Dezember 2022, 16:17
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <xc.h>
#include "ultrasonic.h"
#include <util/delay.h>  // Generates a Blocking Delay
#include <avr/interrupt.h>
 
int TimerOverflow = 0;
volatile uint8_t triggerFlag=0;

ISR(TIMER1_COMPA_vect)
{
    triggerFlag = 0;
}


ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;	/* Increment Timer Overflow count */
}


void sonic_Init(){
    
    DDRC |= (1<<TRIGGER);     //set as output
    DDRB &= ~(1<<ECHO);     //set as input
    PORTB |= (1<<PORTB0); //enable pull-up 
    
    DDRC |= (1<<DDC2); //Test LED

	sei();			/* Enable global interrupt */	
}

void initTimer_1(){
    
    //reset everything
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;
    TIFR1 = 0;
    TCCR1B |= (1<<WGM12);
    TCCR1B |= (1<<CS10);
    TCCR1C |= (1<<FOC1A);
    TIMSK1 |= (1<<OCIE1A);
    OCR1A= 192;
    sei();
}

void initTimer_2(){
    //reset everything
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;
    TIFR1 = 0;
    
    TIMSK1 = (1 << TOIE1);	/* Enable Timer1 overflow interrupts */
	TCCR1A = 0;		/* Set all bit to zero Normal operation */
    
    TCNT1 = 0;	/* Clear Timer counter */
    TCCR1B = 0x41;	/* Capture on rising edge, No prescaler*/
	TIFR1 = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
	TIFR1 = 1<<TOV1;	/* Clear Timer Overflow flag */
}

uint8_t sonic_burst(void) {
    
    static long count;
	static double distance;
    
    /* Give 12us trigger pulse on trig. pin to HC-SR04 */
    triggerFlag = 1;
    TRIGGER_ON;
    initTimer_1();
	while(triggerFlag !=0){};   //vll lieber mit TImerOverflow flag lösen?
	TRIGGER_OFF;
		
		
    initTimer_2();
    /*Calculate width of Echo by Input Capture (ICP) */

    while ((TIFR1 & (1 << ICF1)) == 0);/* Wait for rising edge */
    TCNT1 = 0;	/* Clear Timer counter */
    TCCR1B = 0x01;	/* Capture on falling edge, No prescaler */
    TIFR1 = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
    TIFR1 = 1<<TOV1;	/* Clear Timer Overflow flag */
    TimerOverflow = 0;/* Clear Timer overflow count */

    while ((TIFR1 & (1 << ICF1)) == 0);/* Wait for falling edge */
    count = ICR1 + (65535 * TimerOverflow);	/* Take count */
    /* 16MHz Timer freq, sound speed =343 m/s */
    distance = (double)count / 932.94;
   
    
    if (distance < 10)  //vll entprellen? 
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
