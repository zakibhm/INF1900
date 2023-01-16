#include "Moteur.h"

Moteur::Moteur()
{
    DDRB |= 0xff;
    TCCR0A |=(1<<WGM00) |(1<<COM0A1)|(1<<COM0B1) ;
    TCCR0B |= (1<<CS01)  ;
}

Moteur::~Moteur()
{}

void Moteur::changementVitesse(uint16_t duree1, uint16_t duree2)
{
    OCR0A = duree1 ;
    OCR0B = duree2 ;
}


void Moteur::avancerMoteur()
{
    PORTB &= ~((1<<PB5) | (1<<PB2));
    changementVitesse(102,100);
}

void Moteur::avancerMoteur(uint16_t duree1, uint16_t duree2)
{
    PORTB &= ~((1<<PB5) | (1<<PB2));
    changementVitesse(duree1,duree2);
}

void Moteur::reculerMoteur(uint16_t duree1, uint16_t duree2)
{
    changementVitesse(duree1,duree2);
    PORTB |= (1<<PB5) | (1<<PB2);
}

void Moteur::reculerMoteur()
{
    changementVitesse(98,103);
    PORTB |= (1<<PB5) | (1<<PB2);
}

void Moteur::arreterMoteur()
{
    changementVitesse(0,0);
    
}


void Moteur::tournerDroite90()
{
   
    PORTB &= ~((1<<PB5) | (1<<PB2));
    changementVitesse(28,89);
    
}

void Moteur::tournerGauche90()
{
    PORTB &= ~((1<<PB5) | (1<<PB2));
    changementVitesse(100,31);
}


void Moteur::tournerDroite()
{
    PORTB &= ~((1<<PB5) | (1<<PB2));
    changementVitesse(40,85);
    
}


void Moteur::tournerGauche()
{
    PORTB &= ~((1<<PB5) | (1<<PB2));
    changementVitesse(98,40);
    
}


void Moteur::tournerDroite(uint16_t duree1, uint16_t duree2)

{
    PORTB &= ~((1<<PB5) | (1<<PB2));
    changementVitesse(duree1,duree2);
    
}


void Moteur::tournerGauche(uint16_t duree1, uint16_t duree2)
{
    PORTB &= ~((1<<PB5) | (1<<PB2));
    changementVitesse(duree1,duree2);
    
}

