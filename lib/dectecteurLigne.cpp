#include "detecteurLigne.h"


DetecteurLigne::DetecteurLigne() 
{
    DDRA = modeEntree;
    //DDRA |= (1<< PA6) ;
    DDRB = 0xff ;
}



DetecteurLigne::~DetecteurLigne()
{}




void DetecteurLigne::masquerEntree()
{
    entree = PINA ;
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

void DetecteurLigne::setMilieu(bool valeure)
{
    milieu = valeure ;
}


void DetecteurLigne::detecterGauche(bool push, char* partie)
{
    if(push )
    {
        moteur.avancerMoteur();
        _delay_ms(150);
        // if(partie == "PartieB")
        //     _delay_ms(150);

        if (partie == "PartieB_gauche")
             _delay_ms(300);
    }
    while (true)
    {
        // _delay_ms(7);
        // moteur.tournerGauche90();
        if(partie == "PartieB"|| partie == "PartieA" )
        {
            //_delay_ms(8);
            moteur.tournerGauche90();
        }
        else if (partie == "PartieB_gauche")
        {
            moteur.tournerGauche(98,0);
            //moteur.tournerGauche90();
        }
        masquerEntree();
        
        if(entree == 0x02){
                break ;
        }
            
    }
    // del.rouge(&PORTB);
    // _delay_ms(300);
    // del.eteint(&PORTB);
    moteur.avancerMoteur(115,113);
    // if(push && (partie == "PartieA")){
    //     _delay_ms(240);
    // }
    if (push && (partie == "PartieB"))
    {
        _delay_ms(200);
    }

    else if (push && (partie == "PartieB_gauche"))
    {
        _delay_ms(360);
    }
}

void DetecteurLigne::detecterDroite(bool push, char* partie)

{ 
    if(push )
    {
        moteur.avancerMoteur();
        _delay_ms(150);
        // if(partie == "PartieB")
        //     _delay_ms(150);

        if (partie == "PartieB_droite")
             _delay_ms(60);
    }
    
    while (true)
    {
        //_delay_ms(7);
        //moteur.tournerDroite90();
        if(partie == "PartieB" || partie == "PartieA")
        {
            //_delay_ms(8);
            moteur.tournerDroite90();
        }
        else if (partie == "PartieB_droite")
        {
            //moteur.tournerDroite90();
            moteur.tournerDroite(0,102);
        }
        
        masquerEntree();
        if(entree & 0x08){
                break ;
        }     
    }
    // del.rouge(&PORTB);
    // _delay_ms(300);
    // del.eteint(&PORTB);
    moteur.avancerMoteur(115,113);
    // if(push && (partie == "PartieA")){
    //     _delay_ms(240);
    // }
    if (push && (partie == "PartieB_droite"))
    {
        _delay_ms(360);
    }

    else if (push && (partie == "PartieB"))
    {
        _delay_ms(200);
    }
        
}


void DetecteurLigne::detecterGauche90(char* partie,char* direction)
{
    _delay_ms(200);
    masquerEntree();
    milieu = true ;
    
    if ( (entree == 0b00011111) && partie == "PartieA") // point B
    {
        moteur.arreterMoteur();
        point_B_ = true ;
    }

    else if ((entree == 0b00011111) && partie == "PartieB") // Point S
    {
        moteur.avancerMoteur();
        point_S_ = true ;
    }


    else if(direction == "deuxDirection" || direction == "Gauche")
    { 
        // del.rouge(&PORTB);
        // _delay_ms(2000);
        detecterGauche(true,partie) ;
    }
}


void DetecteurLigne::detecterDroite90(char* partie,char* direction)
{
    _delay_ms(230);
    masquerEntree();
    milieu = true ;


    if ( (entree == 0b00011111) && partie == "PartieA") // point B
    {
        moteur.arreterMoteur();
        point_B_ = true ;
    } 

    else if ((entree == 0b00011111) && partie == "PartieB") // Point S
    {
        moteur.avancerMoteur();
        point_S_ = true ;
    }

    else if(direction == "deuxDirection" || direction == "Droite")
    { 
        detecterDroite(true,partie);
    }
}



void DetecteurLigne::detecterZigZag(){

    masquerEntree();
    switch (entree){

    case 0b00000011 :
       moteur.tournerDroite(32,113);
       break;
    case 0b00011000 :
       moteur.tournerGauche(117,32);
       break;

    case 0b00000001:
            moteur.tournerDroite(32,113);
            break;


    case 0b00010000:
      

        moteur.tournerGauche(117,32);

        break;
    
    }
}










void DetecteurLigne::verifierDoubleChemin()
{
    _delay_ms(50);
    masquerEntree();
    if(entree == 0b00001110)
    { 
        doubleChemin = true ;
    }
    else if(entree == 0b00001111 || entree == 0b00000111 ||entree == 0b00011110 || entree == 0b00011100 )
    {
        milieu = true ;
    }
    moteur.avancerMoteur(); 
}

void DetecteurLigne::detecteurDistance()
{
    int moyenne = 0,somme = 0 ;
    uint16_t adresseCompteur = 0x0004 ;
    for(int i =0;i<50;i++)
    {
        distance = (convertisseurAnalogique.lecture(0x06) >>2);
        somme+= distance ;
    }
    moyenne = int(somme/50) ;
    switch (moyenne)
    {
        
        case 27 ... 33: // [43cm - 53cm] loin 
            _delay_ms(45);
            distance = (convertisseurAnalogique.lecture(0x06) >>2);
            if(distance > 33)
            {
                moteur.arreterMoteur();
                del.vert(&PORTB);
                sonnerie.jouerSon(frequence[10]);
                _delay_ms(1100);
                sonnerie.arreterSon();
                moteur.avancerMoteur(130,130);
                _delay_ms(1000);
                uint8_t donnee = 1 ;
                memoire_.ecriture(adresse,donnee);
                tableaux_des_barrieres[compteurBarr_] = 1 ;
                adresse++;
                compteurBarr_++;
                memoire_.ecriture(adresseCompteur,compteurBarr_) ;
            }
            else 
            {
                moteur.arreterMoteur();
                sonnerie.jouerSon(frequence[2]);
                _delay_ms(1000);
                sonnerie.arreterSon();
                moteur.avancerMoteur(130,130);
                _delay_ms(1000);
                del.rouge(&PORTB);
                uint8_t donnee = 2 ;
                memoire_.ecriture(adresse,donnee);
                tableaux_des_barrieres[compteurBarr_] = 2 ;
                compteurBarr_++;
                adresse++;
                memoire_.ecriture(adresseCompteur,compteurBarr_) ;
            }
            
            break;

        case  34 ... 120 : // [11cm - 21cm] proche 
            moteur.arreterMoteur();
            del.vert(&PORTB);

            
            sonnerie.jouerSon(frequence[10]);
            _delay_ms(1000);
            sonnerie.arreterSon();
            moteur.avancerMoteur(130,130);
                _delay_ms(1000);
            uint8_t donnee = 1 ;
            memoire_.ecriture(adresse,donnee);
            tableaux_des_barrieres[compteurBarr_] = 1 ;
            compteurBarr_++;
            adresse++;
            memoire_.ecriture(adresseCompteur,compteurBarr_) ;
            break;

        // default:
        //     sonnerie.arreterSon() ;
        //     moteur.avancerMoteur();

        //     break;


    }
}


void DetecteurLigne::detecterLigne(char* partie, char* direction)

{   
    masquerEntree();
    switch (entree)
        {
            case 0b00000001 :
                detecterGauche(false,"PartieA");
                //moteur.tournerGauche();
                break;

            case 0b00000010 :
                moteur.tournerGauche();
                break ;

            case 0b00000011 :
                //detecterGauche(false,"PartieA");
                milieu = true ;
                moteur.tournerGauche(80,30);
                break;

            case 0b00001000 :
                moteur.tournerDroite();
                break;

            case 0b000010000 :
                detecterDroite(false,"PartieA");
                //moteur.tournerDroite();
                break;

            case 0b00011000 :
                moteur.tournerDroite(30,80);
                milieu = true ;
                //moteur.tournerDroite();
                break;

            case 0b00000100 :
                if(partie == "PartieB_gauche" || partie == "PartieB_droite")
                {
                    moteur.avancerMoteur(92,90);
                }
                else{
                    moteur.avancerMoteur();
                }
                
                break;

            case 0b00001110 :
                  
                verifierDoubleChemin();
                break;

            case 0b00000110 :
                moteur.tournerGauche();
                break;

            case 0b00001100 : 
                moteur.tournerDroite();
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

                detecterGauche90(partie,direction);
                break ;  
                        

            case 0b00001111 : 

                detecterGauche90(partie,direction);   
                break;  

            case 0b00011100 : 

                detecterDroite90(partie,direction);
                break;  

            case 0b00011110 : 

                detecterDroite90(partie,direction);
                break;  
            case 0b00011111 : 
                milieu = true ;
                if (partie == "PartieB")
                    detecterGauche90(partie,direction);   
            
            default:
                moteur.arreterMoteur();
                break;
        }
}

