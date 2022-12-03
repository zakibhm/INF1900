#include "Moteur.h"

Moteur::Moteur()
{
    // DDRD |= (1 << PD2) | (1<< PD3)| (1 << PD4) | (1<< PD5);
    // TCCR1A |=(1<<WGM10) |(1<<COM1A1)|(1<<COM1B1) ;//|(1<<COM1A0)|(1<<COM1B0);
    // TCCR1B |= (1<<CS11)  | (0 << CS10) | (0 << CS12);
    // TCCR1C = 0;
    DDRB |= 0xff;
    TCCR0A |=(1<<WGM00) |(1<<COM0A1)|(1<<COM0B1) ;
    TCCR0B |= (1<<CS01)  ;//| (0 << CS00) | (0 << CS02);
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
    changementVitesse(97,102);// 95,100
    //changementVitesse(50,152);
}

void Moteur::avancerMoteur(uint16_t duree1, uint16_t duree2)
{
    PORTB &= ~((1<<PB5) | (1<<PB2));
    changementVitesse(duree1,duree2);// 144,130
    //changementVitesse(50,152);
}

void Moteur::reculerMoteur(uint16_t duree1, uint16_t duree2)
{
    //changementVitesse(122,128);
    changementVitesse(duree1,duree2);
    PORTB |= (1<<PB5) | (1<<PB2);
}

void Moteur::reculerMoteur()
{
    //changementVitesse(122,128);
    changementVitesse(91,102);
    PORTB |= (1<<PB5) | (1<<PB2);
}

void Moteur::arreterMoteur()
{
    //TCCR1B = 0 ;
    changementVitesse(0,0);
    
}


void Moteur::tournerDroite90()
{
   
    //_delay_ms(50);
    PORTB &= ~((1<<PB5) | (1<<PB2));
    changementVitesse(40,93);
    //changementVitesse(30,97);
    
}

void Moteur::tournerGauche90()
{
    
    //_delay_ms(50);
    PORTB &= ~((1<<PB5) | (1<<PB2));
    //changementVitesse(85,30);
    //changementVitesse(90,40);
    changementVitesse(97,40);

    
    
}


void Moteur::tournerDroite()
{
    PORTB &= ~((1<<PB5) | (1<<PB2));
    changementVitesse(40,85);
    
}


void Moteur::tournerGauche()
{
    PORTB &= ~((1<<PB5) | (1<<PB2));
    changementVitesse(95,40);// changementVitesse(125,40);
    
}


void Moteur::tournerDroite(uint16_t duree1, uint16_t duree2)

{
    PORTB &= ~((1<<PB5) | (1<<PB2));
    changementVitesse(duree1,duree2);
    
}


void Moteur::tournerGauche(uint16_t duree1, uint16_t duree2)
{
    PORTB &= ~((1<<PB5) | (1<<PB2));
    changementVitesse(duree1,duree2);// changementVitesse(125,40);
    
}

