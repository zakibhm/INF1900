#include "Del.h"

Del::Del()
{}

Del::~Del()
{}

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

void Del::ambre(volatile uint8_t* port)
{
    Del::rouge(port);
    _delay_ms(4);
    Del::vert(port);
    _delay_ms(8);
}
void Del::eteint(volatile uint8_t* port)
{
    *port &= ~_BV(1);
    *port &= ~_BV(0);
}
