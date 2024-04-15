#include "conjunto.h"
#include <iostream>

//Constructor default
Conjunto::Conjunto() {
    elementosValidos = 0;
    for (int i = 0; i < 100; i++) elemento[i] = " ";
}

//Union Conjuntos
Conjunto Conjunto::unionC(Conjunto conjuntoB) {
    Conjunto conjuntoC;
    for(int i=0;i<elementosValidos+conjuntoB.getElementosValidos();i++){
        i<elementosValidos ? conjuntoC.setElementos(i,elemento[i]) : conjuntoC.setElementos(i,conjuntoB.getElemento(i-elementosValidos));
    }
    conjuntoC.setElementosValidos(elementosValidos+conjuntoB.getElementosValidos());
    conjuntoC.validarConjunto();
    return conjuntoC;
}

//Interseccion Conjuntos
Conjunto Conjunto::interseccion(Conjunto conjuntoB) {
    Conjunto conjuntoC;
    //Nos aseguramos de tener un conjunto sin repetidos
    validarConjunto();
    conjuntoB.validarConjunto();
    int posNewArray=0;
    for(int i=0; i<elementosValidos; i++){
        for(int j=0; j<conjuntoB.getElementosValidos(); j++){
            if(elemento[i]==conjuntoB.getElemento(j)){
                conjuntoC.setElementos(posNewArray,elemento[i]);
                posNewArray++;
                break;
            }
        }
    }
    //	conjuntoC.validarConjunto();
    return conjuntoC;
}

//Producto Cruz
Conjunto Conjunto::productoCruz(Conjunto conjuntoB) {
    Conjunto conjuntoC;
    //Asegurarse que no hay elementos repetidos
    validarConjunto(); conjuntoB.validarConjunto();
    int newPosArray=0;
    for(int i=0;i<elementosValidos;i++){
        for(int j=0;j<conjuntoB.getElementosValidos();j++){
            conjuntoC.setElementos(newPosArray,("("+elemento[i]+","+conjuntoB.getElemento(j)+")"));
            newPosArray++;
        }
    }
    return conjuntoC;
}

//Diferencia Conjuntos
Conjunto Conjunto::diferencia(Conjunto conjuntoB) {
    Conjunto conjuntoC;
    int band=0, posNewArray=0;
    validarConjunto();
    conjuntoB.validarConjunto();
    for(int i=0;i<elementosValidos;i++){
        band=0;
        for(int j=0;j<conjuntoB.getElementosValidos();j++){
            if(elemento[i]==conjuntoB.getElemento(j)){
                band=1;

            }
        }
        if(band==0){
            conjuntoC.setElementos(posNewArray,elemento[i]);
            posNewArray++;
        }
    }


    return conjuntoC;
}

//Armar Relaciones
void Conjunto::relaciones(Conjunto conjuntoB) {

}

//Armar Subconjuntos
void Conjunto::subconjuntos(Conjunto conjuntoB, int nSubConjunotos) {

}

//Validar Conjuntos (Eliminar repetidos)
void Conjunto::validarConjunto(){
    std::string newArray[100];
    newArray[0] = elemento[0];
    int posNewArray=1,original=elementosValidos;
    bool noRepetido=true;
    //Array que avanza linealmente
    for(int i= 1; i<original;i++){
        noRepetido=true;
        //Array que avanza para comprobacion
        for(int j=0;j<i;j++){
            if(elemento[i].compare(elemento[j])==0){
                noRepetido=false;
                elementosValidos--;
                break;
            }
        }

        if(noRepetido){
            newArray[posNewArray]=elemento[i];
            posNewArray++;
        }
    }

    for(int i=0;i<elementosValidos;i++){

        i<elementosValidos?elemento[i]=newArray[i]:elemento[i]=" ";
    }

}

int Conjunto::pertenencia(std::string elemento){
    for(int i=0; i<elementosValidos;i++){
        if(this->elemento[i]==elemento){
            return i;
        }
    }
    return -1;
}

//getElemento
std::string Conjunto::getElemento(int numElemento) {
    return elemento[numElemento];
}
//getElementosValidos
int Conjunto::getElementosValidos() {
    return elementosValidos;
}


QList<std::string> Conjunto::getElementsList(){
    QList <std::string> toReturn;
    for(int i=0;i<elementosValidos;i++){
        toReturn.append(elemento[i]);
    }
    return toReturn;
}


//setElementos
void Conjunto::setElementos(int numElemento, std::string elemento) {
    this->elemento[numElemento] = elemento;
    this->elementosValidos++;
}

void Conjunto::setElemento(int posicion, std::string elemento){
    this->elemento[posicion] = elemento;
}

void Conjunto::setElemento(std::string elemento){
    this->elemento[elementosValidos] = elemento;
    elementosValidos++;
}

//setElementosValidos
void Conjunto::setElementosValidos(int elementosValidos){
    this->elementosValidos = elementosValidos;
}

void Conjunto::toString(){
    if(elementosValidos==0){
        std::cout << "{ø}";
    } else {

        std::cout << "{";
        for(int i=0;i<elementosValidos;i++){
            if(i==elementosValidos-1){
                std::cout << elemento[i]<<"}";
            } else {
                std::	cout << elemento[i] << ", ";
            }
        }
    }
}

