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

double frequence[37]=
{
    110,116.54,123.47,130.81,138.59,146.83,
    155.56,164.81,174.61,185.00,196.00,207.65,
    220,233.08,246.94,261.63,277.18,293.66,311.13,
    329.63,349.23,369.99,392.00,415.30,440,466.16,
    493.88,523.25,554.37,587.33,622.25,659.26,698.46,
    739.99,783.99,830.61,880
};

void detectionBarreDeFer()
{
    gdistance = (convertisseurAnalogique.lecture(0x00) >>2);
    switch (gdistance)
    {
        case  0x38 ... 0x45:
            //moteur.arreterMoteur();
            sonnerie.jouerSon(frequence[36]);
            _delay_ms(1000);
            sonnerie.arreterSon();
            break;

        case 0x1C ... 0x22:
            //moteur.arreterMoteur();
            sonnerie.jouerSon(frequence[0]);
            _delay_ms(1000);
            sonnerie.arreterSon();
            break;

        default:
            moteur.avancerMoteur();


    }
}

int main()
{
    DDRC = 0x00;
    DDRA = 0xff ;
    
    uint8_t entree = PINC ;
    //moteur.avancerMoteur();
    //_delay_ms(10000);
    //moteur.tournerDroite90();
    //moteur.tournerGauche90();



    
    while(true)
    {
        
        entree = PINC ;


        if((entree & 0X04) && !(entree & 0X01) && !(entree & 0X10) )
        {
            //del.ambre(&PORTA);
            moteur.avancerMoteur();
            del.eteint(&PORTA);
        }

        else if( ((entree & 0x01) && (entree & 0x02) && (entree & 0x04) && !(entree & 0x08) && !(entree & 0x10)) ||   ((entree & 0x01) && (entree & 0x02) && (entree & 0x04) && (entree & 0x08) && !(entree & 0x10)))

        {
            del.vert(&PORTA);
            moteur.tournerGauche90();
        }

        else if( ((entree & 0x10) && (entree & 0x08) && (entree & 0x04) && !(entree & 0x01) && !(entree & 0x02) )   ||   ((entree & 0x10) && (entree & 0x08) && (entree & 0x04) && (entree & 0x02) && !(entree & 0x01) )  )
        {
            
            del.rouge(&PORTA);
            moteur.tournerDroite90();
            
            
        }


        else if((entree & 0x03) && !(entree & 0x0C))
        {
            del.eteint(&PORTA);
            moteur.tournerGauche();
        }

        else if((entree & 0x0C) &&!(entree & 0x03))
        {
            
            del.eteint(&PORTA);
            moteur.tournerDroite();
        }

        else if ((entree & 0x10) && (entree & 0x08) && (entree & 0x04) && (entree & 0x02) && (entree & 0x01))
        {
            del.eteint(&PORTA);
            moteur.arreterMoteur();
        }
        else
        {
            del.eteint(&PORTA);
            moteur.arreterMoteur();
        }
    }
    
    return 0;
}
