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

Memoire24CXXX memoire ;
Moteur moteur ;
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

int note[37]=
{
    45,46,47,48,49,50,51,52,53,
    54,55,56,57,58,59,60,61,62,
    63,64,65,66,67,68,69,70,71,
    72,73,74,75,76,77,78,79,80,
    81
};

double detecterSon(uint8_t operande){
    
    for(uint8_t i=0;i<37;i++)
    {
        if(operande==note[i])
        {
            return frequence[i];
        }
    }
}
void lectureMemoire(uint16_t& adresse, uint8_t& donnee)
{
    memoire.lecture(adresse,&donnee);
    adresse+=1;
}


uint16_t tailleFichier(uint16_t& adresse)
{
    uint8_t ptr_taille[2] ;
    memoire.lecture(adresse, ptr_taille,2);
    adresse+=2 ;
    return ((uint16_t)(ptr_taille[0] << 8) | ptr_taille[1]);
}


bool debutProgramme(uint8_t instruction)
{
    return (instruction == 0x01);
}


int main()
{
    
    DDRA = 0xff ;
    bool commencer = false ;
    uint8_t instruction;
    uint8_t operande ;
    uint16_t adresse = 0x0000 ;
    uint16_t taille = tailleFichier(adresse) ;
    uint8_t iter = 1;
    double frequence ;
    uint8_t debutBoucle ;
    
    while(!(commencer))
    {
        lectureMemoire(adresse, instruction) ;
        lectureMemoire(adresse, operande);
        commencer = debutProgramme(instruction);

    }
    while(commencer)
    {
        for (uint16_t i =0;i< taille; i++)
        {
            lectureMemoire(adresse, instruction);
            lectureMemoire(adresse,operande);
            
        
            switch (instruction)
            {
                case 0x02 :
                    for(uint8_t i=0; i<operande;i++)
                    {
                        _delay_ms(25);
                    }
                    break ;

                case 0x44 :
                    if(operande==1)
                    {
                        
                        del.vert(&PORTA);
                    }
                    else if (operande ==2)
                    {
                        del.rouge(&PORTA);
                    }
                    break ;

                case 0x45 :
                    del.eteint(&PORTA);
                    break;

                case 0x48 :
                    frequence = detecterSon(operande);
                    sonnerie.jouerSon(frequence);
                    break;

                case 0x09 :
                    sonnerie.arreterSon();
                    break;               
                
                case 0x60 :
                    moteur.arreterMoteur();
                    break ;
                
                case 0x61 :
                    moteur.arreterMoteur();
                    break ;

                case 0x62 :
                    moteur.avancerMoteur(operande,operande-10);
                    break;

                case 0x63 :
                    moteur.reculerMoteur(operande,operande-10);
                    break;

                case 0x64 :
                    moteur.tournerDroite90();
                    break ;
                 
                case 0x65 :
                    moteur.tournerGauche90();
                    break ;
                
                case 0xc0 :
                    iter += operande ;
                    debutBoucle = adresse ;
                    break ;
                
                case 0xc1 :
                    iter -=1 ;
                    if(iter !=0)
                    {
                        adresse = debutBoucle ;
                    }
                    break ;
                
                case 0xFF :
                    moteur.arreterMoteur();
                    sonnerie.arreterSon();
                    del.eteint(&PORTA);
                    commencer = false ;
                    break ;
            }
        }
    }
    return 0;
}
