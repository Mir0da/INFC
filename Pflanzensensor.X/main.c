/*
 * File:   main.c
 * Author: sophi
 *
 * Created on 30. November 2022, 11:50
 */
#define F_CPU 16000000UL

#include <xc.h>
#include "moist.h"
#include "uart.h"
#include "buzzer.h"
#include <util/delay.h>  // Generates a Blocking Delay



 uint16_t  ADC_High_Byte = 0x00000011; // unsigned int 8 bit variable
 
 ISR(TIMER0_COMPA_vect){
     
     volatile uint8_t overflowCounter = 0;
   
     if(overflowCounter > 61)
     {
         overflowCounter =0;
         play_melody(); 
     }
     
     overflowCounter++; 
 }

int main(void) {
    
    moist_Init();  
    USART_Init();
    buzzer_Init();
    buzzer_on();
//    uint16_t test= 200;
    uint8_t critical;
    
	while (1)
	{
        //ohne Autotrigger funktioniert
        //ADCSRA |= (1<<ADSC);    //start conversion

        //ADC ist im Autotrigger mode, man muss nur warten bis ein ergebnis da ist.
        //k�nnten wir auch seltener abfragen, �ber Timer steuern wann die conversion gestartet wird
        while(!(ADCSRA & (1<<ADSC))){};
        
        //mit Interrupt enable f�r ADC kommt IRGENDWAS beim Uart an
        //USART_TransmitPolling(test);
        
        USART_TransmitPolling(ADCH);
		_delay_ms(1000);
        
        
        //Prototype programmablauf
        if(ADCH > critical)
        {
            //if(us_listen())
            //{
                //play_sound();
            //}
        }
	}
     return 0;
}
