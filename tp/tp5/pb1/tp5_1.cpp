#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h> 
#include "memoire_24.h"
#include <stdio.h>
#include <string.h>
//#include <avr/eeprom.h>
void rouge(){
    PORTA&=~(1<<PA0);
    PORTA|=(1<<PA1);
}

void vert() {
    PORTA&=~(1<<PA1);
    PORTA|=(1<<PA0);
}
int main() {

    DDRA=0xff;
    //vert();
    const char* message = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
    Memoire24CXXX memoire = Memoire24CXXX();
    char resultat[45];
    memoire.ecriture(0x0000,(uint8_t*)message, strlen(message));
    _delay_ms(5);
    memoire.lecture(0x0000,(uint8_t*)resultat, strlen(message));
    if(strcmp(message,resultat)==0){
        vert();
    }
    else {
        rouge();
    }
    return 0;
}