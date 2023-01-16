#include "robot.h"

uint8_t gMinuterieExpiree ;
uint8_t gappellé1 = 0 ;
const uint8_t modeEntree = 0x00 ;
const uint8_t modeSortiee = 0xff ;


Robot::Robot()

{}


Robot::~Robot()

{}



void Robot::partirMinuterie () {
    sei ();

    gMinuterieExpiree = 0;

    TCNT1 = 0 ;

    OCR1A = duree;
    TCCR1A |= (1<<WGM12)|(1<<WGM12);
    

    TCCR1B |= (1<<CS12)|(1<<CS10);

    TIMSK1 |=(1<<OCIE1A);
}


ISR ( TIMER1_COMPA_vect ) {
    TCNT1 = 0 ;
    gMinuterieExpiree += 1;
    if(gMinuterieExpiree > 20)
     {
        gappellé1 = 1 ;
        }
        

}

void Robot::ecrireTabMem(uint8_t* tableau)  
{   
    uint16_t adresse =0x0000 ;
    const uint8_t tailleTab = 3 ;
    memoire.ecriture(adresse,tableau[0]);
    adresse+=1 ;
    memoire.ecriture(adresse,tableau[1]);
    adresse+=1 ;
    memoire.ecriture(adresse,tableau[2]);

}


void Robot::partieA()
{
    moteur_.avancerMoteur(122,118);
    _delay_ms(1000);
    while (!(detecteurLigne_.getPoint_B()))
    {
        detecteurLigne_.detecteurDistance();
        detecteurLigne_.detecterLigne("PartieA","deuxDirection");

    }
}

