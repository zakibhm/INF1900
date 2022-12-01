#include "robot.h"

uint8_t gMinuterieExpiree ;
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


// void Robot::initialisation ( void ) {
//     cli ();//disabling all external interruptions 
//     EIMSK |= (1 << INT0); //Dit au microcontroleur quil px se faire interrompre
//     EICRA |= (1 << ISC00)|(1<<ISC01); //Dit au microcontroleur quil px se faire interrompre que par des fronts montants/descendants
//     sei ();
// }


ISR ( TIMER1_COMPA_vect ) {
    TCNT1 = 0 ;
    gMinuterieExpiree += 1;

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
    uint8_t compteur = 0 ;
    uint8_t tableau[3]= {1,2,1} ;
    bool gauche = false,droite = false ;
    //uint8_t* tableauBarriere = lectureTabMem();
    enum class Partie {barriere_1,barriere_2,barriere_3,fin};
    Partie partieCourante = Partie::barriere_1 ;
    Del del ;
    Son son ;
    Moteur moteur ;
    //del.vert(&PORTB);
    // if(!(detecteurLigne_.getPoint_S()))
    //     del.rouge(&PORTB);
    //      _delay_ms(3000) ;
    
    //detecteurLigne_.setPoint_S(flase)
    while(!(detecteurLigne_.getPoint_S()))
    {
        
        switch (partieCourante)
        {
        case Partie::barriere_1 :
            //del.vert(&PORTB);
            detecteurLigne_.detecterLigne("PartieB","deuxDirection");
            if (detecteurLigne_.getDoublechemin() )
            {
                del.rouge(&PORTB);
                moteur.arreterMoteur();
                _delay_ms(500);
                del.eteint(&PORTB) ;
                //partirMinuterie();
                if(tableau[2] == 1) 
                {
                    //son.jouerSon(110) ;
                    moteur_.tournerGauche(160,0);
                    _delay_ms(1500);
                    droite =  true ;
                }
                else
                {
                    moteur_.tournerGauche(160,0);
                    _delay_ms(1500);
                    gauche = true ;
                }
                partieCourante = Partie::barriere_2 ;
            }
            
            break;
        
        case Partie::barriere_2 :
            //del.rouge(&PORTB);
            if (droite)
            {
                detecteurLigne_.detecterLigne("PartieB","Droite");
            }
            else if (gauche)
            {
                detecteurLigne_.detecterLigne("PartieB","Gauche");
            }
            if(detecteurLigne_.getMilieu())
            {
                compteur++ ;
                if(compteur == 3)
                {
                    del.vert(&PORTB);
                    moteur.arreterMoteur();
                    _delay_ms(500);
                    partirMinuterie();
                    del.eteint(&PORTB);
                    }
            }
            if(gMinuterieExpiree == 4)
            {
                cli ();
                moteur.arreterMoteur();
                _delay_ms(1200);
                if(tableau[1] == 1)
                {
                    moteur_.tournerGauche(160,0);
                    _delay_ms(1200);
                    moteur_.arreterMoteur();
                    _delay_ms(1000) ;

                    moteur_.tournerDroite(0,160);
                    _delay_ms(1200);
                }

                else if (tableau[1] == 2)
                {
                    moteur_.tournerDroite(0,160);
                    _delay_ms(1200);
                    moteur_.arreterMoteur();
                    _delay_ms(1000) ;

                    moteur_.tournerGauche(160,0);
                    _delay_ms(1200);
                }
                else
                {
                    moteur_.reculerMoteur();
                    _delay_ms(1000);
                    moteur_.arreterMoteur();
                    _delay_ms(1000) ;
                }
                partieCourante = Partie::barriere_3 ;
                detecteurLigne_.setDoublechemin(false) ;
                droite = false ;
                gauche = false ;
            }

            break;

            


        case Partie::barriere_3 :
            del.rouge(&PORTB);
            detecteurLigne_.detecterLigne("PartieB","deuxDirection");
            if (detecteurLigne_.getDoublechemin() )
            {
                moteur.arreterMoteur();
                _delay_ms(500);
                if(tableau[0] == 1) 
                {
                    //del.vert(&PORTB);
                    //son.jouerSon(110) ;
                    moteur_.tournerDroite(0,160);
                    _delay_ms(1500);

                }
                else 
                {
                    moteur_.tournerGauche(160,0);
                    _delay_ms(1500);
                }
                partieCourante = Partie::fin ;
            }

            
            break;

        case Partie::fin :
            detecteurLigne_.detecterLigne("PartieB","Droite");
            break;


        default:
            break;
        }
    }

}



void Robot::partieC()
{
    // à Farid et Sid pour completer 
}