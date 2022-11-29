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




bool DetecteurLigne::getPoint_S()
{
    return point_S_ ;
}

bool DetecteurLigne::getPoint_B()
{
    return point_B_ ;
}



void DetecteurLigne::detecterLigne(char* partie)

{   
    Son son ;
    masquerEntree();
    switch (entree)
        {
            case 0b00000001 :
                while (true)
                    {
                        moteur.tournerGauche90();
                        entree = PINC ;
                        entree &= 0x1f & entree ;
                        if(entree & 0x04)
                            break ;
                    }
                //moteur.tournerGauche(150,115);
                break;

            case 0b00000010 :
                moteur.tournerGauche(140,115);
                break ;

            case 0b00000011 :
                while (true)
                    {
                        moteur.tournerGauche90();
                        entree = PINC ;
                        entree &= 0x1f & entree ;
                        if(entree & 0x04)
                            break ;
                    }
                //moteur.tournerGauche(145,115);
                break;

            case 0b00001000 :
                moteur.tournerDroite(115,140);
                break;

            case 0b000010000 :
                while (true)
                    {
                        moteur.tournerDroite90();
                        entree = PINC ;
                        entree &= 0x1f & entree ;
                        if(entree & 0x04)
                            break ;
                    }
                //moteur.tournerDroite(115,150);
                break;

            case 0b00011000 :
                while (true)
                        {
                            moteur.tournerDroite90();
                            entree = PINC ;
                            entree &= 0x1f & entree ;
                            if(entree & 0x04)
                                break ;
                        }
                //moteur.tournerDroite(115,145);
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
                
                son.jouerSon(110) ;
                _delay_ms(300);
                son.arreterSon();
                doubleChemin = true ;
                break;
            case 0b00011101 :
                
                son.jouerSon(110) ;
                _delay_ms(300);
                son.arreterSon();
                doubleChemin = true ;
                break;
            case 0b00010111 :
                
                son.jouerSon(110) ;
                _delay_ms(300);
                son.arreterSon();
                doubleChemin = true ;
                break;
            case 0b00010011 :
                
                son.jouerSon(110) ;
                _delay_ms(300);
                son.arreterSon();
                doubleChemin = true ;
                break;
            case 0b00011001 :
                
                son.jouerSon(110) ;
                _delay_ms(300);
                son.arreterSon();
                doubleChemin = true ;
                break;
            
            case 0b00010001 :
                
                son.jouerSon(110) ;
                _delay_ms(300);
                son.arreterSon();
                doubleChemin = true ;
                break ;
                    
            case 0b0000111 : 
                //del.rouge(&PORTB);
                _delay_ms(250);
                masquerEntree();

                if ((entree == 0b00011111) && partie == "PartieB") // Point S
                {
                    moteur.avancerMoteur();
                    point_S_ = true ;
                }

                else if ( (entree == 0b00011111) && partie == "PartieA") // point B
                {
                    moteur.arreterMoteur();
                    point_B_ = true ;
                }

                
                
                else {
                    moteur.avancerMoteur(140,147);
                    //_delay_ms(270);
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

                if ((entree == 0b00011111) && partie == "PartieB") // Point S
                {
                    moteur.avancerMoteur();
                    point_S_ = true ;
                }

                else if ( (entree == 0b00011111) && partie == "PartieA") // point B
                {
                    moteur.arreterMoteur();
                    point_B_ = true ;
                }

                
                else {
                    moteur.avancerMoteur(140,147);
                    //_delay_ms(270);
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

                if ((entree == 0b00011111) && partie == "PartieB") // Point S
                {
                    moteur.avancerMoteur();
                    point_S_ = true ;
                }

                else if ( (entree == 0b00011111) && partie == "PartieA") // point B
                {
                    moteur.arreterMoteur();
                    point_B_ = true ;
                }

                else if ( (entree == 0b00011111) && !(point_B_) ) // point B
                {
                    moteur.arreterMoteur();
                    point_B_ = true ;
                }

                
                
                else {
                    moteur.avancerMoteur(140,147);
                    //_delay_ms(270);
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

                if ((entree == 0b00011111) && partie == "PartieB") // Point S
                {
                    moteur.avancerMoteur();
                    point_S_ = true ;
                }

                else if ( (entree == 0b00011111) && partie == "PartieA") // point B
                {
                    moteur.arreterMoteur();
                    point_B_ = true ;
                }
                
                else {
                    moteur.avancerMoteur(140,147);
                    //_delay_ms(270);
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

