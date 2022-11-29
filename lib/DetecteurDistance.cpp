
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
    // int moyenne,somme = 0 ;
    // for(int i =0;i<100;i++)
    // {

    // }
    gdistance = (convertisseurAnalogique.lecture(0x00) >>2);
    //Uart uart;
    //uart.transmissionUART(gdistance);
    //_delay_ms(500);
    switch (gdistance)
    {

        

        case 0x15 ... 0x2c: // [43cm - 53cm] loin //0x15 0x1C
            moteur.arreterMoteur();
            sonnerie.jouerSon(frequence[0]);
            _delay_ms(1000);
            sonnerie.arreterSon();

            del.rouge(&PORTB);
            tableaux_des_barrieres[conteurBarr] = 2 ;
            conteurBarr++;
            break;

        case  0x5a ... 0x73: // [11cm - 21cm] proche 0x40 0x5c
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
