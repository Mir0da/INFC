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

#define BUTTON1_PRESS (!(PIND & (1<<PIND1)))
#define BUTTON2_PRESS (!(PINB & (1<<PINB1)))

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
        LED_OFF;
        sleepFlag=0;
        count = 0;
        //stop timer
        TCCR1B &= ~(1<<CS12); 
        TCCR1B &= ~(1<<CS10);
    }
    if(count > 5 && sleepLongFlag == 1)  //72 für ~ 5min
    {
        sleepFlag=0;
        sleepLongFlag = 0;
        count = 0;
        LED_OFF;
//      SendCommandSeq(windowSleep,6);
//    
//          for(uint16_t i= 0; i < (166*122); i++)
//           {
//               SPISend8Bit(0x00); // WEISS 0x07EF
//               SPISend8Bit(0x00); // WEISS 0x07EF
//            }
        //stop timer
        TCCR1B &= ~(1<<CS12); 
        TCCR1B &= ~(1<<CS10);
    }
     
    count++;
}

void button_Init(){
    //Button 1 for long Sleep Timer
    DDRD &= ~(1<< DDD1);   //Button input 
    PORTD |= (1<<PORTD1); //enable pull-up 
    
    //Button 2 for Melody Change?
    DDRB &= ~(1<< DDB1);   //Button input 
    PORTB |= (1<<PORTB1); //enable pull-up 
}

