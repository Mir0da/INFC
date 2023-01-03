
#ifndef PICTURE_H_
#define PICTURE_H_

extern const __flash int Bild1[2301];
extern const __flash int Bild1Animated[2085];

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
    0x1279, 0x156F, 0x1341, 0x164B //Werte fuer Fenstergroesse, xEnde(122), xAnfang(112), yStart(66), yEnde (76)       
};
uint16_t melody1window[] ={
    0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
    0x1279, 0x156F, 0x1373, 0x167D //Werte fuer Fenstergroesse, xEnde(122), xAnfang(112), yStart(116), yEnde (126)       
};
uint16_t melody2window[] ={
    0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
    0x1279, 0x156F, 0x1385, 0x168F //Werte fuer Fenstergroesse, xEnde(122), xAnfang(112), yStart(134), yEnde (144)       
};
uint16_t melody3window[] ={
    0xEF08, 0x1805, //Initialisierungsstart, Landscape Modus
    0x1279, 0x156F, 0x1397, 0x16A1 //Werte fuer Fenstergroesse, xEnde(122), xAnfang(112), yStart(152), yEnde (162)       
};

#endif /* PICTURE_H_ */