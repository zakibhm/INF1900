#include "robot.h"

uint8_t gMinuterieExpiree = 0 ;
const uint8_t modeEntree = 0x00 ;
const uint8_t modeSortiee = 0xff ;


Robot::Robot()

{}


Robot::~Robot()

{}



void Robot::partirMinuterie () {
    
    TCNT0 = 0 ;

    OCR0A = duree;
    TCCR0A |= (1<<WGM12)|(1<<WGM12);
    

    TCCR0B |= (1<<CS12)|(1<<CS10);

    TIMSK0 |=(1<<OCIE1A);
}


void Robot::initialisation ( void ) {
    cli ();//disabling all external interruptions 
    EIMSK |= (1 << INT0); //Dit au microcontroleur quil px se faire interrompre
    EICRA |= (1 << ISC00)|(1<<ISC01); //Dit au microcontroleur quil px se faire interrompre que par des fronts montants/descendants
    sei ();
}


ISR ( TIMER0_COMPA_vect ) {
    gMinuterieExpiree = 1;

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
        detecteurDistance_.detecterBar();
        detecteurLigne_.detecterLigne("PartieA");

    }
    ecrireTabMem(retournerTab()) ;
}

void Robot::partieB()
{
    
    initialisation();

    uint8_t tableau[3]= {1,2,1} ;
    //uint8_t* tableauBarriere = lectureTabMem();
    enum class Partie{barriere_1,barriere_2,barriere_3,fin} ;
    Partie partieCourante = Partie::barriere_1 ;
    Del del ;
    Son son ;
    while(!(detecteurLigne_.getPoint_S()))
    {
        
        switch (partieCourante)
        {
        case Partie::barriere_1 :
            
            detecteurLigne_.detecterLigne("PartieB");
            if (detecteurLigne_.getDoublechemin() )
            {
                del.rouge(&PORTB);
                partirMinuterie();
                if(tableau[2] == 1) 
                {
                    son.jouerSon(110) ;
                    moteur_.tournerDroite90();
                    _delay_ms(300) ;
                }
                else
                {
                    moteur_.tournerGauche90();
                    _delay_ms(300) ;
                }
            }
            partieCourante = Partie::barriere_2 ;
            break;
        
        case Partie::barriere_2 :
            detecteurLigne_.detecterLigne("PartieB");
            if(gMinuterieExpiree)
            {
                if(tableau[1] == 1)
                {
                    moteur_.tournerGauche90();
                    _delay_ms(300);
                    moteur_.arreterMoteur();
                    _delay_ms(1000) ;
                }

                else if (tableau[1] == 2)
                {
                    moteur_.tournerDroite90();
                    _delay_ms(300);
                    moteur_.arreterMoteur();
                    _delay_ms(1000) ;
                }
                else
                {
                    moteur_.reculerMoteur();
                    _delay_ms(1000);
                    moteur_.arreterMoteur();
                    _delay_ms(1000) ;
                }
                partieCourante = Partie::barriere_3 ;
            }
            break;


        case Partie::barriere_3 :
            detecteurLigne_.detecterLigne("PartieB");
            if (detecteurLigne_.getDoublechemin() )
            {
                if(tableau[0] == 1) 
                {
                    del.vert(&PORTB);
                    son.jouerSon(110) ;
                    moteur_.tournerDroite90();
                    _delay_ms(300) ;
                }
                else 
                {
                    moteur_.tournerGauche90();
                    _delay_ms(300) ;
                }
            }

            partieCourante = Partie::fin ;
            break;

        case Partie::fin :
            detecteurLigne_.detecterLigne("PartieB");
            break;


        default:
            break;
        }
        del.eteint(&PORTB);
    }

}



void Robot::partieC()
{
    // à Farid et Sid pour completer 
}