/*
 * File:   main.c
 * Author: sophi
 *
 * Created on 30. November 2022, 11:50
 */


#include <xc.h>
#include "moist.h"
#include "uart.h"
#include <util/delay.h>  // Generates a Blocking Delay


 uint16_t  ADC_8bit_Low_Byte  = 0; // unsigned int 8 bit variable
 uint16_t  ADC_8bit_High_Byte = 0; // unsigned int 8 bit variable

ISR(ADC_vect){
    ADC_8bit_Low_Byte   = ADCL;   // Read the 8 bit ADCL first,then ADCH
    ADC_8bit_High_Byte  = ADCH;
}

void main(void) {
    
    //moistInit();  
    USART_Init();
    uint16_t test= 1000;
	while (1)
	{
        USART_TransmitPolling('A');
        USART_TransmitPolling(ADC_8bit_High_Byte);
		USART_TransmitPolling(ADC_8bit_Low_Byte);
		USART_TransmitPolling('E');
		USART_TransmitPolling('\n');
		_delay_ms(1000);
	}
	return 0;
}
