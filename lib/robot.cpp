#include "robot.h"


Robot::Robot()

{}


Robot::~Robot()

{}


void Robot::pariteA()
{
    while (!(detecteurLigne_.getPoint_B()))
    {
        detecteurDistance_.detecterBar();
        detecteurLigne_.dectcterLigne();

    }
}

void Robot::partieB()
{
    int* tab_barrieres = detecteurDistance_.getTabBarrieres(); // recuperer les donnees des barrieres pour continuer sur la partie B 
    while(!(detecteurLigne_.getPoint_S()))
    {
        detecteurLigne_.dectcterLigne();

    }
}


void Robot::partieC()
{
    // à Farid et Sid pour completer 
}