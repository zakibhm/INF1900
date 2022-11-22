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
    uint8_t entree = PINC ;
    
    while(true)
    {
        
        entree = PINC ;


        if((entree & 0X04) && !(entree & 0X01) && !(entree & 0X10) )
        {
            del.ambre(&PORTA);
            moteur.avancerMoteur();
        }

        else if((entree & 0x01) && (entree & 0x02) && (entree & 0x04) )

        {
            
            // for(uint8_t i=0;i<16;i++)
            // {
            //     del.rouge(&PORTA);
            //     _delay_ms(500);
            //     del.vert(&PORTA);
            //     _delay_ms(500);
            // }
            
            moteur.tournerDroite90();
        }

        else if((entree & 0x10) && (entree & 0x08) && (entree & 0x04) )
        {
            // for(uint8_t i=0;i<16;i++)
            // {
            //     del.rouge(&PORTA);
            //     _delay_ms(500);
            //     del.vert(&PORTA);
            //     _delay_ms(500);
            // }
            moteur.tournerGauche90();
            
        }

        else if((entree & 0x03) && !(entree & 0x0C))
        {
            del.vert(&PORTA);
            moteur.tournerGauche();
        }

        else if((entree & 0x0C) &&!(entree & 0x03))
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
