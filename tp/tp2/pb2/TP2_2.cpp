#include <avr/io.h> 
#define F_CPU 8000000UL
#include <util/delay.h> 



/*
ETAT PRESENT  |  D      |  ETAT SUIVANT  |  SORTIE A
INIT          |  0      |  INIT          |  couleur rouge (10)
INIT          |  1      |  EA            |  couleur ambre (10) & (01)
EA            |  0      |  EA            |  couleur verte (01)
EA            |  1      |  EB            |  couleur rouge (10)
EB            |  0      |  EB            |  aucune couleur (00)
EB            |  1      |  EC            |  couleur verte (01)
EC            |  0      |  INIT          |  couleur rouge (10)
*/



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

bool antirebound_function(){

    const double anti_REBOUND=10;
    int signal1=PIND;
    _delay_ms(anti_REBOUND);

    int signal2=PIND;
    if (signal1==signal2){
        return true;
    }
    
    return false;


}
int main(){

    DDRA = 0xff; // PORT A est en mode sortie
    DDRD = 0x00;

    enum class ETAT { INIT,EA,EB,EC}; 
    ETAT systeme = ETAT::INIT;

    while (true)
    {
        if (antirebound_function())
        {   
            switch (systeme)
            {
            case ETAT::INIT:
                if (PIND == 0x00)
                {
                    ROUGE();
                }
                if (PIND == 0x04)
                {
                    while (PIND & 0x04)
                    {
                        AMBRE();                   
                    }
                    systeme=ETAT::EA;
                    
                }
                
                break;

            case ETAT::EA:
                if (PIND & 0x00)
                {
                    VERT();
                }
                if (PIND & 0x04)
                {
                    while (PIND & 0x04)
                    {                        
                        ROUGE();
                    }
                    systeme=ETAT::EB;
                    
                }
                
                break;

            case ETAT::EB:
                if (PIND == 0x00)
                {
                    ETEINT();
                }
                if (PIND & 0x04)
                {
                    while (PIND & 0x04)
                    {                        
                        VERT();
                    }
                    systeme=ETAT::INIT;
                    
                }
                
                break;

            case ETAT::EC:
                if (PIND == 0x00)
                {
                    ROUGE();
                    systeme=ETAT::INIT;
                }
                
                break;


            }
                
        }
    }
    

    return 0;
}


    

