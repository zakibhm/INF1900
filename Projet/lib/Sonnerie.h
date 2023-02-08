
#pragma once
#define F_CPU 8000000
#include <avr/io.h>


class Son 
{
public :  
    Son();

    ~Son();

    void jouerSon(double frequence);

    void arreterSon();

};