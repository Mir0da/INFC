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
    if(count > 5 && sleepLongFlag == 1)  //72 f�r ~ 5min
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

//    uint16_t plantwindow[] ={
//        0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
//        0x1269, 0x1505, 0x1305, 0x16AA //Werte fuer Fenstergroesse, xEnde(106), xAnfang(6), yStart(6), yEnde (171)       
//	};
//    uint16_t statuswindow[] ={
//        0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
//        0x127E, 0x156A, 0x1305, 0x16AA //Werte fuer Fenstergroesse, xEnde(127), xAnfang(107), yStart(6), yEnde (171)       
//	};
//    uint16_t sleepwindow[] ={
//        0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
//        0x1279, 0x156F, 0x1341, 0x164B //Werte fuer Fenstergroesse, xEnde(122), xAnfang(112), yStart(66), yEnde (76)       
//	};
//    uint16_t melody1window[] ={
//        0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
//        0x1279, 0x156F, 0x1373, 0x167D //Werte fuer Fenstergroesse, xEnde(122), xAnfang(112), yStart(116), yEnde (126)       
//	};
//    uint16_t melody2window[] ={
//        0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
//        0x1279, 0x156F, 0x1385, 0x168F //Werte fuer Fenstergroesse, xEnde(122), xAnfang(112), yStart(134), yEnde (144)       
//	};
//    uint16_t melody3window[] ={
//        0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
//        0x1279, 0x156F, 0x1397, 0x16A1 //Werte fuer Fenstergroesse, xEnde(122), xAnfang(112), yStart(152), yEnde (162)       
//	};
    
    
//    
//    for(uint16_t i= 0; i < (176*132); i++)
//    {
//       SPISend8Bit(0x00); // SCHWARZ 0x0000
//       SPISend8Bit(0x00); // SCHWARZ 0x0000
//    }
//    
//    SendCommandSeq(plantwindow,6);
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
        //k�nnten wir auch seltener abfragen, �ber Timer steuern wann die conversion gestartet wird
        while(!(ADCSRA & (1<<ADSC))){
        
        };
        
        //mit Interrupt enable f�r ADC kommt IRGENDWAS beim Uart an
        USART_TransmitPolling(0xAA);
        trash= ADCL;        //es sollen immer beide Werte ausgelesen werden
        USART_TransmitPolling(ADCH);
        
        _delay_ms(500);
        
        //Prototype programmablauf
//        if(BUTTON1_PRESS)   //activate Long Sleep Timer, kein Entprellen n�tig
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
//        if(BUTTON2_PRESS && buttonFlag ==0)   //activate Long Sleep Timer, kein Entprellen n�tig
//        {
//            buttonFlag = 1;
//            _delay_ms(64);      //mit delay gel�st da alle TImer schon beelgt waren 
//            //timer 1 wird f�r den SleepTimer gebraucht. Dieser k�nnte abgebrochen werden wenn w�hrendessen der button gedr�ckt wird
//            //Timer 0&2 werden f�r den buzzer gebraucht, k�nnte diesen durcheinander brigne  wenn w�hrendessen der button gedr�ckt wird
//            // besser microcontroller wird hier kurz blockiert anstatt f�r die ganze melodyspielzeit0
//            if(BUTTON2_PRESS)   //activate Long Sleep Timer, kein Entprellen n�tig
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
