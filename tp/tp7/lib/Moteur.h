#pragma once
#define F_CPU 8000000
#include <avr/io.h>

class Moteur 
{
public :

    Moteur();

    ~Moteur();


    void changementVitesse(uint16_t duree1, uint16_t duree2);

    void avancerMoteur(uint16_t duree1, uint16_t duree2);

    void reculerMoteur(uint16_t duree1, uint16_t duree2);

};