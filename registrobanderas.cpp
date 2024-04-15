#include "registrobanderas.h"

RegistroBanderas::RegistroBanderas()
{
    oneClickArrow = false;
    twoClickArrow = false;
    changesOnVertices = false;
}

void RegistroBanderas::setOneClickArrow(bool oneClickArrow){
    this->oneClickArrow = oneClickArrow;
}

void RegistroBanderas::setTwoClickArrow(bool twoClickArrow){
    this->twoClickArrow = twoClickArrow;
}

void RegistroBanderas::setChangesOnVertices(bool changesOnVertices){
    this->changesOnVertices = changesOnVertices;
}

bool RegistroBanderas::getOneClickArrow(){
    return oneClickArrow;
}

bool RegistroBanderas::getTwoClickArrow(){
    return twoClickArrow;
}

bool RegistroBanderas::getChangesOnVertices(){
    return changesOnVertices;
}



