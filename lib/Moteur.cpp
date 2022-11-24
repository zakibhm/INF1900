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
    PORTD &= ~((1<<PD2) | (1<<PD3));
    changementVitesse(184,170);
    //changementVitesse(50,152);
}

void Moteur::reculerMoteur()
{
    //changementVitesse(122,128);
    changementVitesse(140,148);
    PORTD |= (1<<PD2) | (1<<PD3);
}

void Moteur::arreterMoteur()
{
    //TCCR1B = 0 ;
    changementVitesse(0,0);
    
}


void Moteur::tournerDroite90()
{
    PORTD &= ~((1<<PD2) | (1<<PD3));
    Moteur::avancerMoteur();
    _delay_ms(40);
    changementVitesse(0,142);
    _delay_ms(1250);
    arreterMoteur();
    
}

void Moteur::tournerGauche90()
{
    

    
    PORTD &= ~((1<<PD2) | (1<<PD3));
    Moteur::avancerMoteur();
    _delay_ms(110);
    changementVitesse(142,0);
    _delay_ms(1000);
    arreterMoteur();
    
}


void Moteur::tournerDroite()

{
    PORTD &= ~((1<<PD2) | (1<<PD3));
    changementVitesse(max_,min_);
    
}

void Moteur::tournerGauche()
{
    PORTD &= ~((1<<PD2) | (1<<PD3));
    changementVitesse(min_,max_);
    
}