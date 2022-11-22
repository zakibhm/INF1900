#pragma once
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h> 
class Moteur 
{
public :

    Moteur();

    ~Moteur();


    

    void avancerMoteur();

    void reculerMoteur();

    void arreterMoteur();

    void tournerDroite90();

    void tournerGauche90();

private:
    void changementVitesse(uint16_t duree1, uint16_t duree2);
    
    const uint8_t min_ = 90;
    const uint8_t max_ = 0;

};