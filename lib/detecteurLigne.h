#pragma once
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h> 
#include "Sonnerie.h"
#include "Moteur.h"
#include "can.h"
#include "Del.h"



class DetecteurLigne
{
public :

    DetecteurLigne() ;

    ~DetecteurLigne();

    void detecterLigne();

    bool getMoteurArrete();

    void setMoteurArrete(bool valeure);

    bool getPoint_S() ;

    bool getPoint_B() ;

    bool getDoublechemin();

private :


    void masquerEntree();
    const uint8_t modeEntree = 0x00 ;
    Moteur moteur ;
    Del del ;
    bool point_S_ =false;
    bool point_B_ = false;
    const uint8_t masque = 0x1f ;
    uint8_t entree ;
    bool doubleChemin = false ;

    uint8_t virage = 0 ;




};