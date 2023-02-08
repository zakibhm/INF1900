#include "Controleur.h"

Controleur::Controleur()
{
    initialisationbreadBoard();
    initialisationButtonPoussoir();
}

Controleur::~Controleur()
{}

volatile uint8_t gBoutonPoussoir = 0;
volatile uint8_t gBoutonPoussoirBoard = 0;


void Controleur::initialisationbreadBoard()
{
    cli ();//disabling all external interruptions 
    EIMSK |= (1 << INT1); //Dit au microcontroleur quil px se faire interrompre
    EICRA |= (1 << ISC11)|(1<<ISC10); //Dit au microcontroleur quil px se faire interrompre que par des fronts montants/descendants
    sei ();
}

void Controleur::initialisationButtonPoussoir()
{
    cli ();//disabling all external interruptions 
    EIMSK |= (1 << INT0); //Dit au microcontroleur quil px se faire interrompre
    EICRA |= (1 << ISC00)|(1<<ISC01); //Dit au microcontroleur quil px se faire interrompre que par des fronts montants/descendants
    sei ();
}

ISR ( INT0_vect ) {
    _delay_ms(30);
    gBoutonPoussoir = 1;   
}

ISR ( INT1_vect ) {
    _delay_ms(50);
    gBoutonPoussoirBoard += 1;   
}



void Controleur::SelectionnerPartie()
{
    switch (partieCourante_)
        {
            case Partie::partieA : 
            del_.vert(&PORTB);
            if(gBoutonPoussoir)
            {
                del_.clignote(&PORTB,2000);
                speedyFennec_.partieA();
                gBoutonPoussoir = 0;
            }
            if(gBoutonPoussoirBoard == 1)
            {
                partieCourante_=Partie::partieB ;

            }
            break;


            case Partie::partieB : 
                del_.rouge(&PORTB);
                if(gBoutonPoussoir)
                {
                    del_.clignote(&PORTB,2000);
                    speedyFennec_.partieB();
                    speedyFennec_.partieC();
                    gBoutonPoussoir = 0;
                }
                if(gBoutonPoussoirBoard == 2)
                {
                    partieCourante_=Partie::partieC ;

                }
                break;

            case Partie::partieC :
                del_.ambre(&PORTB,10);
                if(gBoutonPoussoir)
                {
                    del_.clignote(&PORTB,2000);
                    speedyFennec_.partieC();
                    gBoutonPoussoir = 0;
                    gBoutonPoussoirBoard = 0 ;
                    partieCourante_=Partie::partieA ;
                }
                if(gBoutonPoussoirBoard == 3)
                {
                    partieCourante_=Partie::partieA ;
                    gBoutonPoussoirBoard = 0 ;

                }
                break;
        }
}