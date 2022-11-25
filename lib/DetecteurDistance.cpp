// #include "DetecteurDistance.h"


// DetecteurDistance::DetecteurDistance()
// {}

// DetecteurDistance::~DetecteurDistance()
// {}



// int- DetecteurDistance::detecterBar(){

//     gdistance = (convertisseurAnalogique.lecture(0x00) >>2);
//     //Uart uart;
//     //uart.transmissionUART(gdistance);
//     //_delay_ms(500);
//     switch (gdistance)
//     {

        

//         case 0x13 ... 0x17: // [43cm - 53cm] loins 
//             moteur.arreterMoteur();
//             sonnerie.jouerSon(frequence[0]);
//             _delay_ms(1000);
//             sonnerie.arreterSon();

//             del.rouge(&PORTB);
//             tableaux_des_barrieres[conteurBarr] = 2 ;

//             break;

//         case  0x4f ... 0x59: // [11cm - 21cm] proche
//             moteur.arreterMoteur();
//             del.vert(&PORTB);

            
//             sonnerie.jouerSon(frequence[35]);
//             _delay_ms(1000);
//             sonnerie.arreterSon();
//             moteur.avancerMoteur();

//             tableaux_des_barrieres[conteurBarr] = 1 ;

//             break;

//         // case 0x6C ... 0x93 : 
//         //     del.eteint(&PORTB);
//         //     break;
//         // case 0x00 ... 0x13 :
//         //     del.eteint(&PORTB);
//         //     break;
//         default:
//             del.eteint(&PORTB);
//             sonnerie.arreterSon() ;
//             moteur.avancerMoteur();

//             tableaux_des_barrieres[conteurBarr] = 0 ;

//             break;


//     }
//     conteurBarr++;

//     return tableaux_des_barrieres ;
// }
