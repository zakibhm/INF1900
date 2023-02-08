#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h> 
#include "debug.h"
#include "Uart.h"
#include <memoire_24.h>



int main()
{
    Memoire24CXXX memoire ;
    Uart uart;

    uint16_t adresse =0x0000 ;
    uint8_t donnee1 ;
    uint8_t donnee2 ;
    uint16_t tailleFichier ;
    donnee1 = uart.receptionUART();
    donnee2 = uart.receptionUART();
    tailleFichier = static_cast<uint16_t>(donnee1 << 8) | donnee2 ;
    uint8_t byteCode[tailleFichier];
    byteCode[0]=donnee1 ;
    byteCode[1]=donnee2 ;
    for (uint8_t i=2;i<tailleFichier;i++){
        byteCode[i] = uart.receptionUART();
    }
    memoire.ecriture(adresse,byteCode, tailleFichier);//ecrire le tableau qui contient tout les instructions et les operandes de  notre bytecode
    return 0;
}
