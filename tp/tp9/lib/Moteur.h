#pragma once
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h> 
class Moteur 
{
public :

    Moteur();

    ~Moteur();


    void changementVitesse(uint16_t duree1, uint16_t duree2);

    void avancerMoteur(uint16_t duree1, uint16_t duree2);

    void reculerMoteur(uint16_t duree1, uint16_t duree2);

    void arreterMoteur();

    void tournerDroite90();

    void tournerGauche90();

private:
    
    const uint8_t min_ = 255;
    const uint8_t max_ = 0;

};