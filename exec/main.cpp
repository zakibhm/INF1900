#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h> 
#include <avr/interrupt.h>
#include "Del.h"
#include "debug.h"
#include "Sonnerie.h"
#include "Minuterie.h" 
#include "Interrupteur.h"
#include "Moteur.h"
#include "photoresistance.h"
#include "Uart.h"
#include <avr/interrupt.h>
#include <memoire_24.h>


Moteur moteur;
Memoire24CXXX memoire ;
Del del ;
Son sonnerie ;



int main()
{
    DDRC = 0x00;
    DDRA = 0xff ;
    
    DDRA = 0xff ;
    
    while(true)
    {
        if(PINC & 0X04)
        {
            del.ambre(&PORTA);
            moteur.avancerMoteur();
        }

        else if(PINC & 0x01)

        {
            
            moteur.arreterMoteur();
            _delay_ms(200); 
            moteur.reculerMoteur();
            _delay_ms(500);
            //moteur.avancerMoteur();
            moteur.tournerDroite90();
        }

        else if(PINC & 0x10)
        {
            moteur.arreterMoteur();
            _delay_ms(200);
            moteur.reculerMoteur();
            _delay_ms(500);
            //moteur.avancerMoteur();
            moteur.tournerGauche90();
        }

        else if(PINC & 0x03)
        {
            del.vert(&PORTA);
            moteur.tournerGauche();
        }

        else if(PINC & 0x0C)
        {
            del.rouge(&PORTA);
            moteur.tournerDroite();
        }
        else
        {
            del.eteint(&PORTA);
            moteur.arreterMoteur();
        }
    }
    
    return 0;
}
