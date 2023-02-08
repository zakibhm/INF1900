/*
Auteurs: Zekaria Bouchama 2174321
         Moualdi Sofiane  2115145

Date: 17 octobre 2022

Description du programme : Cette partie 2 du TP6 de INF1900 consiste d'abord à faire l'installation d'une photo-resistance et la del devra afficher
ambre en cas d'une detection d'une lumière ambiante, vert en cas d'une lumière basse et rouge en cas de lumière très forte.
entrée: valeur numrique convertie à partir de la détection de lumière captée par la photo-resistance
Sortie: lumière de la DEL

*/

#include <avr/io.h> 
#define F_CPU 8000000UL
#include <util/delay.h> 
#include <avr/interrupt.h>
#include "can.h"
volatile uint8_t gLumiereNum;//la variable qui stocke la version numerique de l'itensité de la lumière captée en 8 bits
const uint8_t mode_entree = 0x00;
const uint8_t mode_sortie = 0xff;
can convertisseurAnalogique;

void vert() {
    PORTB&=~(1<<PA1);
    PORTB|=(1<<PA0);
}

void rouge(){
    PORTB&=~(1<<PA0);
    PORTB|=(1<<PA1);
}

void ambre(){
    rouge();
    _delay_ms(4);
    vert();
    _delay_ms(8);                   
}

void changementDeCouleur_Par_gLumiereNum(){

    gLumiereNum = (convertisseurAnalogique.lecture(0x00) >> 2);  // charger les 8 premiers bits de la lecture dans la variable gLumiereNum

    switch (gLumiereNum)
    {
        case  0x00 ... 0xE0:
            vert();
            break;
    
        case 0xE1 ... 0xEE :
            ambre();
            break;

        default:
            rouge();
            break;
    }
}

int main() {
  DDRA = mode_entree; 
  DDRB = mode_sortie; 

  while (true) {
    changementDeCouleur_Par_gLumiereNum();
  }
}
