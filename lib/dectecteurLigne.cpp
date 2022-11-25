#include "detecteurLigne.h"



DetecteurLigne::DetecteurLigne() 
{
    DDRC = modeEntree;
}



DetecteurLigne::~DetecteurLigne()
{}

void DetecteurLigne::masquerEntree()
{
    entree = PINC ;
    entree &= 0x1f & entree ;
}

bool DetecteurLigne::getPoint_S()
{
    return point_S_ ;
}

bool DetecteurLigne::getPoint_B()
{
    return point_B_ ;
}


void DetecteurLigne::dectcterLigne()

{ 
    masquerEntree();
    switch (entree)
        {
            case 0b00000001 :
                moteur.tournerGauche();
                break;

            case 0b00000010 :
                moteur.tournerGauche();
                break ;

            case 0b00000011 :
                moteur.tournerGauche();
                break;

            case 0b00001000 :
                moteur.tournerDroite();
                break;

            case 0b000010000 :
                moteur.tournerDroite();
                break;

            case 0b00011000 :
                moteur.tournerDroite();
                break;

            case 0b00000100 :
                moteur.avancerMoteur();
                break;

            case 0b00001110 :
                moteur.avancerMoteur();
                break;

            case 0b00000110 :
                moteur.avancerMoteur();
                break;

            case 0b00001100 : 
                moteur.avancerMoteur();
                break;

            case 0b00011111: 
                moteur.arreterMoteur();
                break;




            case 0b00000111 :
                _delay_ms(300);
                masquerEntree();

                if ((entree == 0b00011111) && (point_B_)) // Point S
                {
                    moteur.avancerMoteur();
                    point_S_ = true ;
                }

                else if ( (entree == 0b00011111) && !(point_B_) ) // point B
                {
                    moteur.arreterMoteur();
                    point_B_ = true ;
                }
                
                else {
                    moteur.avancerMoteur();
                    _delay_ms(170);
                    while (!(entree & 0x04))
                    {
                        moteur.tournerGauche90();
                        entree = PINC ;
                        entree &= 0x1f & entree ;
                    }
                    
                }
                    
                break;          
                        

            case 0b00001111 : 

                _delay_ms(300);
                masquerEntree();

                if ((entree == 0b00011111) && (point_B_)) // Point S
                {
                    moteur.avancerMoteur();
                    point_S_ = true ;
                }

                else if ( (entree == 0b00011111) && !(point_B_) ) // point B
                {
                    moteur.arreterMoteur();
                    point_B_ = true ;
                }
                
                else {
                    moteur.avancerMoteur();
                    _delay_ms(170);
                    while (!(entree & 0x04))
                    {
                        moteur.tournerGauche90();
                        entree = PINC ;
                        entree &= 0x1f & entree ;
                    }
                    
                }
                    
                break;  

            case 0b00011100 : 

                _delay_ms(300);
                masquerEntree();

                if ((entree == 0b00011111) && (point_B_)) // Point S
                {
                    moteur.avancerMoteur();
                    point_S_ = true ;
                }

                else if ( (entree == 0b00011111) && !(point_B_) ) // point B
                {
                    moteur.arreterMoteur();
                    point_B_ = true ;
                }
                
                else {
                    moteur.avancerMoteur();
                    _delay_ms(170);
                    while (!(entree & 0x04))
                    {
                        moteur.tournerDroite90();
                        entree = PINC ;
                        entree &= 0x1f & entree ;
                    }
                    
                }
                    
                break;  

            case 0b00011110 : 
                _delay_ms(300);
                masquerEntree();

                if ((entree == 0b00011111) && (point_B_)) // Point S
                {
                    moteur.avancerMoteur();
                    point_S_ = true ;
                }

                else if ( (entree == 0b00011111) && !(point_B_) ) // point B
                {
                    moteur.arreterMoteur();
                    point_B_ = true ;
                }
                
                else {
                    moteur.avancerMoteur();
                    _delay_ms(170);
                    while (!(entree & 0x04))
                    {
                        moteur.tournerDroite90();
                        entree = PINC ;
                        entree &= 0x1f & entree ;
                    }
                    
                }
                    
                break;  
            
            default:
                moteur.arreterMoteur();
                break;
        }
}

