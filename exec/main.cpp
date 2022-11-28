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

// volatile uint8_t gdistance ;
// Moteur moteur;
// Memoire24CXXX memoire ;
// Del del ;
// Son sonnerie ;
// can convertisseurAnalogique ;

// double frequence[37]=
// {
//     110,116.54,123.47,130.81,138.59,146.83,
//     155.56,164.81,174.61,185.00,196.00,207.65,
//     220,233.08,246.94,261.63,277.18,293.66,311.13,
//     329.63,349.23,369.99,392.00,415.30,440,466.16,
//     493.88,523.25,554.37,587.33,622.25,659.26,698.46,
//     739.99,783.99,830.61,880
// };

// void detectionBarreDeFer()
// {
//     gdistance = (uint8_t)(convertisseurAnalogique.lecture(0x00) >>2);
//     Uart uart;
//     uart.transmissionUART(gdistance);
//     _delay_ms(1000);
//     switch (gdistance)
//     {

        

//         case 0x15 ... 0x1c: // [43cm - 53cm] loins 
//             moteur.arreterMoteur();
//             sonnerie.jouerSon(frequence[0]);
//             _delay_ms(1000);
//             sonnerie.arreterSon();

//             del.rouge(&PORTB);

//             break;

//         case  0x40 ... 0x5c: // [11cm - 21cm] proche
//             moteur.arreterMoteur();
//             del.vert(&PORTB);

            
//             sonnerie.jouerSon(frequence[35]);
//             _delay_ms(1000);
//             sonnerie.arreterSon();
//             moteur.avancerMoteur();
//             break;


//         default:
//             del.eteint(&PORTB);
//             sonnerie.arreterSon() ;
//             moteur.avancerMoteur();
//             break;


//     }
// }

// int main()
// {
//     DDRA = 0x00;
//     DDRB = 0xff;
//     DDRD = 0xff ;
    
//     uint8_t entree = PINC ;
//     _delay_ms(5000) ;
//     moteur.avancerMoteur();
//     _delay_ms(10000);
//     moteur.tournerDroite90();
//     moteur.tournerGauche90();
//     moteur.tournerDroite();
//     _delay_ms(10000);
//     while (true)
//     {
//         entree = PINC ;
//         entree &= 0x1f & entree ;
//     detectionBarreDeFer();
    
//         switch (entree)
//         {
//                 case 0b00000001 :
//                     moteur.tournerGauche();
//                     break;
//             case 0b00000010 :
//                 moteur.tournerGauche();
//                 break ;
//             case 0b00000011 :
//                 moteur.tournerGauche();
//                 break;

//             case 0b00001000 :
//                 moteur.tournerDroite();
//                 break;

//             case 0b000010000 :
//                 moteur.tournerDroite();
//                 break;

//             case 0b00011000 :
//                 moteur.tournerDroite();
//                 break;

//             case 0b00000111 :
//                 _delay_ms(300);
//                 entree = PINC ;
//                 entree &= 0x1f & entree ;
//                 if (entree == 0b00011111 )
//                     moteur.arreterMoteur();
                    
                
//                 else {
//                     moteur.avancerMoteur();
//                     _delay_ms(170);
//                     while (!(entree & 0x04))
//                     {
//                         moteur.tournerGauche90();
//                         entree = PINC ;
//                         entree &= 0x1f & entree ;
//                     }
                    
//                 }
                    
//                 break;          
                        

//             case 0b00001111 : 

//                 _delay_ms(300);
//                 entree = PINC ;
//                 entree &= 0x1f & entree ;
//                 if (entree == 0b00011111 )
//                     moteur.arreterMoteur();
                    
                
//                 else {
//                     moteur.avancerMoteur();
//                     _delay_ms(170);
//                     while (!(entree & 0x04))
//                     {
//                         moteur.tournerGauche90();
//                         entree = PINC ;
//                         entree &= 0x1f & entree ;
//                     }
//                 }
                    
//                 break;

//             case 0b00011100 : 

//                 _delay_ms(300);
//                 entree = PINC ;
//                 entree &= 0x1f & entree ;
//                 if (entree == 0b00011111 ){
//                     moteur.arreterMoteur();
//                     }

//                 else {
//                     moteur.avancerMoteur();
//                     _delay_ms(250);
//                     while (!(entree & 0x04))
//                     {
//                         moteur.tournerDroite90();
//                         entree = PINC ;
//                         entree &= 0x1f & entree ;
//                     }
//                 }
                    
                    
//                 break;

//             case 0b00011110 : 
//                 _delay_ms(300);
//                 entree = PINC ;
//                 entree &= 0x1f & entree ;
//                 if (entree == 0b00011111 ){
//                     moteur.arreterMoteur();
//                     }

//                 else {
//                     moteur.avancerMoteur();
//                     _delay_ms(250);
//                     while (!(entree & 0x04))
//                     {
//                         moteur.tournerDroite90();
//                         entree = PINC ;
//                         entree &= 0x1f & entree ;
//                     }
//                 }
                    
                    
//                 break;

//             case 0b00000100 :
//                 moteur.avancerMoteur();
//                 break;

//             case 0b00001110 :
//                 moteur.avancerMoteur();
//                 break;

//             case 0b00000110 :
//                 moteur.avancerMoteur();
//                 break;

//             case 0b00001100 : 
//                 moteur.avancerMoteur();
//                 break;

//             case 0b00011111: 
//                 moteur.arreterMoteur();
//                 break;
            
//             default:
//                 moteur.arreterMoteur();
//                 break;
//         }

//     }
    
//     return 0;
// }




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
    // Del del ;
    // while(!(detecteurLigne_.getPoint_S()))
    // {
        
    //     switch (partieCourante)
    //     {
    //     case Partie::barriere_1 :
    //         del.rouge(&PORTB);
    //         detecteurLigne_.detecterLigne();
    //         break ;
    //     default :
    //         break ;
    //     }
    // }
    Robot robot ;
    //robot.pariteA();
    Son son ;
    
    son.arreterSon();
    //robot.partieB();
    DetecteurLigne dec ;
    Del del ;
    Moteur moteur ;
    //moteur.avancerMoteur();
    //_delay_ms(10000);
    //del.rouge(&PORTB);
    while (true)
    {
        //del.rouge(&PORTB);
        dec.detecterLigne();
    }

    return 0 ;
}



