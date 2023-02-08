#include "Minuterie.h"

Minuterie::Minuterie()
{}

Minuterie::~Minuterie()
{}

void Minuterie::set_MinuterieExpiree(uint8_t valeur)
{
    MinuterieExpiree_= valeur ;
}

void Minuterie::initMinuterie(uint8_t duree)
{
   
    // mode CTC du timer 1 avec horloge divisée par 1024

    // interruption après la durée spécifiée

    MinuterieExpiree_ = 0;

    TCNT1 = 0 ;

    OCR1A = duree;

    TCCR1A = 0 ;

    TCCR1B |= (1<<CS12)|(1<<CS10)|(1<<WGM12);

    TCCR1C = 0;

    TIMSK1 = (1<<OCIE1A) ;

}
void Minuterie::finMinuterie()
{
    TCCR1B &= ~((1<<CS12)|(1<<CS10));//pas de source d'horloge "0 - 0 - 0"
}