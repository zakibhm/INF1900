#include <avr/io.h> 
#define F_CPU 8000000UL
#include <util/delay.h> 

void ROUGE(){
    PORTA&=~(1<<PA0);
    PORTA|=(1<<PA1);
}

void VERT() {
    PORTA&=~(1<<PA1);
    PORTA|=(1<<PA0);
}
void ETEINT(){
    PORTA&=~(1<<PA0);
    PORTA&=~(1<<PA1);
}

void AMBRE(){
    PORTA&=~(1<<PA0);
    PORTA|=(1<<PA1);
    _delay_us(1);
    PORTA&=~(1<<PA1);
    PORTA|=(1<<PA0);
    _delay_us(4);                   
}


int main(){

    DDRA = 0xff; // PORT A est en mode sortie
    ETEINT();
    _delay_ms(2000);
    for(int i=0;i<120;i++)
    {
        ROUGE();
        _delay_ms(100/24);
        ETEINT();
        _delay_ms(100/8);
    }
    ETEINT();    
    /*for(int i=0;i<120;i++)
    {
        ROUGE();
        _delay_ms(100/12);
        ETEINT();
        _delay_ms(100/12);
    }
    for(int i=0;i<120;i++)
    {
        ROUGE();
        _delay_ms(100/8);
        ETEINT();
        _delay_ms(100/24);
    }

    ROUGE();
    _delay_ms(2000);

    ETEINT();
    _delay_ms(2000);
    for(int i=0;i<800;i++)
    {
        ROUGE();
        for(int j=0;j<625;j++)
            _delay_us(1);
        ETEINT();
        for(int j=0;j<1875;j++)
            _delay_us(1);
    }   
    for(int i=0;i<800;i++)
    {
        ROUGE();
        _delay_ms(10/8);
        ETEINT();
        _delay_ms(10/8);
    }
    for(int i=0;i<800;i++)
    {
        ROUGE();
        _delay_ms(30/16);
        ETEINT();
        _delay_ms(10/16);
    }

    ROUGE();
    _delay_ms(2000);
    ETEINT();*/
    

    return 0;
}
