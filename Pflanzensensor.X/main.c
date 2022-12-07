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
#include <util/delay.h>  // Generates a Blocking Delay



 uint16_t  ADC_High_Byte = 0x00000011; // unsigned int 8 bit variable
 


void main(void) {
    
    moist_Init();  
    USART_Init();
    uint16_t test= 200;
	while (1)
	{
        //ohne Autotrigger funktioniert
        //ADCSRA |= (1<<ADSC);    //start conversion

        //ADC ist im Autotrigger mode, man muss nur warten bis ein ergebnis da ist.
        //könnten wir auch seltener abfragen, über Timer steuern wann die conversion gestartet wird
        while(!(ADCSRA & (1<<ADSC))){};
        
        //mit Interrupt enable für ADC kommt IRGENDWAS beim Uart an
        //USART_TransmitPolling(test);
        
        USART_TransmitPolling(ADCH);
		_delay_ms(1000);
	}
}
