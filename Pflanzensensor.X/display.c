/* Based on code by Michael Behrens */

#include "display.h"
#include "picture.h"

void SPI_init(){
	//set CS, MOSI and SCK to output:
	SPI_DDR |= (1 << CS) | (1 << MOSI) | (1 << SCK);

	//enable SPI, set as master, and clock to fosc/4:
	SPCR = (1 << SPE) | (1 << MSTR);
}

void SPISend8Bit(uint8_t data){
	PORTB &= ~(1<<CS);				//CS low = active
	SPDR = data;					//load data into register
	while(!(SPSR & (1 << SPIF)));	//wait for transmission complete
    //SPIF wird gesetzt wenn �bertragung abgeschlossen ist
    //solang das SPIF (Interrupt Flag) 0 ist, ist die �bertragung nicht abgeschlossen, also in While schleife bleiben/warten
	PORTB |= (1<<CS);				//CS high = inactive
}

void SendCommandSeq(const uint16_t * data, uint16_t Anzahl){
	uint16_t index;
	uint8_t SendeByte;
	for (index=0; index<Anzahl; index++){
		PORTD |= (1<<D_C);						//Data/Command auf High => Kommando-Modus
		SendeByte = (data[index] >> 8) & 0xFF;	//High-Byte des Kommandos 0xFF=11111111 aber eig unn�tig
        //sendet das MSB bzw die linken 8 Bits des 16Bit Wortes data[index]
		SPISend8Bit(SendeByte);
		SendeByte = data[index] & 0xFF;			//Low-Byte des Kommandos
        //sendes das LSB, bzw die rechten 6 Bits des 16Bit Wortes data[index]
		SPISend8Bit(SendeByte);
		PORTD &= ~(1<<D_C);						//Data/Command auf Low => Daten-Modus
	}
}

void Display_init(void) {
    DDRD |= (1<<D_C)|(1<<Reset);		//output: PD2 -> Data/Command; PD3 -> Reset
    
	const uint16_t InitData[] ={
		//Initialisierungsdaten fuer 16Bit-Farben-Modus
		0xFDFD, 0xFDFD,
		/* pause */
		0xEF00, 0xEE04, 0x1B04, 0xFEFE, 0xFEFE,
		0xEF90, 0x4A04, 0x7F3F, 0xEE04, 0x4306, //0x7F3F, 3F f�r 16 Bit Farbmodus
		/* pause */
		0xEF90, 0x0983, 0x0800, 0x0BAF, 0x0A00,
		0x0500, 0x0600, 0x0700, 0xEF00, 0xEE0C,
		0xEF90, 0x0080, 0xEFB0, 0x4902, 0xEF00,
		0x7F01, 0xE181, 0xE202, 0xE276, 0xE183,
		0x8001, 0xEF90, 0x0000,
        /*pause*/
        0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
        0x1200, 0x1300, 0x15AF, 0x1683 //Werte f�r Fenstergr��e, xAnfang, yAnfang, xEnde, yEnde
	};
	
	_delay_ms(300);
	PORTD &= !(1<<Reset);			//Reset-Eingang des Displays auf Low => Beginn Hardware-Reset
	_delay_ms(75);
	PORTB |= (1<<CS);				//SSEL auf High
	_delay_ms(75);
	PORTD |= (1<<D_C);				//Data/Command auf High
	_delay_ms(75);
	PORTD |= (1<<Reset);			//Reset-Eingang des Displays auf High => Ende Hardware Reset
	_delay_ms(75);
	SendCommandSeq(&InitData[0], 2);
	_delay_ms(75);
	SendCommandSeq(&InitData[2], 10);
	_delay_ms(75);
	SendCommandSeq(&InitData[12], 23);
}

void sendPic(const __flash int picture[], int count){
    int wert, wiederholung;
    uint16_t  counter=0;
    uint8_t SendeByte;
    
    
    while(counter < count){
        wert= picture[counter];
        
        if(wert == picture[counter+1]){
            wiederholung=picture[counter+2];
            counter += 3;
        }
        else{
            wiederholung= 1;
            counter += 1;
        }
        
        for(int i=0x00; i<wiederholung; i++){
            SendeByte = (wert >> 8) & 0xFF;	//High-Byte des 16 Bit Wertes
            SPISend8Bit(SendeByte);
            SendeByte = wert & 0xFF; //Low-Byte des 16Bit Wertes
            SPISend8Bit(SendeByte);
        }  
    }   
}

void displayPlant(uint8_t advalue){
    SendCommandSeq(plantwindow,6);
    static uint8_t changeFlag = 0;
    
    if(advalue < 140){                      //WELL
        if(changeFlag == 0)
        {
            sendPic(Bild1,2085);
            changeFlag=1;
        }
        else
        {
            sendPic(Bild1Animated,2025);
            changeFlag=0;
        }
    }
    
    if(advalue < 180 && advalue > 140){     //MEDIOCRE
       
        if(changeFlag == 0)
        {
             sendPic(Bild2,1929);
            changeFlag=1;
        }
        else
        {
            sendPic(Bild2Animated,1869);
            changeFlag=0;
        }
    }
    if(advalue > 180){                      //BAD

        if(changeFlag == 0)
        {
            sendPic(Bild3,1978);
            changeFlag=1;
        }
        else
        {
            sendPic(Bild3Animated,1908);
            changeFlag=0;
        }
    }
}

void drawStatus(){
    SendCommandSeq(statuswindow,6);
    sendPic(Status,891);
}

void drawMelodyStatus(uint8_t melodyPicker){
        
      SendCommandSeq(melody0window,6);

      for(uint16_t i= 0; i < (11*11); i++)
      {
          SPISend8Bit(0x00); // schwarz
          SPISend8Bit(0x00); // schwarz
      }

      SendCommandSeq(melody1window,6);

      for(uint16_t i= 0; i < (11*11); i++)
      {
          SPISend8Bit(0x00); // schwarz
          SPISend8Bit(0x00); // schwarz
      }

      SendCommandSeq(melody2window,6);

      for(uint16_t i= 0; i < (11*11); i++)
      {
          SPISend8Bit(0x00); // schwarz
          SPISend8Bit(0x00); // schwarz
      }      
    if(melodyPicker == 0)
    {
      SendCommandSeq(melody0window,6);
      
    }
    if(melodyPicker == 1)
    {
      SendCommandSeq(melody1window,6);
      
    }
    if(melodyPicker == 2)
    {
      SendCommandSeq(melody2window,6);
    
    }
      
    //for schleife aus den einzelnen if abfragen genommen und 1x am Ende eingef�gt um Wiederholung zu vermeiden.
    for(uint16_t i= 0; i < (11*11); i++)
      {
          SPISend8Bit(0x55); // gr�n
          SPISend8Bit(0x27); // gr�n
      }  

}

void drawSleepStatus(uint8_t sleep){
       SendCommandSeq(sleepwindow,6);
    
    if(sleep == 0)
    {
          for(uint16_t i= 0; i < (11*11); i++)
           {
               SPISend8Bit(0x00); // schwarz
               SPISend8Bit(0x00); // schwarz
            }
    }
    else
    {
          for(uint16_t i= 0; i < (11*11); i++)
           {
               SPISend8Bit(0x55); // gr�n
               SPISend8Bit(0x27); // gr�n
            }
    }

}