int main(void) {

    //sonic_Init();
    moist_Init();  
    USART_Init();
    //buzzer_Init();
    //button_Init();
    // Display
    //SPI_init();
    //Display_init();
    
    uint8_t buttonFlag=0;
    uint8_t trash;

//    uint16_t windowAnimation[] ={
//        0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
//        0x127E, 0x1505, 0x1305, 0x16AA //Werte fï¿½r Fenstergrï¿½ï¿½e, xAnfang (0x1267), xEnde, yStart, yEnde (0x169D)       
//	};
    
    //    uint16_t windowStatus[] ={
//        0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
//        0x127E, 0x1505, 0x1305, 0x16AA //Werte fï¿½r Fenstergrï¿½ï¿½e, xAnfang (0x1267), xEnde, yStart, yEnde (0x169D)       
//	};
    
//    uint16_t windowSleep[] ={
//        0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
//        0x127E, 0x1505, 0x1305, 0x16AA //Werte fï¿½r Fenstergrï¿½ï¿½e, xAnfang (0x1267), xEnde, yStart, yEnde (0x169D)       
//	};
//    uint16_t windowMelody0[] ={
//        0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
//        0x127E, 0x1505, 0x1305, 0x16AA //Werte fï¿½r Fenstergrï¿½ï¿½e, xAnfang (0x1267), xEnde, yStart, yEnde (0x169D)       
//	};
//    
//    uint16_t windowMelody1[] ={
//        0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
//        0x127E, 0x1505, 0x1305, 0x16AA //Werte fï¿½r Fenstergrï¿½ï¿½e, xAnfang (0x1267), xEnde, yStart, yEnde (0x169D)       
//	};
//    
//    uint16_t windowMelody2[] ={
//        0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
//        0x127E, 0x1505, 0x1305, 0x16AA //Werte fï¿½r Fenstergrï¿½ï¿½e, xAnfang (0x1267), xEnde, yStart, yEnde (0x169D)       
//	};
    
//    
//    for(uint16_t i= 0; i < (176*132); i++)
//    {
//       SPISend8Bit(0x00); // SCHWARZ 0x0000
//       SPISend8Bit(0x00); // SCHWARZ 0x0000
//    }
//    
//    SendCommandSeq(window,6);
//    
//    for(uint16_t i= 0; i < (166*122); i++)
//    {
//       SPISend8Bit(0xFF); // WEISS 0x07EF
//       SPISend8Bit(0xFF); // WEISS 0x07EF
//    }
//    
//    //sendPic(Bild1); //funktioniert!
//    
//    uint8_t critical = 150;
	
	while (1)
	{
        //displayPlant(ADCH);   
        
        //ohne Autotrigger funktioniert
        ADCSRA |= (1<<ADSC);    //start conversion

        //ADC ist im Autotrigger mode, man muss nur warten bis ein ergebnis da ist.
        //kï¿½nnten wir auch seltener abfragen, ï¿½ber Timer steuern wann die conversion gestartet wird
        while(!(ADCSRA & (1<<ADSC))){
        
        };
        
        //mit Interrupt enable fï¿½r ADC kommt IRGENDWAS beim Uart an
        USART_TransmitPolling(0xAA);
        trash= ADCL;        //es sollen immer beide Werte ausgelesen werden
        USART_TransmitPolling(ADCH);
        
        _delay_ms(500);
        
        //Prototype programmablauf
//        if(BUTTON1_PRESS)   //activate Long Sleep Timer, kein Entprellen nötig
//        {   
//            sleepLongFlag = 1;
//            LED_ON;
////          SendCommandSeq(windowSleep,6);
////    
////          for(uint16_t i= 0; i < (166*122); i++)
////           {
////               SPISend8Bit(0x55); //
////               SPISend8Bit(0x27); //
////            }
//            startSleepTimer();
//        }
//        if(BUTTON2_PRESS && buttonFlag ==0)   //activate Long Sleep Timer, kein Entprellen nötig
//        {
//            buttonFlag = 1;
//            _delay_ms(64);      //mit delay gelöst da alle TImer schon beelgt waren 
//            //timer 1 wird für den SleepTimer gebraucht. Dieser könnte abgebrochen werden wenn währendessen der button gedrückt wird
//            //Timer 0&2 werden für den buzzer gebraucht, könnte diesen durcheinander brigne  wenn währendessen der button gedrückt wird
//            // besser microcontroller wird hier kurz blockiert anstatt für die ganze melodyspielzeit0
//            if(BUTTON2_PRESS)   //activate Long Sleep Timer, kein Entprellen nötig
//            {   
//                melodyPicker++;
//                if(melodyPicker >2)
//                {
//                        melodyPicker=0;
//                }
//                
////                  SendCommandSeq(windowMelody0,6);
////    
////                  for(uint16_t i= 0; i < (166*122); i++)
////                  {
////                      SPISend8Bit(0x00); //
////                      SPISend8Bit(0x00); //
////                  }
//                    
////                  SendCommandSeq(windowMelody1,6);
////    
////                  for(uint16_t i= 0; i < (166*122); i++)
////                  {
////                      SPISend8Bit(0x00); //
////                      SPISend8Bit(0x00); //
////                  }
//                    
////                  SendCommandSeq(windowMelody2,6);
////    
////                  for(uint16_t i= 0; i < (166*122); i++)
////                  {
////                      SPISend8Bit(0x00); //
////                      SPISend8Bit(0x00); //
////                  }      
//                if(melodyPicker == 0)
//                {
////                  SendCommandSeq(windowMelody0,6);
////    
////                  for(uint16_t i= 0; i < (166*122); i++)
////                  {
////                      SPISend8Bit(0x55); //
////                      SPISend8Bit(0x27); //
////                  }      
//                }
//                if(melodyPicker == 1)
//                {
////                  SendCommandSeq(windowMelody1,6);
////    
////                  for(uint16_t i= 0; i < (166*122); i++)
////                  {
////                      SPISend8Bit(0x55); //
////                      SPISend8Bit(0x27); //
////                  }      
//                }
//                if(melodyPicker == 2)
//                {
////                  SendCommandSeq(windowMelody2,6);
////    
////                  for(uint16_t i= 0; i < (166*122); i++)
////                  {
////                      SPISend8Bit(0x55); //
////                      SPISend8Bit(0x27); //
////                  }      
//                }
//            }
//        }
//        if(!BUTTON2_PRESS)
//        {
//            buttonFlag = 0;
//        }
// 
//        if(sleepFlag == 0 && sleepLongFlag == 0){
//           // if(ADCH > critical)
//           // {
//                if(sonic_burst() != 0)
//                {
//                    play_sound(melodyPicker);
//                    sleepFlag = 1;
//                    startSleepTimer();
//                }
//            //}
//        }
    }
    return 0;
}
