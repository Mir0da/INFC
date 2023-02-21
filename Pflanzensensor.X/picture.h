
#ifndef PICTURE_H_
#define PICTURE_H_

extern const __flash int Bild1[2085];
extern const __flash int Bild1Animated[2025];
extern const __flash int Bild2[1929];
extern const __flash int Bild2Animated[1869];
extern const __flash int Bild3[1978];
extern const __flash int Bild3Animated[1908];
extern const __flash int Status[891];

uint16_t plantwindow[] ={
    0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
    0x1269, 0x1505, 0x1305, 0x16AA //Werte fuer Fenstergroesse, xEnde(106), xAnfang(6), yStart(6), yEnde (171)       
};
uint16_t statuswindow[] ={
    0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
    0x127E, 0x156A, 0x1305, 0x16AA //Werte fuer Fenstergroesse, xEnde(127), xAnfang(107), yStart(6), yEnde (171)       
};
uint16_t sleepwindow[] ={
    0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
    0x127C, 0x1572, 0x1342, 0x164C //Werte fuer Fenstergroesse, xEnde(125), xAnfang(115), yStart(67), yEnde (77)       
};
uint16_t melody0window[] ={
    0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
    0x127C, 0x1572, 0x1374, 0x167E //Werte fuer Fenstergroesse, xEnde(125), xAnfang(115), yStart(117), yEnde (127)       
};
uint16_t melody1window[] ={
    0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
    0x127C, 0x1572, 0x1386, 0x1690 //Werte fuer Fenstergroesse, xEnde(125), xAnfang(115), yStart(135), yEnde (145)       
};
uint16_t melody2window[] ={
    0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
    0x127C, 0x1572, 0x1398, 0x16A2 //Werte fuer Fenstergroesse, xEnde(125), xAnfang(115), yStart(153), yEnde (163)       
};

#endif /* PICTURE_H_ */