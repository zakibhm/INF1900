#pragma once
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h> 
#include "Sonnerie.h"
#include "Moteur.h"
#include "can.h"
#include "Del.h"
#include "DetecteurDistance.h"
#include "detecteurLigne.h"
#include <avr/interrupt.h>
#include "memoire_24.h"


class Robot {
public :
    Robot();

    ~Robot();

    void pariteA();

    void partieB();

    void partieC();

    

    

private :

    uint8_t* retournerTab() ;

    void ecrireTabMem(uint8_t* tableau);

    uint8_t* lectureTabMem();

    void partirMinuterie();

    void initialisation( void );




    DetecteurDistance detecteurDistance_ ;
    DetecteurLigne detecteurLigne_ ;
    Moteur moteur_ ;
    int duree = 3906;
    //Memoire24CXXX memoire ;

};
