#include "Uart.h"
Uart::Uart()
{
    UBRR0H = 0;
    UBRR0L =0xCF;

    UCSR0A |= (1<<RXC0)|(1<<TXC0);
    UCSR0B |= (1<<RXEN0) | (1 << TXEN0) ;
    UCSR0C |= (1<< UCSZ01) | (1<<UCSZ00);
}

Uart::~Uart()
{}


void Uart::transmissionUART(uint8_t donnee)
{
    do{

    }
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = donnee ;
}

uint8_t Uart::receptionUART(){
    do{

    }
    while(!(UCSR0A & (1<<RXC0)));
    return(UDR0);
}

void Uart::envoyerMessage(const char* message){
    int i = 0;
    while(message[i] != '\0'){
        Uart::transmissionUART(message[i++]);
    }
}