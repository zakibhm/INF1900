#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h> 
#include "Del.h"
#include "debug.h"
#include "Minuterie.h" 
#include "Interrupteur.h"
#include "Moteur.h"
#include "photoresistance.h"
#include "Uart.h"
#include <avr/interrupt.h>



Del del ;
Interrupteur interrupteur ;
volatile uint8_t gbutton=0;
//Minuterie minuterie ;
//Photoresistance photoresistance ;
//Uart uart ;
//can convertisseurAnalogique;
// ISR (INT0_vect) 
// {
//     
//     _delay_ms(30);
//      gbutton =1 ;
// }

int main()
{
    /*
    //test de la classe Del :
    DDRD = 0xff ;
    del.rouge(&PORTD);
    _delay_ms(5000);
    DEBUG_PRINT(("ROUGE"));
    del.vert(&PORTD);
    _delay_ms(5000);
    DEBUG_PRINT(("VERT"));
    _delay_ms(5000);
    del.eteint(&PORTD);
    */



    // Test de la classe Moteur :
    // Moteur moteur;
    // while (true){
    //     moteur.avancerMoteur( 120,120);
    //     DEBUG_PRINT(("le robot avance"));
    //     _delay_ms(5000);
    //     moteur.avancerMoteur(170,170);
    //     _delay_ms(5000);
    //     moteur.avancerMoteur(0,0); 
    //     DEBUG_PRINT(("le robot arrete"));
    //     _delay_ms(500); 
    //     moteur.reculerMoteur(50,50);
    //     DEBUG_PRINT(("le robot recule"));
    //     _delay_ms(5000);
    //     moteur.reculerMoteur(150,150); 
    // }
    

    //test de la classe Interrupteur :
    // interrupteur.initialisationInterruption();
    // if(gbutton==1){
    //     DEBUG_PRINT(("le boutton est pesé (par interruption)"));
    //     del.rouge(&PORTA);
    //     _delay_ms(1000);
    // }
    // if (interrupteur.antiRebound()){
    //     DEBUG_PRINT(("le boutton est pesé (par scrutation)"));
    //     del.rouge(&PORTA);
    //     _delay_ms(1000);
    // }

    /*
    //Test de la photoresistance :
    Photoresistance photoresistance;
    photoresistance.chargerEntree();
    DEBUG_PRINT(("charger de l'entree pour le CAN"));
    photoresistance.affichage();
    DEBUG_PRINT(("affichage de la conversion de LA donnée comme une couleure sue la DEL"));
    */
}
