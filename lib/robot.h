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


class Robot {
public :
    Robot();

    ~Robot();

    void pariteA();

    void partieB();

    void partieC();

    void partirMinuterie();

    void initialisation( void );

private :
    int* retournerTab() ;
    DetecteurDistance detecteurDistance_ ;
    DetecteurLigne detecteurLigne_ ;
    Moteur moteur_ ;
    int duree = 7500;

};
