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
#include <memoire_24.h>


class Robot {
public :
    Robot();

    ~Robot();

    void partieA();

    void partieB();

    void partieC();

    void stationnement();

    

    

private :

    //void stationner();

    uint8_t* retournerTab() ;

    void ecrireTabMem(uint8_t* tableau);

    uint8_t* lectureTabMem();

    void partirMinuterie();

    void initialisation( void );

    DetecteurLigne detecteurLigne_ ;
    Moteur moteur_ ;
    int duree = 3906;
    Memoire24CXXX memoire ;

};
