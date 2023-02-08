#include "photoresistance.h"


const uint8_t modeEntree = 0x00 ;
const uint8_t modeSortie = 0xff ;
can convertisseurAnalogique;
Del del;

Photoresistance::Photoresistance()
{
    DDRA = modeEntree; 
    DDRB = modeSortie;
}

Photoresistance::~Photoresistance()
{}


void Photoresistance::chargerEntree()
{
    lumiereNum = (convertisseurAnalogique.lecture(0x00) >> 2);
}

void Photoresistance::affichage()
{
    while (true)
    {
        switch (lumiereNum)
        {
        case  0x00 ... 0xE0:
            del.vert(&PORTB);
            break;
    
        case 0xE1 ... 0xEE :
            del.ambre(&PORTB);
            break;

        default:
            del.rouge(&PORTB);
            break;
        }
    }
}