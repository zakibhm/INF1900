#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h> 
#include <avr/interrupt.h>
#include "Del.h"
#include "can.h"
#include "debug.h"
#include "Sonnerie.h"
#include "Minuterie.h" 
#include "Interrupteur.h"
#include "Moteur.h"
#include "photoresistance.h"
#include "Uart.h"
#include <avr/interrupt.h>
#include <memoire_24.h>


#include "robot.h"




int main()
{
    // DetecteurLigne detecteurLigne_ ;
    // while (!(detecteurLigne_.getPoint_B()))
    // {
    //     //detecteurDistance_.detecterBar();
    //     detecteurLigne_.detecterLigne();

    // }
    // int tableau[3]= {1,2,1} ;
    // enum class Partie{barriere_1,barriere_2,barriere_3,fin} ;
    // Partie partieCourante = Partie::barriere_1 ;
    Del del ;
    
    Moteur moteur ;
    // while(true)
    // {
    //     moteur.avancerMoteur();
    // }
    
    //_delay_ms(5000);
    Robot robot ;
    //robot.pariteA();
    //moteur.avancerMoteur();
    //_delay_ms(500);
    //del.vert(&PORTB);
    //_delay_ms(10000);
    //robot.pariteA();
    //moteur.avancerMoteur();
    //_delay_ms(2000);
    //robot.pariteA();
    robot.partieB();
    // Son son ;
    
    // son.arreterSon();
    // //robot.partieB();
    // DetecteurLigne dec ;
    // DetecteurDistance decD ;
    // Del del ;
    
    //moteur.tournerDroite(0,150);
    //_delay_ms(5000);
    //moteur.avancerMoteur();
    //_delay_ms(10000);
    //del.rouge(&PORTB);
    // while(true)
    // {
    //     dec.detecteurDistance();
    //     dec.detecterLigne("PartieA");
    // }
    // while (true)
    // {
    //     //del.rouge(&PORTB);
    //     dec.detecterLigne("PartieA");
    // }

    return 0 ;
}



