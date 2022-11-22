#pragma once 
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include "can.h"
#include "Del.h"


class Photoresistance 
{
    public : 
        Photoresistance();

        ~Photoresistance();
        

        void chargerEntree() ;

        void affichage();

    private :

    volatile uint8_t lumiereNum;

};