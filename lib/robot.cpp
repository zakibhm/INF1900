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

// void clignote()
// {
//     Del del ;
//     for(int i = 0; i < 4 ; i++)
//             {del.rouge(&PORTB);
//             _delay_ms(250);
//             del.vert(&PORTB);
//             _delay_ms(250);
// }
// void Robot::initialisation ( void ) {
//     cli ();//disabling all external interruptions 
//     EIMSK |= (1 << INT0); //Dit au microcontroleur quil px se faire interrompre
//     EICRA |= (1 << ISC00)|(1<<ISC01); //Dit au microcontroleur quil px se faire interrompre que par des fronts montants/descendants
//     sei ();
// }


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
    const uint16_t adresse =0x0000 ;
    const uint8_t tailleTab = 3 ;
    Memoire24CXXX memoire ;
    memoire.ecriture(adresse,tableau, tailleTab);

}

uint8_t* Robot::retournerTab()
{
    uint8_t* tab_barrieres = detecteurLigne_.getTabBarrieres() ; // recuperer les donnees des barrieres pour continuer sur la partie B 
    if(tab_barrieres[2] == 0) // si le robot n'a detecté que deux barrieres (pas barriers au milieu)
    {
        tab_barrieres[2] = tab_barrieres[1] ;
        tab_barrieres[1] = 0 ;

    }
    return tab_barrieres ;
}


uint8_t* Robot::lectureTabMem()
{
    const uint16_t adresse =0x0000 ;
    const uint8_t tailleTab = 3 ;
    Memoire24CXXX memoire ;
    uint8_t tableauMem[3] ;
    memoire.lecture(adresse,tableauMem, tailleTab);
    return tableauMem ;
}


void Robot::pariteA()
{
    while (!(detecteurLigne_.getPoint_B()))
    {
        detecteurLigne_.detecteurDistance();
        detecteurLigne_.detecterLigne("PartieA","deuxDirection");

    }
    ecrireTabMem(retournerTab()) ;
}

void Robot::partieB()
{
    uint8_t entree ;
    bool reculer = false ;
    uint8_t compteur = 0 ;
    uint8_t tableau[3]= {1,2,1} ;
    bool gauche = false,droite = false ;
    //uint8_t* tableauBarriere = lectureTabMem();
    enum class Partie {debut,point_E,point__J,point_M,point_P,fin};
    Partie partieCourante = Partie::debut ;
    Del del ;
    Son son ;
    Moteur moteur ;
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
            else 
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
            if(detecteurLigne_.getMilieu() && gMinuterieExpiree > 19)
            {
                cli() ;
                del.vert(&PORTB);
                
                moteur.avancerMoteur(123,122);
                _delay_ms(1200);
                del.eteint(&PORTB);
                moteur.arreterMoteur();
                _delay_ms(300);
                detecteurLigne_.setMilieu(false) ;
                if(droite)
                {
                    detecteurLigne_.detecterDroite(true,"PartieB_droite");
                    // moteur_.tournerDroite(0,116);
                    // _delay_ms(500);
                }
                else if(gauche)
                {
                    detecteurLigne_.detecterGauche(true,"PartieB_gauche");
                    // moteur_.tournerGauche(116,0);
                    // _delay_ms(500);
                }
                partirMinuterie();
                
            }

            else if(gMinuterieExpiree == 3 && gappellé1)
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
                        _delay_ms(650);
                        moteur_.arreterMoteur();
                        _delay_ms(1000) ;

                        moteur_.tournerDroite(0,125);
                        _delay_ms(680);
                    }

                    else if (tableau[1] == 2)
                    {
                        moteur_.tournerDroite(0,125);
                        _delay_ms(680);
                        moteur_.arreterMoteur();
                        _delay_ms(1000) ;

                        moteur_.tournerGauche(125,0);
                        _delay_ms(650);
                    }
                    else
                    {
                        moteur_.reculerMoteur();
                        _delay_ms(1000);
                        moteur_.arreterMoteur();
                        _delay_ms(1000) ;
                        moteur.avancerMoteur(125,132);
                        _delay_ms(500) ;
                        //reculer = true ;
                    }
                    partieCourante = Partie::point_M ;
                    detecteurLigne_.setDoublechemin(false) ;
                    gauche = false ;
                    droite = false ;
                    moteur.arreterMoteur();
                    _delay_ms(250);
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
                else
                {
                    detecteurLigne_.detecterGauche(true,"PartieB_gauche");
                    gauche = true ;
                }
                partirMinuterie();
                partieCourante = Partie::point_P ;
            }

            
            break;

        case Partie::point_P :

            del.vert(&PORTB);
            _delay_ms(1000);
            del.eteint(&PORTB);


            if (droite)
            {
                detecteurLigne_.detecterLigne("PartieB","Droite");
            }
            else if (gauche)
            {
                detecteurLigne_.detecterLigne("PartieB","Gauche");
            }
            if(detecteurLigne_.getMilieu() && gMinuterieExpiree > 14)
            {
                cli() ;
                del.vert(&PORTB);
                moteur.avancerMoteur();
                _delay_ms(250);
                del.eteint(&PORTB);
                detecteurLigne_.setMilieu(false) ;
                if(droite)
                {
                    detecteurLigne_.detecterDroite(true,"PartieB_droite");
                }
                else if(gauche)
                {
                    detecteurLigne_.detecterGauche(true,"PartieB_gauche");
                }
                partieCourante = Partie::fin ;  
                
            }
            break;

        case Partie::fin :
            detecteurLigne_.detecterLigne("PartieA","deuxDirection");
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
    partirMinuterie();
    while(gMinuterieExpiree < 8)
    {  
        detecteurLigne_.detecterLigne("PartieA","deuxDirection");
    }

    while(true)
    {
        entree = PINC ;
        entree &= 0x1f & entree ;
        moteur.tournerDroite(0,95);
        if(entree & 0x10){
                moteur.arreterMoteur();
                _delay_ms(1000);
                break ;
        }  
    }
    partirMinuterie();

    while(gMinuterieExpiree < 31)
    {   
        detecteurLigne_.detecterZigZag();

    }
    del.rouge(&PORTB);
    cli();
    entree = PINC ;
    entree &= 0x1f & entree ;
    if (entree == 0b00000000)
    {
        while(true)
    {
        entree = PINC ;
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
       entree = PINC ;
       entree &= 0x1f & entree ;
       detecteurLigne_.detecterLigne("PartieA","deuxDirection");
    }
    
    _delay_ms(1000);
    del.eteint(&PORTB);
        
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