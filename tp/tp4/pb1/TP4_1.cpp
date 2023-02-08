#include <avr/io.h> 
#define F_CPU 8000000UL
#include <util/delay.h> 
#include <avr/interrupt.h>

void ROUGE(){
    PORTA&=~(1<<PA0);
    PORTA|=(1<<PA1);
}

void VERT() {
    PORTA&=~(1<<PA1);
    PORTA|=(1<<PA0);
}
void ETEINT(){
    PORTA&=~(1<<PA0);
    PORTA&=~(1<<PA1);
}

void AMBRE(){
    PORTA&=~(1<<PA0);
    PORTA|=(1<<PA1);
    _delay_us(1);
    PORTA&=~(1<<PA1);
    PORTA|=(1<<PA0);
    _delay_us(4);                   
}

enum class ETAT { INIT,EA,EB,EC,ED,EF}; 
volatile ETAT systeme = ETAT::INIT;
volatile uint8_t Compteur_etat = 0;


void initialisation ( void ) 
{
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontrôleur n'est pas prêt...
    cli ();
    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    DDRA = 0xff; // PORT A est en mode sortie
    DDRD = 0x00; // PORT D est en mode entree

    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0) ;


    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |=(1<<ISC00);
    // sei permet de recevoir à nouveau des interruptions.
    sei ();
}

// placer le bon type de signal d'interruption à prendre en charge en argument
ISR (INT0_vect) 
{
    // laisser un délai avant de confirmer la réponse du bouton-poussoir: environ 30 ms (anti-rebond)
    _delay_ms ( 30 );
    // se souvenir ici si le bouton est pressé ou relâché
    // changements d'état tels que ceux de la semaine précédente
    ETAT tableau_des_etats[6]={ETAT::INIT,ETAT::EA,ETAT::EB,ETAT::EC,ETAT::ED,ETAT::EF};
    Compteur_etat++;   
    systeme=tableau_des_etats[Compteur_etat];  

    EIFR |= (1 << INTF0) ;
}
int main()
{
    initialisation ();
    while (true)
    { 
        switch (systeme)
        {
        case ETAT::INIT:
            ROUGE();                                  
            break;

        case ETAT::EA:                
            AMBRE();
            break;

        case ETAT::EB:
            VERT();
            break;

        case ETAT::EC:
            ROUGE();               
            break;

        case ETAT::ED:
            ETEINT();               
            break;
        case ETAT::EF:
            Compteur_etat=-1;
            VERT();
            break;
                
        }
    }
}