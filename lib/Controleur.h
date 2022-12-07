#include "robot.h"

class Controleur
{
public :    
    Controleur();

    ~Controleur();

    void SelectionnerPartie();

    void initialisationbreadBoard ( void ) ;

    void initialisationButtonPoussoir ( void ) ;

private :
    enum class Partie {partieA,partieB,partieC}; 
    Partie partieCourante_ = Partie::partieA ;
    Robot speedyFennec_ ;
    Del del_ ;

};