/*
Auteurs: Zekaria Bouchama 2174321
         Moualdi Sofiane  2115145

Date: 17 octobre 2022

Description du programme : Cette partie 1 du TP6 de INF1900 consiste à réaliser des installations
sur le breadboard ensuite réaliser une machine à état. Au debut on devra appuyer sur le bouton 
installé et un compteur commence. Lorsque le bouton n'est plus pesé ou que le compteur atteint 120, la Led tournera
au vert pendant 0.5 secondes. La led s'eteint et laisse un delai de 2 secondes avant de clignoter compteur/2 fois au rythme de 2 clignotements par seconde. 
Une fois terminé, la Led tourne au vert pendant 1 seconde
puis revient à un état initial eteint.

Etat Actuel                             - - - - - - - - Prochain état - - - - - - -       Sortie (lumière)
Entrée Bouton poussoir /Compteur        0/x     |      0/120   |   1/x   |    1/120      
init                                    init    |       init   |   e1    |     e1         (eteint)
e1                                      e2      |       e2     |   e1    |     e2         (aucune lumiere puis lumiere verte pour 0.5s puis  aucune lumiere)
e2                                      e3      |       e3     |   e3    |     e3         (aucune lumiere pendant 2s puis lumiere rouge clignante compteur/2 fois)
e3                                      init    |       init   |   init  |     init       (lumiere verte pendant 1s)

*/

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h> 
#include <avr/interrupt.h>

const uint8_t mode_sortie = 0xff;
enum class Etat { init,     //Etat initial qui verife si le button est pesé ou non
                  e1,       //Etat clignotant avec la couleur verte pour 0.5s
                  e2,       //Etat clignotant avec la couleur rouge au rythme de 2 fois par seconde
                  e3        //Etat final la lumière tourne au vert pendant une seconde
                };      

volatile Etat State = Etat::init;
volatile uint8_t gCompteur = 0;
void rouge(){
    PORTB&=~(1<<PA0);
    PORTB|=(1<<PA1);
}

void vert() {
    PORTB&=~(1<<PA1);
    PORTB|=(1<<PA0);
}

void eteint(){
    PORTB&=~(1<<PA0);
    PORTB&=~(1<<PA1);
}


void partirMinuterie () {
    sei();    // cli est une routine qui bloque toutes les interruptions.
    TCNT1 = 0 ;//initializing Timer/Counter register on 0
    OCR1A = 781;//interruption chaque 0.1 seconde
    TCCR1B |= (1<<CS12)|(1<<CS10)|(1<<WGM12);//setting Timer/Counter register (8bits) on 1024 prescalar and on CTC mode
    TIMSK1 |=(1<<OCIE1A);
}

ISR (TIMER1_COMPA_vect) //chaque 0.1s on a une iterruption qui incremente notre compteur
{
    gCompteur+=1;
}
void changementEtat(){
    switch (State)
    {
        case Etat::init://Etat initial qui verife si le button est pesé ou non
            gCompteur=0;
            eteint() ;
            if(!(PIND & 0x04))//button pesé
            {
                State=Etat::e1;
                partirMinuterie();
            }                                 
            break;

        case Etat::e1://Etat clignotant avec la couleur verte pour 0.5s
            if((PIND & 0x04) || (gCompteur==120))//si le button est relaché ou le compteur atteint la valeur 120 (12s passées)
            { 
            vert();
            _delay_ms(500);
            eteint();
            State=Etat::e2;
            }            
            break;

        case Etat::e2://Etat clignotant avec la couleur rouge au rythme de 2 fois par seconde
            _delay_ms(2000);
            cli();
            for (uint8_t i = 0; i < gCompteur/2; i++)
            {
                rouge();
                _delay_ms(250);
                eteint();
                _delay_ms(250);
            }
            State=Etat::e3;
            break;

        case Etat::e3://Etat final la lumière tourne au vert pendant une seconde
            vert();
            _delay_ms(1000);
            State=Etat::init;               
            break;
        }
}

int main(){

    DDRB=mode_sortie;
    while (true)
    { 
        changementEtat();
    }
}