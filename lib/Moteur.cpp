#include "Moteur.h"

Moteur::Moteur()
{
    DDRD |= (1 << PD2) | (1<< PD3)| (1 << PD4) | (1<< PD5);
    TCCR1A |=(1<<WGM10) |(1<<COM1A1)|(1<<COM1B1) ;//|(1<<COM1A0)|(1<<COM1B0);
    TCCR1B |= (1<<CS11)  | (0 << CS10) | (0 << CS12);
    TCCR1C = 0;
}

Moteur::~Moteur()
{}

void Moteur::changementVitesse(uint16_t duree1, uint16_t duree2)
{
    OCR1A = duree1 ;
    OCR1B = duree2 ;
}


void Moteur::avancerMoteur()
{
    changementVitesse(134,155);
    //changementVitesse(50,152);
}

void Moteur::reculerMoteur()
{
    changementVitesse(122,128);
    PORTD |= (1<<PD2) | (1<<PD3);
}

void Moteur::arreterMoteur()
{
    //TCCR1B = 0 ;
    changementVitesse(0,0);
    
}


void Moteur::tournerDroite90()
{
    changementVitesse(max_,min_);
    //_delay_ms(2110);
    //arreterMoteur();
}

void Moteur::tournerGauche90()
{
    changementVitesse(min_,max_);
    //_delay_ms(1950);
    //arreterMoteur();
}
