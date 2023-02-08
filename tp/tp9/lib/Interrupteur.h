#pragma once
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

class Interrupteur
{
public :
    Interrupteur();
    
    ~Interrupteur();

    void initialisationInterruption();

    bool antiRebound();

};

