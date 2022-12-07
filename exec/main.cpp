#define F_CPU 8000000
#include "Controleur.h"

int main()
{
    Controleur controleur ;
    controleur.initialisationbreadBoard();
    controleur.initialisationButtonPoussoir();
    Del del ;
    DetecteurLigne dec ;
    // Moteur moteur ;
    // moteur.avancerMoteur();
    // _delay_ms(5000);
    // moteur.arreterMoteur();
    // while(true)
    // {
    //     dec.detecterLigne("PartieB","deuxDirection");
    //     if(dec.getDoublechemin())
    //         {del.vert(&PORTB);
    //         break;}

    // }
    //Robot robot ;
    //robot.partieB();
    //robot.partieC();

    while(true)
    {
        controleur.SelectionnerPartie();
    }    

    return 0 ;
}



