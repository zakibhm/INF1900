#include "Sonnerie.h"



Son::Son()
{
    DDRD |= (1<<PD7) | (1 << PD6);
    PORTD &= ~(1<<PD6);
    TCCR2A |= (1<< WGM21) | (1<<COM2A0);//mode CTC
    TCCR2B |= (1<<CS22) ;// prescalaire de 256
    TCNT2 =0 ;
}

Son::~Son()
{}


void Son::jouerSon(double frequence)
    {
        OCR2A= ((8000000 / (2* 256 * frequence))-1);//deviser la vitesse du microprocesseur sur un prescalaire de 256
    }

void Son::arreterSon()
{
    OCR2A = 0 ;
}