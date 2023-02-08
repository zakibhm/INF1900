#pragma once
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

class Del 
{
public :

    Del();

    ~Del();

    
    void rouge(volatile uint8_t* port);
    
    void vert(volatile uint8_t* port);
    
    void eteint(volatile uint8_t* port);
    
    void ambre(volatile uint8_t* port);

};