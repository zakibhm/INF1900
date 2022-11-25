
#include "DetecteurDistance.h"


DetecteurDistance::DetecteurDistance()
{
    DDRA = modeEntree ;
    DDRB = modeSortie ;
    //frequence[37]=



}

DetecteurDistance::~DetecteurDistance()
{}


int* DetecteurDistance::getTabBarrieres()
{
    return tableaux_des_barrieres ;
}


void DetecteurDistance::detecterBar(){

    gdistance = (convertisseurAnalogique.lecture(0x00) >>2);
    //Uart uart;
    //uart.transmissionUART(gdistance);
    //_delay_ms(500);
    switch (gdistance)
    {

        

        case 0x15 ... 0x1c: // [43cm - 53cm] loin
            moteur.arreterMoteur();
            sonnerie.jouerSon(frequence[0]);
            _delay_ms(1000);
            sonnerie.arreterSon();

            del.rouge(&PORTB);
            tableaux_des_barrieres[conteurBarr] = 2 ;
            conteurBarr++;
            break;

        case  0x40 ... 0x5c: // [11cm - 21cm] proche
            moteur.arreterMoteur();
            del.vert(&PORTB);

            
            sonnerie.jouerSon(frequence[35]);
            _delay_ms(1000);
            sonnerie.arreterSon();
            moteur.avancerMoteur();

            tableaux_des_barrieres[conteurBarr] = 1 ;
            conteurBarr++;
            break;

        default: // rien pour detecter 
            del.eteint(&PORTB);
            sonnerie.arreterSon() ;
            moteur.avancerMoteur();

            break;


    }
}
