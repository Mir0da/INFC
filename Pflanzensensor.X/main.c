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
#include <avr/interrupt.h>

uint16_t  ADC_High_Byte = 0x00000011; // unsigned int 8 bit variable

 volatile uint8_t sleepFlag=0;
 
void startSleepTimer(){
    //reset everything
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;
    TIFR1 = 0;
    
    //configure Timer for ~5min
    TCCR1A = 0;
    TCCR1B |= (1<<WGM12);
    TCCR1B |= (1<<CS12) | (1<<CS10);
    TCCR1C |= (1<<FOC1A);
    TIMSK1 |= (1<<OCIE1A);
    OCR1A= 4718592;
}

ISR(TIMER1_COMPA_vect)
{
	static volatile uint8_t count = 0;
    count++;
    if(count > 72)
    {
        //stop timer
        TCCR1B &= ~(1<<CS12); 
        TCCR1B &= ~(1<<CS10);
        sleepFlag=0;
        count = 0;
    }
}

int main(void) {
   
    sonic_Init();
    moist_Init();  
    USART_Init();
    buzzer_Init();
    
    // Display
    SPI_init();
	Display_init();
    
    uint16_t window[] ={
        0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
        0x127E, 0x1505, 0x1305, 0x16AA //Werte f�r Fenstergr��e, xAnfang (0x1267), xEnde, yStart, yEnde (0x169D)       
	};
    
    for(uint16_t i= 0; i < (176*132); i++)
    {
       SPISend8Bit(0x00); // SCHWARZ 0x0000
       SPISend8Bit(0x00); // SCHWARZ 0x0000
    }
    
    SendCommandSeq(window,6);
    
    for(uint16_t i= 0; i < (166*122); i++)
    {
       SPISend8Bit(0xFF); // WEISS 0x07EF
       SPISend8Bit(0xFF); // WEISS 0x07EF
    }
    
    //sendPic(Bild1); //funktioniert!
    
    uint8_t critical;
	
	while (1)
	{
        displayPlant(ADCH);   
        
        //ohne Autotrigger funktioniert
        //ADCSRA |= (1<<ADSC);    //start conversion

        //ADC ist im Autotrigger mode, man muss nur warten bis ein ergebnis da ist.
        //k�nnten wir auch seltener abfragen, �ber Timer steuern wann die conversion gestartet wird
       // while(!(ADCSRA & (1<<ADSC))){
        
        //};
        
        //mit Interrupt enable f�r ADC kommt IRGENDWAS beim Uart an
        //USART_TransmitPolling(test);
        //USART_TransmitPolling(ADCH);
        
        //Prototype programmablauf
        
        if(sleepFlag == 0){
            if(ADCH > critical)
            {
                if(sonic_burst())
                {
                    play_sound();
                    sleepFlag = 1;
                    startSleepTimer();
                }
            }
        }
	}
    return 0;
}
