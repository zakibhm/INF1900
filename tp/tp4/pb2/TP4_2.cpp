#include <avr/io.h> 
#define F_CPU 8000000UL
#include <util/delay.h> 
#include <avr/interrupt.h>


volatile uint8_t gMinuterieExpiree;
volatile uint8_t gBoutonPoussoir;

void rouge(){
    PORTA&=~(1<<PA0);
    PORTA|=(1<<PA1);
}

void vert() {
    PORTA&=~(1<<PA1);
    PORTA|=(1<<PA0);
}
void eteint(){
    PORTA&=~(1<<PA0);
    PORTA&=~(1<<PA1);
}
bool antirebound_fonction(){

    const double anti_REBOUND=10;
    int signal1=PIND;
    _delay_ms(anti_REBOUND);

    int signal2=PIND;
    if (signal1==signal2){
        return true;
    }
    
    return false;
}

void partirMinuterie ( uint16_t duree ) {
    gMinuterieExpiree = 0;
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    TCNT1 = 0 ;//initializing Timer/Counter register on 0
    
    OCR1A = duree;//Output Compare Register 1 16 bits
    TCCR1A |= (1<<WGM12)|(1<<WGM12);    
    // setting Timer/Counter register (8bits) on 'clear Timer on compar' Mode 
    //Bit 7         6     5     4     3    2    1    0
    //   COM1A1 COM1A0 COM1B1 COM1B0  –    –  WGM11 WGM10
    //WGM : Wave form Generation Mode which had been sitted on CTC mode
    
    TCCR1B |= (1<<CS12)|(1<<CS10);//setting Timer/Counter register (8bits) on 1024 prescalar
    //Bit 7     6     5     4     3     2    1    0
    // ICNC1 ICES1 RTGEN WGM13  WGM12  CS12 CS11 CS10 
    //WGMn3:2: Waveform Generation Mode
    // Bit 2:0 – CSn2:0: Clock Select, which had been selected on 1024 prescalar value


    TCCR1C = 0;
    TIMSK1 |=(1<<OCIE1A);// Timer/Counter Interrupt Mask Register
    //Bit 7     6     5     4     3      2      1     0
    //    –     –    ICIE1   –    –   OCIE1B OCIE1A TOIE1 
    //When the OCIE1A bit is written to one, and the I-bit in the Status Register is set, the
    //Timer/Counter Compare Match A interrupt is enabled
    //
}
void initialisation ( void ) {
    cli ();//disabling all external interruptions 
    DDRA = 0xff;
    DDRD = 0x00;
    EIMSK |= (1 << INT0); //Dit au microcontroleur quil px se faire interrompre
    EICRA |= (1 << ISC00)|(1<<ISC01); //Dit au microcontroleur quil px se faire interrompre que par des fronts montants/descendants
    sei ();
}

ISR ( INT0_vect ) {
    // anti-rebond
    if(antirebound_fonction() && PIND == 0x04)
        gBoutonPoussoir = 1;   
}

ISR ( TIMER1_COMPA_vect ) {
    gMinuterieExpiree = 1;

}
int main()
{
    initialisation ();
    _delay_ms(10000);
    rouge();
    _delay_ms(100);
    eteint();
    
    partirMinuterie(7812);//QUESTION: esq on est capable de passer une paramatere reel?
    do {

    } while ( gMinuterieExpiree == 0 && gBoutonPoussoir == 0 );
    // Une interruption s'est produite. Arrêter toute
    // forme d'interruption. Une seule réponse suffit.
    cli ();
    // Verifier la réponse
    if(gMinuterieExpiree == 1 )
        rouge();
    else
        vert();
    return 0;
}