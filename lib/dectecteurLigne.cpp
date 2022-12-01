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

void DetecteurLigne::setDoublechemin(bool var)
{
    doubleChemin = var ;
}


bool DetecteurLigne::getPoint_S()
{
    return point_S_ ;
}

void DetecteurLigne::setPoint_S(bool valeure)
{
    point_S_ = valeure;
}

bool DetecteurLigne::getPoint_B()
{
    return point_B_ ;
}

Son son ;

uint8_t* DetecteurLigne::getTabBarrieres()
{
    return tableaux_des_barrieres ;
}


bool DetecteurLigne::getMilieu()
{
    return milieu ;
}


void DetecteurLigne::detecteurDistance()
{
    int moyenne = 0,somme = 0 ;
    for(int i =0;i<50;i++)
    {
        distance = (convertisseurAnalogique.lecture(0x00) >>2);
        somme+= distance ;
    }
    moyenne = int(somme/50) ;
    switch (moyenne)
    {
        
        case 27 ... 33: // [43cm - 53cm] loin //0x15 0x1C   30 ... 40
            _delay_ms(45);
            distance = (convertisseurAnalogique.lecture(0x00) >>2);
            if(distance > 33)
            {
                moteur.arreterMoteur();
                del.vert(&PORTB);
                sonnerie.jouerSon(frequence[2]);
                _delay_ms(1100);
                sonnerie.arreterSon();
                moteur.avancerMoteur(140,150);
                _delay_ms(1000);

                tableaux_des_barrieres[conteurBarr] = 1 ;
                conteurBarr++;
            }
            else 
            {
                moteur.arreterMoteur();
                sonnerie.jouerSon(frequence[5]);
                _delay_ms(1000);
                sonnerie.arreterSon();
                moteur.avancerMoteur(115,125);
                _delay_ms(900);
                del.rouge(&PORTB);
                tableaux_des_barrieres[conteurBarr] = 2 ;
                conteurBarr++;
            }
            
            break;

        case  34 ... 120 : // [11cm - 21cm] proche 0x40 0x5c     60 ... 77
            moteur.arreterMoteur();
            del.vert(&PORTB);

            
            sonnerie.jouerSon(frequence[5]);
            _delay_ms(1000);
            sonnerie.arreterSon();
            moteur.avancerMoteur(115,125);
            _delay_ms(900);

            tableaux_des_barrieres[conteurBarr] = 1 ;
            conteurBarr++;
            break;

        default: // rien pour detecter 
            sonnerie.arreterSon() ;
            moteur.avancerMoteur();

            break;


    }
}


void DetecteurLigne::detecterLigne(char* partie, char* direction)

{   
    
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
                // del.rouge(&PORTB);
                doubleChemin = true ;
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
                
                doubleChemin = true ;
                break;
            case 0b00011101 :
                
                doubleChemin = true ;
                break;
            case 0b00010111 :
                
                doubleChemin = true ;
                break;
            case 0b00010011 :
                
                doubleChemin = true ;
                break;
            case 0b00011001 :
                
                doubleChemin = true ;
                break;
            
            case 0b00010001 :
                
                doubleChemin = true ;
                break ;
                    
            case 0b0000111 : 
                //del.rouge(&PORTB);
                _delay_ms(150);
                masquerEntree();

                if(direction == "deuxDirection" || direction == "Gauche")
                { 
                        milieu = true ;
                        moteur.avancerMoteur(140,147);
                        //_delay_ms(270);
                        while (true)
                        {
                            moteur.tournerGauche90();
                            entree = PINC ;
                            entree &= 0x1f & entree ;
                            if(entree & 0x04){
                                 break ;
                            }
                               
                        }
                }

                else if ((entree == 0b00011111) && partie == "PartieB") // Point S
                {
                    moteur.avancerMoteur();
                    point_S_ = true ;
                }

                else if ( (entree == 0b00011111) && partie == "PartieA") // point B
                {
                    moteur.arreterMoteur();
                    point_B_ = true ;
                }
                    
                break;          
                        

            case 0b00001111 : 
                
                _delay_ms(150);
                masquerEntree();

                if(direction == "deuxDirection" || direction == "Gauche")
                { 
                        milieu = true ;
                        moteur.avancerMoteur(140,147);
                        //_delay_ms(270);
                        while (true)
                        {
                            moteur.tournerGauche90();
                            entree = PINC ;
                            entree &= 0x1f & entree ;
                            if(entree & 0x04){
                                 break ;
                            }
                               
                        }
                }

                else if ((entree == 0b00011111) && partie == "PartieB") // Point S
                {
                    moteur.avancerMoteur();
                    point_S_ = true ;
                }

                else if ( (entree == 0b00011111) && partie == "PartieA") // point B
                {
                    moteur.arreterMoteur();
                    point_B_ = true ;
                }
                    
                break;  

            case 0b00011100 : 
                //del.rouge(&PORTB);
                _delay_ms(150);
                masquerEntree();
                
                if(direction == "Droite" || direction == "deuxDirection")
                    {
                        milieu = true ;
                        moteur.avancerMoteur(140,147);
                        //_delay_ms(270);
                        while (true)
                        {
                            moteur.tournerDroite90();
                            entree = PINC ;
                            entree &= 0x1f & entree ;
                            if(entree & 0x04)
                            {
                                break ;
                            }
                                
                        }
                    }

                else if ((entree == 0b00011111) && partie == "PartieB") // Point S
                {
                    moteur.avancerMoteur();
                    point_S_ = true ;
                }

                else if ( (entree == 0b00011111) && partie == "PartieA") // point B
                {
                    moteur.arreterMoteur();
                    point_B_ = true ;
                } 

                break;  

            case 0b00011110 : 
                _delay_ms(150);
                masquerEntree();

                if(direction == "Droite" || direction == "deuxDirection")
                    {
                        milieu = true ;
                        moteur.avancerMoteur(140,147);
                        //_delay_ms(270);
                        while (true)
                        {
                            moteur.tournerDroite90();
                            entree = PINC ;
                            entree &= 0x1f & entree ;
                            if(entree & 0x04)
                            {
                                break ;
                            }
                                
                        }
                    }

                else if ((entree == 0b00011111) && partie == "PartieB") // Point S
                {
                    moteur.avancerMoteur();
                    point_S_ = true ;
                }

                else if ( (entree == 0b00011111) && partie == "PartieA") // point B
                {
                    moteur.arreterMoteur();
                    point_B_ = true ;
                } 

                break;  

            
            default:
                moteur.arreterMoteur();
                break;
        }
}

