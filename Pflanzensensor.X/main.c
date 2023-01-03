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
#include "ultrasonic.h"
#include "buttons.h"
#include <util/delay.h>  // Generates a Blocking Delay
#include <avr/interrupt.h>

volatile uint8_t sleepFlag=0;
volatile uint8_t sleepLongFlag=0;
volatile uint8_t melodyPicker =0;
 
void startSleepTimer(){
    //reset everything
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;
    TIFR1 = 0;
    TCNT1 = 0;	/* Clear Timer counter */
    
    //configure Timer for ~5min
    TCCR1A = 0;
    TCCR1B |= (1<<WGM12);
    TCCR1B |= (1<<CS12) | (1<<CS10);
    TCCR1C |= (1<<FOC1B);
    TIMSK1 |= (1<<OCIE1B);
    OCR1A= 65535; //max value for OCR1B, 71 overflows = 297.8sec
}

ISR(TIMER1_COMPB_vect)
{
	static volatile uint8_t count = 0;
 
    if(count > 2 && sleepLongFlag == 0) 
    {
        sleepFlag=0;
        count = 0;
        //stop timer
        TCCR1B &= ~(1<<CS12); 
        TCCR1B &= ~(1<<CS10);
    }
    if(count > 5 && sleepLongFlag == 1)  //72 fuer ~ 5min
    {
        sleepFlag=0;
        sleepLongFlag = 0;
        count = 0;
        drawSleepStatus(0);
        //stop timer
        TCCR1B &= ~(1<<CS12); 
        TCCR1B &= ~(1<<CS10);
    }
     
    count++;
}

int main(void) {

    sonic_Init();
    moist_Init();  
    USART_Init();
    buzzer_Init();
    button_Init();
    // Display
    SPI_init();
    Display_init();
    
    uint8_t buttonFlag=0;
    uint8_t trash;

    
//    
//    for(uint16_t i= 0; i < (176*132); i++)
//    {
//       SPISend8Bit(0x00); // SCHWARZ 0x0000
//       SPISend8Bit(0x00); // SCHWARZ 0x0000
//    }
//    
   
    
 //   drawStatus();   
    uint8_t critical = 180;
	
	while (1)
	{
        //displayPlant(ADCH);   

        //ADC ist im Autotrigger mode, man muss nur warten bis ein ergebnis da ist.
        while(!(ADCSRA & (1<<ADSC))){
        
        };

        //Testkrams
        USART_TransmitPolling(0xAA);
        trash= ADCL;        //es sollen immer beide Werte ausgelesen werden
        USART_TransmitPolling(ADCH);

        
 //       Prototype programmablauf
        if(BUTTON1_PRESS)   //activate Long Sleep Timer, kein Entprellen n�tig
        {   
            sleepLongFlag = 1;
            drawSleepStatus(1);
            startSleepTimer();
        }
        if(BUTTON2_PRESS && buttonFlag ==0)   //activate Long Sleep Timer, kein Entprellen n�tig
        {
            buttonFlag = 1;
            _delay_ms(64);      //mit delay gel�st da alle TImer schon beelgt waren 
            //timer 1 wird fuer den SleepTimer gebraucht. Dieser k�nnte abgebrochen werden wenn waehrendessen der button gedrueckt wird
            //Timer 0&2 werden fuer den buzzer gebraucht, k�nnte diesen durcheinander brigne  wenn waehrendessen der button gedrueckt wird
            // besser microcontroller wird hier kurz blockiert anstatt f�r die ganze melodyspielzeit0
            if(BUTTON2_PRESS)   //activate Long Sleep Timer, kein Entprellen n�tig
            {   
                melodyPicker++;
                if(melodyPicker >2)
                {
                        melodyPicker=0;
                }
                drawMelodyStatus(melodyPicker);
            }
        }
        if(!BUTTON2_PRESS)
        {
            buttonFlag = 0;
        }
 
        if(sleepFlag == 0 && sleepLongFlag == 0){
            if(ADCH > critical)
            {
                if(sonic_burst() != 0)
                {
                    play_sound(melodyPicker);
                    sleepFlag = 1;
                    startSleepTimer();
                }
            }
        }
    }
    return 0;
}
