#include <avr/io.h> 
#define F_CPU 8000000UL
#include <util/delay.h> 
#include <avr/interrupt.h>


void rouge(){
    PORTA&=~(1<<PA0);
    PORTA|=(1<<PA1);
}

void ajustementPwm ( uint16_t duree) {
    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5
    // page 130 de la description technique du ATmega324PA)
    OCR1A = duree ;
    OCR1B = duree ;

    // division d'horloge par 8 - implique une fréquence de PWM fixe
    TCCR1A |=(1<<WGM10) |(1<<COM1A1)|(1<<COM1B1) ;
    TCCR1B |= (1<<CS11);
    TCCR1C = 0;
}
void generateur_des_signeaux(){ 

    ajustementPWM (0); //qnd OCR1n est set a 0, le pwm est automatiquement a 0%, il est mit a 0 la premiere fois que le trnt = 0 = ocr1a=ocr1b et apres il bge plus mm si trnt reegale = 0
        _delay_ms(2000);
        
        ajustementPWM (64); //pas oublier que le pwm est en non inverted
        _delay_ms(2000);
        
        ajustementPWM (128); // mm que 64
        _delay_ms(2000);
        
        ajustementPWM (191); // mm que 128
        _delay_ms(2000);
        
        ajustementPWM (255); //mm que 0 mais qnd ocr1n est set a la valeur top (255), alors il est mi directement a 100% des que le timer commence(le timer commence a 0 et la valeur de ocr1n = 255, mais mm a sa sa le met directement a 100%) et il ne bge plus par la suite
        _delay_ms(2000);
}

int main()
{
    DDRD = 0xff;
    while(true)  // boucle sans fin
    {
        generateur_des_signeaux();
    } 
    return 0;
}