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

    void detecterLigne2();

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
    // void lireCapteur() ;
    // uint8_t capteur1 = (PINC & 16);
    // uint8_t capteur2 = (PINC & 8) ;
    // uint8_t capteur3 = (PINC & 4) ;
    // uint8_t capteur4 = (PINC & 2) ;
    // uint8_t capteur5 = (PINC & 1) ;
    // uint8_t delCompteur = 0 ;


};