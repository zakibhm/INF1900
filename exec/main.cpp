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
    

    //robot.pariteA();
    robot.partieB();

    return 0 ;
}



