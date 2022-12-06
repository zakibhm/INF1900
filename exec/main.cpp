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
    Del del ;
    Moteur moteur ;
    Robot robot ;
    
    //del.rouge(&PORTB);
    //robot.pariteA();
    robot.partieB();
    robot.partieC();
    //robot.stationnement();
    // DetecteurLigne dec ;
    // while(true)
    // {
    //     dec.detecterZigZag();
    // }
    

    return 0 ;
}



