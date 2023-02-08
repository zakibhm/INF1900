#pragma once 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>


class Uart
{
public :
    Uart();

    ~Uart();

    void transmissionUART( uint8_t donnee );

    uint8_t receptionUART();

    void envoyerMessage(const char* message);

};