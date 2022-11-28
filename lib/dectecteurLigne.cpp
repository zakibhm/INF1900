#include "detecteurLigne.h"


DetecteurLigne::DetecteurLigne() 
{
    DDRC = modeEntree;
    DDRB = 0xff ;
}



DetecteurLigne::~DetecteurLigne()
{}




void DetecteurLigne::masquerEntree()
{
    entree = PINC ;
    entree &= 0x1f & entree ;
}


bool DetecteurLigne::getDoublechemin()
{
    return doubleChemin ;
}


// void DetecteurLigne::lireCapteur()
// {
//     delCompteur = 0 ;
//     capteur1 = (PINC & 16);
//     if(capteur1)    {delCompteur++ ; }
//     capteur2 = (PINC & 8) ;
//     if(capteur2)    {delCompteur++ ; }
//     capteur3 = (PINC & 4) ;
//     if(capteur3)    {delCompteur++ ; }
//     capteur4 = (PINC & 2) ;
//     if(capteur4)    {delCompteur++ ; }
//     capteur5 = (PINC & 1) ;
//     if(capteur5)    {delCompteur++ ; }
// }


bool DetecteurLigne::getPoint_S()
{
    return point_S_ ;
}

bool DetecteurLigne::getPoint_B()
{
    return point_B_ ;
}

// void DetecteurLigne::detecterLigne2()

// {
//     lireCapteur();
//     switch (delCompteur)
//     {
//     case 1 :
//         if(capteur1)
//         {
//             moteur.tournerDroite();
//         }
//         else if (capteur2)
//         {
//             moteur.tournerDroite();
//         }
//         else if (capteur3)
//         {
//             moteur.avancerMoteur();
//         }

//         else if (capteur4)
//         {
//             moteur.tournerGauche();
//         }
//         else if (capteur5)
//         {
//             moteur.tournerGauche();
//         }
//         break;
    
//     case 2 :
//         if(capteur4 && capteur3)
//         {
//             moteur.avancerMoteur() ;
//         }

//         else if (capteur5 && capteur3)
//         {
//             moteur.avancerMoteur() ;
//         }

//         else if (capteur1 && capteur2)
//         {
//             moteur.tournerDroite();
//         }
//         else if(capteur5 && capteur4)
//         {
//             moteur.tournerGauche();
//         }

//     case 3 :
//         if(capteur1 && capteur2 && capteur3 )
//         {
//             moteur.tournerDroite90() ;
//         }
//         else if (capteur3 && capteur4 && capteur5)
//         {
//             moteur.tournerGauche90() ;
//         }

//         else if (capteur2 && capteur3 && capteur4 )
//         {
//             moteur.avancerMoteur();
//         }
//     default:
//         break;
//     }

// }

void DetecteurLigne::detecterLigne()

{   
    Son son ;
    masquerEntree();
    switch (entree)
        {
            case 0b00000001 :
                moteur.tournerGauche(150,115);
                break;

            case 0b00000010 :
                moteur.tournerGauche(140,115);
                break ;

            case 0b00000011 :
                moteur.tournerGauche(145,115);
                break;

            case 0b00001000 :
                moteur.tournerDroite(115,140);
                break;

            case 0b000010000 :
                moteur.tournerDroite(115,150);
                break;

            case 0b00011000 :
                moteur.tournerDroite(115,145);
                break;

            case 0b00000100 :
                moteur.avancerMoteur();
                break;

            case 0b00001110 :
                del.rouge(&PORTB);
                moteur.avancerMoteur();
                doubleChemin = true ;
                break;

            case 0b00000110 :
                moteur.tournerGauche(120,100);
                break;

            case 0b00001100 : 
                moteur.tournerDroite(100,120);
                break;

            case 0b00011111: 
                moteur.arreterMoteur();
                break;


            case 0b00011011 :
                //del.rouge(&PORTB);
                son.jouerSon(110) ;
                _delay_ms(300);
                son.arreterSon();
                doubleChemin = true ;
                break;
            case 0b00011101 :
                //del.rouge(&PORTB);
                son.jouerSon(110) ;
                _delay_ms(300);
                son.arreterSon();
                doubleChemin = true ;
                break;
            case 0b00010111 :
                //del.rouge(&PORTB);
                son.jouerSon(110) ;
                _delay_ms(300);
                son.arreterSon();
                doubleChemin = true ;
                break;
            case 0b00010011 :
                //del.rouge(&PORTB);
                son.jouerSon(110) ;
                _delay_ms(300);
                son.arreterSon();
                doubleChemin = true ;
                break;
            case 0b00011001 :
                //del.rouge(&PORTB);
                son.jouerSon(110) ;
                _delay_ms(300);
                son.arreterSon();
                doubleChemin = true ;
                break;
            
            case 0b00010001 :
                //del.rouge(&PORTB);
                son.jouerSon(110) ;
                _delay_ms(300);
                son.arreterSon();
                doubleChemin = true ;
                break ;
                    
            case 0b0000111 : 
                //del.rouge(&PORTB);
                _delay_ms(250);
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
                    moteur.avancerMoteur(140,147);
                    _delay_ms(270);
                    while (true)
                    {
                        moteur.tournerGauche90();
                        entree = PINC ;
                        entree &= 0x1f & entree ;
                        if(entree & 0x04)
                            break ;
                    }
                    
                }
                    
                break;          
                        

            case 0b00001111 : 
                
                _delay_ms(250);
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
                    moteur.avancerMoteur(140,147);
                    _delay_ms(270);
                    while (true)
                    {
                        moteur.tournerGauche90();
                        entree = PINC ;
                        entree &= 0x1f & entree ;
                        if(entree & 0x04)
                            break ;
                    }
                    
                }
                    
                break;  

            case 0b00011100 : 
                del.rouge(&PORTB);
                _delay_ms(250);
                masquerEntree();

                if ((entree == 0b00011111) && (point_B_)) // Point S
                {
                    moteur.avancerMoteur();
                    point_S_ = true ;
                }

                else if(entree == 0b00000000) 
                {
                    doubleChemin = true ;
                }

                else if ( (entree == 0b00011111) && !(point_B_) ) // point B
                {
                    moteur.arreterMoteur();
                    point_B_ = true ;
                }

                
                
                else {
                    moteur.avancerMoteur(140,147);
                    _delay_ms(270);
                    while (true)
                    {
                        moteur.tournerDroite90();
                        entree = PINC ;
                        entree &= 0x1f & entree ;
                        if(entree & 0x04)
                            break ;
                    }
                    
                }
                    
                break;  

            case 0b00011110 : 
                _delay_ms(250);
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
                    moteur.avancerMoteur(140,147);
                    _delay_ms(270);
                    while (true)
                    {
                        moteur.tournerDroite90();
                        entree = PINC ;
                        entree &= 0x1f & entree ;
                        if(entree & 0x04)
                            break ;
                    }
                    
                }
                    
                break;  
            
            default:
                moteur.arreterMoteur();
                break;
        }
}

