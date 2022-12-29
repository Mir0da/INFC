/*
 * File:   sonicFinn.c
 * Author: sophi
 *
 * Created on 28. Dezember 2022, 15:43
 */


#include <xc.h>

#include "sonic.h" 
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <util/delay.h>  // Generates a Blocking Delay
#include<avr/interrupt.h>

#define LED_ON PORTC |= (1<<PORTC2)
#define LED_OFF PORTC &= ~(1<<PORTC2)

   
    uint8_t sonic_active; 
    uint16_t sonic_result; 
  
 void init_sonic() 
 { 
         sonic_active = 0; 
         sonic_result = 0; 
          
         // Set as input 
         DDR_SONIC        &= ~(1<<SONIC_ECHO); 
         // Set as output 
         DDR_SONIC        |= (1<<SONIC_TRIGGER); 
         
          DDRC |= (1<<DDC2); //Test LED
  
         SONIC_TRIGGER_LOW; 
          
         // PinChange Interrupt for PORTB 
         PCICR  |= (1<<PCIE0); 
         // Enable for ECHO IN 
         PCMSK0 |= (1<<PCINT0); 
         
         sei();
 } 
  
 void sonic_trigger_burst() 
 { 
         TCCR0B = 0; 
         TCNT0 = 0; 
         sonic_active = 1; 
         SONIC_TRIGGER_HIGH; 
         _delay_us(15); 
         SONIC_TRIGGER_LOW; 
 } 
  
 ISR(PCINT0_vect) 
 { 
         /* 
         Cock von 16000000/64 = 250000 
         340m/s = 340000mm/s 
         340000/250000 = 1,36 
         Also 1,36mm pro Takt 
         */ 
         if(PIN_SONIC &(1<<SONIC_ECHO)) 
         { 
                 TCCR0B |= (1<<CS01)|(1<<CS00); //Start Timer Prescaler 64 
                 return; 
         } 
         uint8_t cycles = TCNT0; // 0.68mm per cycle 
         TCCR0B = 0; 
         sonic_active = 0; 
         sonic_result = (cycles*7)/10; // result in mm, with an maximum of 178mm 
         if (sonic_result < 100)
        {
            LED_ON;
        }
        else
        {
            LED_OFF;
        }
 }