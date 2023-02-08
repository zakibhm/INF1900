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

    void avancerMoteur(uint16_t duree1, uint16_t duree2);

    void reculerMoteur();

    void reculerMoteur(uint16_t duree1, uint16_t duree2) ;

    void arreterMoteur();

    void tournerDroite90();

    void tournerGauche90();

    void tournerGauche();

    void tournerDroite();

    void tournerGauche(uint16_t duree1, uint16_t duree2);

    void tournerDroite(uint16_t duree1, uint16_t duree2);

private:
    void changementVitesse(uint16_t duree1, uint16_t duree2);
    
    const uint8_t min_ = 100; //57
    const uint8_t max_ = 0;

};