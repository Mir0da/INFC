/*
 * File:   sonic.h
 * Author: sophi
 *
 * Created on 28. Dezember 2022, 15:44
 */


#ifndef SONIC_H_ 
 #define SONIC_H_ 

  
  
 #define SONIC_TRIGGER                        DDB4 
 #define SONIC_ECHO                           DDB0 
  
 #define DDR_SONIC                            DDRB 
 #define PORT_SONIC                           PORTB 
 #define PIN_SONIC                            PINB 
  
 #define SONIC_TRIGGER_HIGH                PORT_SONIC |= (1<<SONIC_TRIGGER) 
 #define SONIC_TRIGGER_LOW                 PORT_SONIC &= ~(1<<SONIC_TRIGGER) 
  
 void init_sonic(); 
 void sonic_trigger_burst(); 
  
 #endif /* SONIC_H_ */
