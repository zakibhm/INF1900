#include <avr/io.h> 
#define F_CPU 8000000UL
#include <util/delay.h> 
#include <avr/interrupt.h>



void initialisationUART ( void ) {

// 2400 bauds. Nous vous donnons la valeur des deux

// premiers registres pour vous éviter des complications.

UBRR0H = 0;
UBRR0L = 0xCF;

// permettre la réception et la transmission par le UART0

UCSR0A |= (1<<MPCM0) ;
UCSR0B |= (1<<RXEN0) | (1<<TXEN0) ;

// Format des trames: 8 bits, 1 stop bits, sans parité

UCSR0C |= ~(1<<UPM01) | ~(1<<UPM00) | ~(1<<USBS0) | ~(1<<UCSZ02)| (1<<UCSZ01) | (1<<UCSZ00);

}

// Du USART vers le PC
void transmissionUART ( uint8_t donnee ) {

/* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) );
    /* Put data into buffer, sends the data */
    UDR0 = donnee ;

}

/*
#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#include "memoire24.hpp"


const uint8_t ALL_OUT = 0xff;
const uint8_t ALL_IN  = 0x00;


enum Color
{
    GREEN = 1 << PORTA0,
    RED = 1 << PORTA1,
    OFF = 0
};


void initialisationUART()
{
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0B = 1 << TXEN0;
}

void transmit(uint8_t data)
{
    // Wait for empty transmit buffer 
    while ( !( UCSR0A & (1<<UDRE0)) );
    // Put data into buffer, sends the data 
    UDR0 = data;
}



void pb1()
{
    const char* TXT = "P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
    
    Memoire24CXXX mem;
    
    mem.ecriture(0x00, (uint8_t*)TXT, strlen(TXT));
    
    char result[256];
    
    mem.lecture(0x00, (uint8_t*)result, strlen(TXT));
    
    if (strcmp(TXT, result) == 0) PORTA = Color::GREEN;
    else Color::RED;
}

void printStr(char* str)
{
    char* c = str;
    while (*c != 0)
    {
        transmit(*c);
        c++;
    }
}

void printStr(char* str)
{
    for ( uint8_t i=0; i < strlen(str); i++ ) 
        transmit(str[i]);
}

int main()
{
    initialisationUART();
    
    char mots[21] = "Le robot en INF1900\n";

    uint8_t i, j;

    for ( i = 0; i < 100; i++ ) {
        for ( j=0; j < 20; j++ ) {
            transmit( mots[j] );
        }
    }   
    
    
    while (true)
    {
        
    }
    
    return 0;
}*/