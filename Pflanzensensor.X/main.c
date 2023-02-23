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

volatile uint8_t sleepFlag = 0;
volatile uint8_t sleepLongFlag = 0;
volatile uint8_t melodyPicker = 0;
volatile uint8_t animateCounter = 0;
volatile uint8_t adVal = 0;
 
void startControlTimer(){
    //reset everything
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;
    TIFR1 = 0;
    TCNT1 = 0;	///Clear Timer counter
    
    //configure Timer for 1sec
    TCCR1A = 0;
    TCCR1B |= (1<<WGM12);       //CTC Mode
    TCCR1B |= (1<<CS12) | (1<<CS10);    //Prescaler 1024
    TCCR1C |= (1<<FOC1B);       //enable B Match Interrupt
    TIMSK1 |= (1<<OCIE1B);      //enable B Match Interrupt
    OCR1A= 15625; //1 sec
}

ISR(TIMER1_COMPB_vect)
{
	static volatile uint16_t sleepCount = 0;
 
    if(sleepCount > 5 && sleepLongFlag == 0 && sleepFlag == 1) 
    {
        sleepFlag=0;
        sleepCount = 0;
    }
    if(sleepCount > 300 && sleepLongFlag == 1)  //300 sec = 5 min
    {
        sleepFlag=0;
        sleepLongFlag = 0;
        sleepCount = 0;
        drawSleepStatus(0);
    }
     
    displayPlant(adVal); 
    if(sleepLongFlag == 1 || sleepFlag == 1)
    {
        sleepCount++;
    }
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
    uint8_t trash = 0;
    uint8_t critical = 180;
   

    
    for(uint16_t i= 0; i < (176*132); i++)
    {
       SPISend8Bit(0x00); // SCHWARZ 0x00
       SPISend8Bit(0x00); // SCHWARZ 0x00
    }
    
   
    
    drawStatus();   
    //startControlTimer();
	
	while (1)
	{
        
        //ADC ist im Autotrigger mode, man muss nur warten bis ein ergebnis da ist.
        while(!(ADCSRA & (1<<ADSC))){
        
        };
         
        
        trash= ADCL;        //es sollen immer beide Werte ausgelesen werden
        adVal=ADCH;
        //Test, Wert des AD Wandlers ausgeben
        //USART_TransmitPolling(ADCH);
        
 //       Prototype programmablauf
        if(BUTTON1_PRESS)   //activate Long Sleep Timer, kein Entprellen nötig
        {   
            sleepLongFlag = 1;
            drawSleepStatus(1);
            startControlTimer();
        }
        if(BUTTON2_PRESS && buttonFlag ==0)  
        {
            buttonFlag = 1;
            _delay_ms(64);      //mit delay gelï¿½st da alle TImer schon beelgt waren 
            //timer 1 wird fuer den SleepTimer gebraucht. Dieser kï¿½nnte abgebrochen werden wenn waehrendessen der button gedrueckt wird
            //Timer 0&2 werden fuer den buzzer gebraucht, kï¿½nnte diesen durcheinander brigne  wenn waehrendessen der button gedrueckt wird
            // besser microcontroller wird hier kurz blockiert anstatt fï¿½r die ganze melodyspielzeit0
            if(BUTTON2_PRESS)  
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
                    startControlTimer();
                }
            }
        }
    }
    return 0;
}
