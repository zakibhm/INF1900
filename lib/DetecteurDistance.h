#pragma once
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h> 
#include "Sonnerie.h"
#include "Moteur.h"
#include "Uart.h"
#include "can.h"
#include "Del.h"
class DetecteurDistance
{
public :

    DetecteurDistance();

    ~DetecteurDistance();

    void detecterBar() ;
    
    int* getTabBarrieres();

    

private:
    const uint8_t modeEntree = 0x00 ;
    const uint8_t modeSortie = 0xff ;
    Moteur moteur;
    Son sonnerie;
    Del del ;
    can convertisseurAnalogique ; 
    int tableaux_des_barrieres[3]={0,0,0};
    uint8_t distance ;
    uint8_t conteurBarr = 0;
    double frequence[37] {
    110,116.54,123.47,130.81,138.59,146.83,
    155.56,164.81,174.61,185.00,196.00,207.65,
    220,233.08,246.94,261.63,277.18,293.66,311.13,
    329.63,349.23,369.99,392.00,415.30,440,466.16,
    493.88,523.25,554.37,587.33,622.25,659.26,698.46,
    739.99,783.99,830.61,880
    };

};