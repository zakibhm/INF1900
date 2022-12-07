#define F_CPU 8000000
#include "Controleur.h"

int main()
{
    Controleur controleur ;
    controleur.initialisationbreadBoard();
    controleur.initialisationButtonPoussoir();

    while(true)
    {
        controleur.SelectionnerPartie();
    }    

    return 0 ;
}



