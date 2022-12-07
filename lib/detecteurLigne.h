#pragma once
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h> 
#include "Sonnerie.h"
#include "Moteur.h"
#include "can.h"
#include "Del.h"
#include "Uart.h"
#include "memoire_24.h"



class DetecteurLigne
{
public :

    DetecteurLigne() ;

    ~DetecteurLigne();

    void detecteurDistance() ;

    void detecterLigne(char* partie,char* direction);

    //void detecterLigne2();

    bool getMoteurArrete();

    void setMilieu(bool valeure);

    bool getPoint_S() ;

    void setPoint_S(bool valeure) ;

    bool getPoint_B() ;

    bool getDoublechemin();

    bool getMilieu();

    uint8_t* getTabBarrieres();

    void setDoublechemin(bool var);

    void detecterGauche(bool push, char* partie);

    void detecterDroite(bool push, char* partie);

    void detecterZigZag();
 
private :

    void detecterGauche90(char* partie,char* direction);

    void detecterDroite90(char* partie,char* direction);

    void verifierDoubleChemin();
    
    void masquerEntree();

    const uint8_t modeEntree = 0x00 ;
    Moteur moteur ;
    Del del ;
    bool point_S_ =false;
    bool point_B_ = false;
    const uint8_t masque = 0x1f ;
    uint8_t entree ;
    bool doubleChemin = false ;
    bool milieu =  false ;

    Son sonnerie;
    Memoire24CXXX memoire_ ;
    uint16_t adresse = 0x0000;
    can convertisseurAnalogique ; 
    uint8_t tableaux_des_barrieres[3]={0,0,0};
    uint8_t distance ;
    uint8_t compteurBarr_ = 0;
    double frequence[37] {
    110,116.54,123.47,130.81,138.59,146.83,
    155.56,164.81,174.61,185.00,196.00,207.65,
    220,233.08,246.94,261.63,277.18,293.66,311.13,
    329.63,349.23,369.99,392.00,415.30,440,466.16,
    493.88,523.25,554.37,587.33,622.25,659.26,698.46,
    739.99,783.99,830.61,880
    };



};