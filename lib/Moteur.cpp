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
    changementVitesse(100,110);// 144,130
    //changementVitesse(50,152);
}

void Moteur::avancerMoteur(uint16_t duree1, uint16_t duree2)
{
    PORTD &= ~((1<<PD2) | (1<<PD3));
    changementVitesse(duree1,duree2);// 144,130
    //changementVitesse(50,152);
}



void Moteur::reculerMoteur()
{
    //changementVitesse(122,128);
    changementVitesse(10,148);
    PORTD |= (1<<PD2) | (1<<PD3);
}

void Moteur::arreterMoteur()
{
    //TCCR1B = 0 ;
    changementVitesse(0,0);
    
}


void Moteur::tournerDroite90()
{
   
    //_delay_ms(50);
    PORTD &= ~((1<<PD2) | (1<<PD3));
    changementVitesse(30,97);
    
}

void Moteur::tournerGauche90()
{
    
    //_delay_ms(50);
    PORTD &= ~((1<<PD2) | (1<<PD3));
    changementVitesse(85,30);
    
    
}


void Moteur::tournerDroite(uint16_t duree1, uint16_t duree2)

{
    PORTD &= ~((1<<PD2) | (1<<PD3));
    changementVitesse(100,120);
    
}


void Moteur::tournerGauche(uint16_t duree1, uint16_t duree2)
{
    PORTD &= ~((1<<PD2) | (1<<PD3));
    changementVitesse(120,100);// changementVitesse(125,40);
    
}