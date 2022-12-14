/* Based on code by Michael Behrens */

#include "display.h"

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
    //SPIF wird gesetzt wenn Übertragung abgeschlossen ist
    //solang das SPIF (Interrupt Flag) 0 ist, ist die übertragung nicht abgeschlossen, also in While schleife bleiben/warten
	PORTB |= (1<<CS);				//CS high = inactive
}

void SendCommandSeq(const uint16_t * data, uint16_t Anzahl){
	uint16_t index;
	uint8_t SendeByte;
	for (index=0; index<Anzahl; index++){
		PORTD |= (1<<D_C);						//Data/Command auf High => Kommando-Modus
		SendeByte = (data[index] >> 8) & 0xFF;	//High-Byte des Kommandos 0xFF=11111111 aber eig unnötig
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
		0xEF90, 0x4A04, 0x7F3F, 0xEE04, 0x4306, //0x7F3F, 3F für 16 Bit Farbmodus
		/* pause */
		0xEF90, 0x0983, 0x0800, 0x0BAF, 0x0A00,
		0x0500, 0x0600, 0x0700, 0xEF00, 0xEE0C,
		0xEF90, 0x0080, 0xEFB0, 0x4902, 0xEF00,
		0x7F01, 0xE181, 0xE202, 0xE276, 0xE183,
		0x8001, 0xEF90, 0x0000,
        /*pause*/
        0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
        0x1200, 0x1300, 0x15AF, 0x1683 //Werte für Fenstergröße, xAnfang, yAnfang, xEnde, yEnde
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

void sendPic(const __flash int picture[]){
    int wert, wiederholung;
    uint16_t  counter=0;
    uint8_t SendeByte;
    
    
    while(counter < 2316){
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
