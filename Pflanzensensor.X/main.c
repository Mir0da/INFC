/*
 * File:   main.c
 * Author: sophi
 *
 * Created on 30. November 2022, 11:50
 */
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <xc.h>
#include "moist.h"
#include "uart.h"
#include "buzzer.h"
#include "display.h"
#include "picture.h"
#include "ultrasonic.h"
#include <util/delay.h>  // Generates a Blocking Delay
#include<avr/interrupt.h>

uint16_t  ADC_High_Byte = 0x00000011; // unsigned int 8 bit variable
 
ISR(TIMER2_COMPA_vect){
     
     static volatile uint8_t overflowCounter = 0;
   
     if(overflowCounter > 20)
     {
        play_melody(); 
         overflowCounter =0;
     }
     
     overflowCounter++; 
}

int main(void) {
    
    moist_Init();  
    USART_Init();
    ultrasonic_Init();
    buzzer_Init();
    buzzer_on();
    
    // Display
    SPI_init();
	Display_init();
    
    uint16_t window[] ={
        0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
        0x127E, 0x1505, 0x1305, 0x16AA //Werte für Fenstergröße, xAnfang (0x1267), yAnfang, xEnde, yEnde (0x169D)       
	};
    
    for(uint16_t i= 0; i < (176*132); i++)
    {
       SPISend8Bit(0x00); // SCHWARZ 0x0000
       SPISend8Bit(0x00); // SCHWARZ 0x0000
    }
    
    SendCommandSeq(window,6);
    
    
//    uint16_t test= 200;
    uint8_t critical;
    
	while (1)
	{
        //ohne Autotrigger funktioniert
        //ADCSRA |= (1<<ADSC);    //start conversion

        //ADC ist im Autotrigger mode, man muss nur warten bis ein ergebnis da ist.
        //könnten wir auch seltener abfragen, über Timer steuern wann die conversion gestartet wird
        while(!(ADCSRA & (1<<ADSC))){
        
            
        };
        
        //mit Interrupt enable für ADC kommt IRGENDWAS beim Uart an
        //USART_TransmitPolling(test);
        
        //USART_TransmitPolling(ADCH);
        
       // us_listen();
        //Prototype programmablauf
        if(ADCH > critical)
        {
            //if(us_listen())
            //{
                //play_sound();
            //}
        }
        
        sendPic(Bild1);
        
        _delay_ms(500);
        
        sendPic(Bild1Animated);
	}
    return 0;
}
