#include "Interrupteur.h"

const uint8_t modeEntree = 0x00 ;
const uint8_t modeSortie = 0xff ;
const uint8_t tempsInterruption = 10 ;

Interrupteur::Interrupteur()
{
    DDRD = modeEntree ;
    DDRA = modeSortie ;
}

Interrupteur::~Interrupteur()
{}

void Interrupteur::initialisationInterruption()
{
    cli();
    
    EIMSK |= (1 << INT0) ;

    EICRA |=(1<<ISC00);

    sei();

}

bool Interrupteur::antiRebound()
{
    if(PIND & 0x04){
        _delay_ms(tempsInterruption);
        if(PIND & 0x04){
            return true;
        }
    }
    return false ;
}