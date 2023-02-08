#include <avr/io.h> 
#define F_CPU 800000
#include <util/delay.h> 



/*
ETAT PRESENT  |  D      |  ETAT SUIVANT  |  SORTIE A
INIT          |  0      |  INIT          |  0
INIT          |  1      |  EA            |  0
EA            |  0      |  EA            |  0
EA            |  1      |  EB            |  0
EB            |  0      |  EB            |  0
EB            |  1      |  EC            |  0
EC            |  X      |  INIT          |  1
*/


bool antirebound_function(){

    const double anti_REBOUND=10;
    int signal1=PIND;
    _delay_ms(anti_REBOUND);

    int signal2=PIND;
    if (signal1==signal2 && PIND==0x04){
        return true;
    }
    
    return false;
}


int main()
{   
    const double temps=20000;
    DDRA = 0xff; // PORT A est en mode sortie
    DDRD = 0x00;

    enum class ETAT { INIT,EA,EB,EC}; 
    ETAT systeme = ETAT::INIT;
    bool button_removed=false;

    while (true)
    {
        switch (systeme)
            {
                case ETAT::INIT:
                    PORTA&=~(1<<PA0);
                    if (!button_removed && antirebound_function()) {
                        button_removed=true;
                    }
                    if (button_removed && !antirebound_function())
                    {
                        systeme=ETAT::EA;
                        button_removed=false;
                        
                    }   
                    break;

                
                case ETAT::EA:
                    if (!button_removed && antirebound_function()) {
                        button_removed=true;
                    }
                    if (button_removed && !antirebound_function())
                        {
                            systeme=ETAT::EB;
                            button_removed=false;
                            
                        }   
                        break;

                case ETAT::EB:
                    if (!button_removed && antirebound_function()) {
                        button_removed=true;
                    }
                    if (button_removed && !antirebound_function())
                        {
                            
                            systeme=ETAT::EC;
                            button_removed=false;
                        }   
                        break;

                case ETAT::EC:
                    systeme=ETAT::INIT; 
                    PORTA|=(1<<PA0);
                    _delay_ms(temps);
                    PORTA&=(0<<PA0);
                
                    break;
            }    
            
        }
            
    return 0;

}

