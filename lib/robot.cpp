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
    if(gMinuterieExpiree > 19)
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

uint8_t* Robot::retournerTab()
{
    // uint8_t* tab_barrieres = detecteurLigne_.getTabBarrieres() ; // recuperer les donnees des barrieres pour continuer sur la partie B 
    // if(getComp) // si le robot n'a detecté que deux barrieres (pas barriers au milieu)
    // {
    //     tab_barrieres[2] = tab_barrieres[1] ;
    //     tab_barrieres[1] = 0 ;

    // }
    // return tab_barrieres ;
}


uint8_t* Robot::lectureTabMem()
{
    uint16_t adresse =0x0000 ;
    uint16_t adresseCompteur =0x0004 ;
    uint8_t tableauMem[3] ;
    uint8_t barr1;
    uint8_t barr2;
    uint8_t barr3;
    uint8_t compteurBarr ;
    memoire.lecture(adresseCompteur,&compteurBarr);
    Del del ;
    if(compteurBarr == 3)

    {    
        del.rouge(&PORTB);
        _delay_ms(1000);
        del.eteint(&PORTB);
        _delay_ms(1000);
        memoire.lecture(adresse,&barr1);
        adresse+=1;
        memoire.lecture(adresse,&barr2);
        adresse+=1;
        memoire.lecture(adresse,&barr3);
        tableauMem[0] = barr3;
        tableauMem[1] = barr2;
        tableauMem[2] = barr1;
        // if(barr3 == 2)
        // {
        //     del.rouge(&PORTB);
        //     _delay_ms(500);
        //     del.eteint(&PORTB);
        //     _delay_ms(500);
        // }
        // else if (barr3 == 1)
        // {
        //     del.vert(&PORTB);
        //     _delay_ms(500);
        //     del.eteint(&PORTB);
        //     _delay_ms(500);
        // }

        // del.clignote(&PORTB,2000);

        // if(barr2 == 2)
        // {
        //     del.rouge(&PORTB);
        //     _delay_ms(500);
        //     del.eteint(&PORTB);
        //     _delay_ms(500);
        // }
        // else if (barr2 == 1)
        // {
        //     del.vert(&PORTB);
        //     _delay_ms(500);
        //     del.eteint(&PORTB);
        //     _delay_ms(500);
        // }

        // del.clignote(&PORTB,2000);

        // if(barr1 == 2)
        // {
        //     del.rouge(&PORTB);
        //     _delay_ms(500);
        //     del.eteint(&PORTB);
        //     _delay_ms(500);
        // }
        // else if (barr1 == 1)
        // {
        //     del.vert(&PORTB);
        //     _delay_ms(500);
        //     del.eteint(&PORTB);
        //     _delay_ms(500);
        // }

        // del.clignote(&PORTB,2000);


        }
    else if (compteurBarr == 2)
    {
        del.vert(&PORTB);
        _delay_ms(1000);
        del.eteint(&PORTB);
        
        memoire.lecture(adresse,&barr1);
        adresse+=1;
        memoire.lecture(adresse,&barr2);
        tableauMem[0] = barr2 ;
        tableauMem[1] = 0 ;
        tableauMem[2] = barr1 ;
    }
    else if (compteurBarr == 0)
        {
            del.clignote(&PORTB,2000);
        }
    return tableauMem ;
}


void Robot::partieA()
{
    moteur_.avancerMoteur(120,118);
    _delay_ms(1000);
    while (!(detecteurLigne_.getPoint_B()))
    {
        detecteurLigne_.detecteurDistance();
        detecteurLigne_.detecterLigne("PartieA","deuxDirection");

    }
    //ecrireTabMem(retournerTab()) ;
}

