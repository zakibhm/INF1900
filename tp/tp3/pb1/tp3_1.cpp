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

int main()
{   
    DDRA = 0xff; // PORT A est en mode sortie
    int a=1000;
    int b=1000;

    for (int i=0;i<3000;i++)
    {
         
        _delay_ms(1);
        ROUGE();
        for (int i=0;i<a;i++)
            {
               _delay_us(1); 
            }

        ETEINT();
        for (int i=0;i<b-a;i++)
            {
               _delay_us(1); 
            }  
        a-=1;          
    }
            
    return 0;

}

