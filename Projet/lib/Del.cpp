#include "Del.h"

Del::Del()
{}

Del::~Del()
{}


bool Del::antirebound_fonction(){

    const double anti_REBOUND=10;
    int signal1=PIND;
    _delay_ms(anti_REBOUND);

    int signal2=PIND;
    if (signal1==signal2){
        return true;
    }
    
    return false;
}
void Del::clignote(volatile uint8_t* port, int delai)
{
    int n = int(delai/250);
    for(uint8_t i = 0 ; i < n ; i++ )
    {
        rouge(port);
        _delay_ms(125);
        eteint(port);
        _delay_ms(125);
    }
    eteint(port);
}

void Del::rouge(volatile uint8_t* port)
{
    *port&=~_BV(0);
    *port|=_BV(1);
}

void Del::vert(volatile uint8_t* port)
{
    *port &= ~_BV(1);
    *port |= _BV(0);
}

void Del::ambre(volatile uint8_t* port,int delai)
{
    int n = int(delai/8);
    for(uint8_t i =0 ; i<n;i++)
    {
        Del::rouge(port);
        _delay_ms(4);
        Del::vert(port);
        _delay_ms(8);
    }
    eteint(port);
    
}
void Del::eteint(volatile uint8_t* port)
{
    *port &= ~_BV(1);
    *port &= ~_BV(0);
}