void Robot::partieB()
{
    Del del ;
    uint8_t entree ;
    bool reculer = false ;
    uint8_t compteur = 0 ;
    uint8_t tableau[3]= {2,0,2} ;
    bool gauche = false,droite = false ;
    //uint8_t* tableau = lectureTabMem();
    del.eteint(&PORTB);
    _delay_ms(2000);
    uint16_t adresse =0x0000 ;
    uint16_t adresseCompteur =0x0004 ;
    //uint8_t tableau[3] ;
    uint8_t barr1;
    uint8_t barr2;
    uint8_t barr3;
    uint8_t compteurBarr ;  
    memoire.lecture(adresseCompteur,&compteurBarr);
    if(compteurBarr == 3)

    {    
        del.rouge(&PORTB);
        _delay_ms(250);
        del.eteint(&PORTB);
        memoire.lecture(adresse,&barr1);
        adresse+=1;
        memoire.lecture(adresse,&barr2);
        adresse+=1;
        memoire.lecture(adresse,&barr3);
        tableau[0] = barr3;
        tableau[1] = barr2;
        tableau[2] = barr1;
        //const uint8_t tableau[3] = {barr3,barr2,barr1};

    }

    else if (compteurBarr == 2)
    {
        del.vert(&PORTB);
        _delay_ms(250);
        del.eteint(&PORTB);
        
        memoire.lecture(adresse,&barr1);
        adresse+=1;
        memoire.lecture(adresse,&barr2);
        tableau[0] = barr2 ;
        tableau[1] = 0 ;
        tableau[2] = barr1 ;
        //const uint8_t tableau[3] = {barr2,0,barr1};
    }
    else
    {
        const uint8_t tableau[3] = {0,0,0};
    }
    
    enum class Partie {debut,point_E,point__J,point_M,point_P,fin};
    Partie partieCourante = Partie::debut ;
    //Del del ;
    Son son ;
    Moteur moteur ;
    // moteur_.avancerMoteur(120,118);
    // _delay_ms(1000);
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
            
            del.rouge(&PORTB);
            moteur.avancerMoteur();
            _delay_ms(250);
            del.eteint(&PORTB) ;
            
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
            if(detecteurLigne_.getMilieu() && gMinuterieExpiree > 18)
            {
                //cli() ;
                del.vert(&PORTB);
                
                moteur.avancerMoteur(123,122);
                _delay_ms(1000);
                del.eteint(&PORTB);
                moteur.arreterMoteur();
                _delay_ms(300);
                detecteurLigne_.setMilieu(false) ;
                if(droite)
                {
                    moteur_.tournerDroite(0,116);
                    _delay_ms(500);
                }
                else if(gauche)
                {
                    moteur_.tournerGauche(120,0);
                    _delay_ms(600);
                }
                partirMinuterie();
                moteur_.avancerMoteur(120,126);
                _delay_ms(200);

                
            }

            else if(gMinuterieExpiree == 4 && gappellé1)
                {
                    cli();
                    moteur.arreterMoteur();
                    del.vert(&PORTB);
                    //moteur.avancerMoteur();
                    _delay_ms(250);
                    del.eteint(&PORTB) ;
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
                        moteur_.reculerMoteur();
                        _delay_ms(1000);
                        moteur_.arreterMoteur();
                        _delay_ms(1000) ;
                        moteur.avancerMoteur(120,118);
                        _delay_ms(500) ;
                        //reculer = true ;
                    }
                    
                    detecteurLigne_.setDoublechemin(false) ;
                    gauche = false ;
                    droite = false ;
                    moteur.arreterMoteur();
                    _delay_ms(250);
                    partieCourante = Partie::point_M ;
                    //partirMinuterie();
                }
            

            break;

            


        case Partie::point_M :

            detecteurLigne_.detecterLigne("PartieB","deuxDirection");
            if (detecteurLigne_.getDoublechemin()  )
            {
                //cli();
                del.rouge(&PORTB);
                moteur.avancerMoteur();
                _delay_ms(250);
                del.eteint(&PORTB) ;
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

            // del.vert(&PORTB);
            // _delay_ms(250);
            // del.eteint(&PORTB);
            if (droite)
            {
                detecteurLigne_.detecterLigne("PartieB_droite","Droite");
            }
            else if (gauche)
            {
                detecteurLigne_.detecterLigne("PartieB_gauche","Gauche");
            }
            detecteurLigne_.setPoint_S(false);
            if(detecteurLigne_.getMilieu() && gMinuterieExpiree > 18)
            {
                //cli() ;
                del.vert(&PORTB);
                moteur.avancerMoteur(123,122);
                _delay_ms(1000);
                del.eteint(&PORTB);
                moteur.arreterMoteur();
                _delay_ms(300);
                detecteurLigne_.setMilieu(false) ;
                if(droite)
                {
                    moteur_.tournerDroite(0,112);
                    _delay_ms(350);
                }
                else if(gauche)
                {
                    //detecteurLigne_.detecterGauche(true,"PartieB_gauche");
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
            del.eteint(&PORTB);
            break;
        }
    }
    del.vert(&PORTB);

}



void Robot::partieC()
{
    uint8_t compteur =  0;
    uint8_t entree ;
    Del del ;
    Moteur moteur ;
    moteur.avancerMoteur(110,110);
    _delay_ms(1000);
    partirMinuterie();
    while(gMinuterieExpiree < 8)
    {  
        detecteurLigne_.detecterLigne("PartieA","deuxDirection");
    }

    while(true)
    {
        entree = PINA ;
        entree &= 0x1f & entree ;
        moteur.tournerDroite(0,95);
        if(entree & 0x10){
                moteur.arreterMoteur();
                _delay_ms(1000);
                break ;
        }  
    }
    partirMinuterie();

    while(gMinuterieExpiree < 28)
    {   
        detecteurLigne_.detecterZigZag();

    }
    del.rouge(&PORTB);
    cli();
    entree = PINA ;
    entree &= 0x1f & entree ;
    if (entree == 0b00000000)
    {
        while(true)
    {
        entree = PINA ;
        entree &= 0x1f & entree ;
        moteur.avancerMoteur();
        if(entree == 0b00010000)
        {
            break ;
        }
    }
    }
    del.vert(&PORTB);
    while(entree != 0b00000000)
    {
       entree = PINA ;
       entree &= 0x1f & entree ;
       detecteurLigne_.detecterLigne("PartieA","deuxDirection");
    }
    
    _delay_ms(1000);
    del.eteint(&PORTB);
    stationnement();
        
}


void Robot::stationnement()
{
    moteur_.reculerMoteur(150,150);
    _delay_ms(1350); 

    moteur_.arreterMoteur();
    _delay_ms(2000);

    moteur_.tournerDroite(0, 150);
    _delay_ms(1300);

    moteur_.arreterMoteur();
    _delay_ms(2000);

    moteur_.avancerMoteur(150,150);
    _delay_ms(600);
    moteur_.arreterMoteur();
}