void Robot::partieB()
{
    uint8_t entree ;
    uint8_t tableau[3] ;
    bool gauche = false,droite = false ;

    //                                                 lecture de la memoire

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    uint16_t adresse =0x0000 ;
    uint16_t adresseCompteur =0x0004 ;
    uint8_t barr1;
    uint8_t barr2;
    uint8_t barr3;
    uint8_t compteurBarr ;  
    memoire.lecture(adresseCompteur,&compteurBarr);
    if(compteurBarr == 3)

    {    
        memoire.lecture(adresse,&barr1);
        adresse+=1;
        memoire.lecture(adresse,&barr2);
        adresse+=1;
        memoire.lecture(adresse,&barr3);
        tableau[0] = barr3;
        tableau[1] = barr2;
        tableau[2] = barr1;

    }

    else if (compteurBarr == 2)
    {
        memoire.lecture(adresse,&barr1);
        adresse+=1;
        memoire.lecture(adresse,&barr2);
        tableau[0] = barr2 ;
        tableau[1] = 0 ;
        tableau[2] = barr1 ;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    enum class Partie {debut,point_E,point__J,point_M,point_P,fin};
    Partie partieCourante = Partie::debut ;
    moteur_.avancerMoteur(125,120);
    _delay_ms(1000);
    while(!(detecteurLigne_.getPoint_S()))
    {
        
        switch (partieCourante)
        {
        case Partie::debut :
            detecteurLigne_.detecterLigne("PartieB","deuxDirection");
            if (detecteurLigne_.getDoublechemin() )
            {
                partieCourante = Partie::point_E ;
            }
            
            break;

        case Partie::point_E :
            
            moteur_.avancerMoteur();
            
            if(tableau[0] == 1) 
            {
                detecteurLigne_.detecterDroite(true,"PartieB_droite");
                droite = true;

            }
            else if(tableau[0] == 2) 
            {
                detecteurLigne_.detecterGauche(true,"PartieB_gauche");
                gauche = true ;
            }
            partirMinuterie();
            detecteurLigne_.setMilieu(false) ;
            partieCourante = Partie::point__J ;

            break;
        
        case Partie::point__J :

            

            if (droite)
            {
                detecteurLigne_.detecterLigne("PartieB","Droite");
            }
            else if (gauche)
            {
                detecteurLigne_.detecterLigne("PartieB","Gauche");
            }
            if(detecteurLigne_.getMilieu() && gMinuterieExpiree > 20)
            {
                
                moteur_.avancerMoteur(123,122);
                _delay_ms(1000);
                moteur_.arreterMoteur();
                _delay_ms(300);
                detecteurLigne_.setMilieu(false) ;
                if(droite)
                {
                    detecteurLigne_.detecterDroite(true,"PartieB_droite");
                }
                else if(gauche)
                {
                    detecteurLigne_.detecterGauche(true,"PartieB_gauche");
                }
                partirMinuterie();
                moteur_.avancerMoteur(120,126);
                _delay_ms(200);

                
            }

            else if(gMinuterieExpiree == 2 && gappellé1)
                {
                    cli();
                    moteur_.arreterMoteur();
                    _delay_ms(250);
                    _delay_ms(1000);
                    if(tableau[1] == 1)
                    {
                        moteur_.tournerGauche(125,0);
                        _delay_ms(560);
                        moteur_.arreterMoteur();
                        _delay_ms(1000) ;

                        moteur_.tournerDroite(0,125);
                        _delay_ms(440);
                    }

                    else if (tableau[1] == 2)
                    {
                        moteur_.tournerDroite(0,125);
                        _delay_ms(490);
                        moteur_.arreterMoteur();
                        _delay_ms(1000) ;

                        moteur_.tournerGauche(125,0);
                        _delay_ms(560);
                    }
                    else if (tableau[1] == 0)
                    {
                        moteur_.reculerMoteur(125,120);
                        _delay_ms(1000);
                        moteur_.arreterMoteur();
                        _delay_ms(1000) ;
                        moteur_.avancerMoteur(125,120);
                        _delay_ms(600) ;
                    }
                    
                    detecteurLigne_.setDoublechemin(false) ;
                    gauche = false ;
                    droite = false ;
                    moteur_.avancerMoteur(125,120);
                    _delay_ms(400);
                    partieCourante = Partie::point_M ;
                }
            

            break;

            


        case Partie::point_M :

            detecteurLigne_.detecterLigne("PartieB","deuxDirection");
            if (detecteurLigne_.getDoublechemin()  )
            {
                moteur_.avancerMoteur();
                _delay_ms(250);
                if(tableau[2] == 1) 
                {
                    detecteurLigne_.detecterDroite(true,"PartieB_droite");
                    droite = true;

                }
                else if (tableau[2] == 2)
                {
                    detecteurLigne_.detecterGauche(true,"PartieB_gauche");
                    gauche = true ;
                }
                partirMinuterie();
                detecteurLigne_.setPoint_S(false);
                partieCourante = Partie::point_P ;
            }

            
            break;

        case Partie::point_P :

            if (droite)
            {
                detecteurLigne_.detecterLigne("PartieB_droite","Droite");
            }
            else if (gauche)
            {
                detecteurLigne_.detecterLigne("PartieB_gauche","Gauche");
            }
            detecteurLigne_.setPoint_S(false);
            if(detecteurLigne_.getMilieu() && gMinuterieExpiree > 20)
            {
                moteur_.avancerMoteur(123,122);
                _delay_ms(1200);
                moteur_.arreterMoteur();
                _delay_ms(300);
                detecteurLigne_.setMilieu(false) ;
                if(droite)
                {
                    moteur_.tournerDroite(0,105);
                    _delay_ms(305);
                }
                else if(gauche)
                {
                    moteur_.tournerGauche(114,0);
                    _delay_ms(300);
                }
                
                cli();
                partieCourante = Partie::fin ;  
                
            }
            break;

        case Partie::fin :
            detecteurLigne_.detecterLigne("PartieB","deuxDirection");
            break ;

        default:
            break;
        }
    }

}



void Robot::partieC()
{
    
    uint8_t entree ;
    moteur_.avancerMoteur(126,120);
    _delay_ms(1000);
    partirMinuterie();
    while(gMinuterieExpiree < 12)
    {  
        detecteurLigne_.detecterLigne("PartieA","deuxDirection");
    }

    while(true)
    {
        entree = PINA ;
        entree &= 0x1f & entree ;
        moteur_.tournerDroite(0,91);
        if(entree & 0x10){
                moteur_.arreterMoteur();
                _delay_ms(1000);
                break ;
        }  
    }
    partirMinuterie();

    while(gMinuterieExpiree < 30)
    {   
        detecteurLigne_.detecterZigZag();

    }
    cli();
    entree = PINA ;
    entree &= 0x1f & entree ;
    if (entree == 0b00000000)
    {
        while(true)
    {
        entree = PINA ;
        entree &= 0x1f & entree ;
        moteur_.avancerMoteur(102,98);
        if(entree == 0b00010000)
        {
            break ;
        }
    }
    }
    while(entree != 0b00000000)
    {
       entree = PINA ;
       entree &= 0x1f & entree ;
       detecteurLigne_.detecterLigne("PartieA","deuxDirection");
    }
    
    _delay_ms(1000);
    stationnement();
        
}


void Robot::stationnement()
{
    Son son ;
    moteur_.reculerMoteur(150,150);
    _delay_ms(1600); 

    moteur_.arreterMoteur();
    _delay_ms(2000);

    moteur_.tournerDroite(0, 150);
    _delay_ms(1600);

    moteur_.arreterMoteur();
    _delay_ms(2000);

    moteur_.avancerMoteur(150,150);
    _delay_ms(600);
    moteur_.arreterMoteur();
    son.jouerSon(110);
    _delay_ms(1000);
    son.arreterSon();
}