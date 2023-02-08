#pragma once
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


class Minuterie
{
public :

    Minuterie();

    ~Minuterie();


    void initMinuterie(uint8_t duree);

    void finMinuterie();

    void set_MinuterieExpiree(uint8_t valeur);

private :

    volatile uint8_t MinuterieExpiree_ ;

};