//Relacion.cpp

#include "matriz.h"
#include "conjunto.h"
#include "relacion.h"
#include <iostream>

//Constructor default
Relacion::Relacion(Conjunto conjunto) : matriz(conjunto.getElementosValidos()){
    elementosValidos=0;
    this->conjunto = conjunto;
    for(int i=0;i<100;i++){
        elementoA[i] = "";
        elementoB[i] = "";
        elementos[i] = "";
    }
}

Relacion::Relacion():matriz(1){
    elementosValidos=0;
    for(int i=0;i<100;i++){
        elementoA[i]="";
        elementoB[i]="";
        elementos[i]="";
    }

}

//Funciones propias
void Relacion::update(){
    std::string newElementoA[100];
    std::string newElementoB[100];
    std::string newElementos[100];
    newElementoA[0] = elementoA[0];
    newElementoB[0] = elementoB[0];
    newElementos[0] = elementos[0];

    int posNewArray=1, original=elementosValidos;
    bool noRepetido=true;

    for(int i=1; i<original;i++){
        noRepetido=true;

        for(int j=0; j<i;j++){
            if(elementos[i]==elementos[j]){
                noRepetido=false;
                elementosValidos--;
                break;
            }
        }
        if(noRepetido){
            newElementoA[posNewArray] = elementoA[i];
            newElementoB[posNewArray] = elementoB[i];
            newElementos[posNewArray] = elementos[i];
            posNewArray++;
        }
    }

    for(int i=0;i<original;i++){
        if(i<elementosValidos){
            elementos[i] = newElementos[i];
            elementoA[i] = newElementoA[i];
            elementoB[i] = newElementoB[i];
        } else {
            elementos[i] = "";
            elementoA[i] = "";
            elementoB[i] = "";
        }
    }

    //Update Matriz
    for(int i=0;i<elementosValidos;i++){
        matriz.setValor(conjunto.pertenencia(elementoA[i]),conjunto.pertenencia(elementoB[i]),true);
    }



}

bool Relacion::simetrica(){
    //Si la traspuesta de la matriz es igual a la matriz original, es simetrica
    return matriz.traspuesta().igualdad(matriz);
}

bool Relacion::reflexiva(){
    //Si identidad precede a la matriz, entonces es reflexiva
    Matriz matrizIdentidad(matriz.getCardinalidad());
    for(int i=0;i<matrizIdentidad.getCardinalidad();i++){
        matrizIdentidad.setValor(i,i,true);
    }
    return matrizIdentidad.precedencia(matriz);;
}

bool Relacion::antisimetrica(){
    //Identidad
    Matriz matrizIdentidad(matriz.getCardinalidad());
    for(int i=0;i<matriz.getCardinalidad();i++){
        matrizIdentidad.setValor(i,i,true);
    }
    return (matriz.interseccion(matriz.traspuesta())).precedencia(matrizIdentidad);
}

bool Relacion::transitiva(){

    return (matriz.multiplicacion(matriz)).precedencia(matriz);
}

bool Relacion::funcion(){
    //Verificar que solo haya un 1 en cada fila
    int quantityOfOnes=0;
    for(int i=0; i<matriz.getCardinalidad();i++){
        quantityOfOnes=0;
        for(int j=0;j<matriz.getCardinalidad(); j++) {
            if(matriz.getValor(i,j)==true){
                quantityOfOnes++;
                if(quantityOfOnes>1){
                    return false;
                }
            }
        }
        if(quantityOfOnes==0){
            return false;
        }
    }
    return true;
}

bool Relacion::inyectiva(){
    int quantityOfOnes=0;

    for(int i=0;i<matriz.getCardinalidad();i++){
        quantityOfOnes=0;
        for(int j=0;j<matriz.getCardinalidad();j++){
            if(matriz.getValor(j,i)==true){
                quantityOfOnes++;
                if(quantityOfOnes>1){
                    return false;
                }
            }
        }
        if(quantityOfOnes==0){
            return false;
        }
    }
    return true;
}

bool Relacion::sobreyectiva(){
    int quantityOfOnes=0;

    for(int i=0;i<matriz.getCardinalidad();i++){
        quantityOfOnes=0;
        for(int j=0;j<matriz.getCardinalidad();j++){
            matriz.getValor(j,i) == true ? quantityOfOnes = quantityOfOnes : quantityOfOnes++;
        }

        if(quantityOfOnes==0){
            return false;
        }
    }
    return true;
}

bool Relacion::biyectiva(){
    if(Relacion::inyectiva() && Relacion::sobreyectiva()){
        return true;
    } else {
        return false;
    }
}

bool Relacion::ordenParcial(){
    if(Relacion::reflexiva() && Relacion::transitiva() && Relacion::antisimetrica()){
        return true;
    } else {
        return false;
    }
}

bool Relacion::equivalencia(){
    if(Relacion::reflexiva() && Relacion::transitiva() && Relacion::simetrica()){
        return true;
    } else {
        return false;
    }
}

int Relacion::gradoVertice(std::string vertice){
    int i = conjunto.pertenencia(vertice);
    int grado=0;
    if(i!=-1){
        for(int j=0;j<conjunto.getElementosValidos();j++){
            if(i==j && matriz.getValor(i,j)){
                grado+=2;
            } else if(matriz.getValor(i,j)){
                grado++;
            }
        }
        return grado;
    }
    return -1;
}

bool Relacion::pertenencia(std::string elementoA, std::string elementoB){
    std::string toCompare = "(" + elementoA + "," + elementoB + ")";
    for(int i=0;i<elementosValidos;i++){
        if(toCompare == elementos[i]){
            return true;
        }
    }
    return false;
}



//Getters Y Setter
int Relacion::getElementosValidos(){
    return elementosValidos;
}

std::string Relacion::getElementoA(int pos){
    return elementoA[pos];
}

std::string Relacion::getElementoB(int pos){
    return elementoB[pos];
}

Conjunto Relacion::getConjunto(){
    return this->conjunto;
}

Matriz Relacion::getMatriz(){
    return matriz;
}

void Relacion::setElementosValidos(int elementosValidos){
    this->elementosValidos = elementosValidos;
}

void Relacion::setElementoA(int pos, std::string elementoA){
    this->elementoA[pos] = elementoA;
}

void Relacion::setElementoB(int pos, std::string elementoB){
    this->elementoB[pos] = elementoB;
}

QList <std::string> Relacion::getElementos(){
    QList <std::string> toReturn;
    for(int i=0;i<elementosValidos;i++){
        toReturn.append(elementos[i]);
    }
    return toReturn;
}

int Relacion::setElementos(std::string elementoA, std::string elementoB){


    if(conjunto.pertenencia(elementoA)!=-1&&conjunto.pertenencia(elementoB)!=-1){
        this->elementoA[elementosValidos] = elementoA;
        this->elementoB[elementosValidos] = elementoB;
        this->elementos[elementosValidos] = "("+elementoA+","+elementoB+")";
        elementosValidos++;
        return 1;
    } return 0;
}

void Relacion::addElemento(std::string elemento){
    conjunto.setElemento(elemento);
    matriz = Matriz(conjunto.getElementosValidos());
}

void Relacion::setConjunto(Conjunto conjunto){
    this->conjunto = conjunto;
}

Conjunto* Relacion::getRealConjunto(){
    return &conjunto;
}

void Relacion::toString(){
    std::cout << "{";
    for(int i=0;i<elementosValidos;i++){
        std::cout << elementos[i] << ", ";
    }
    std::cout << "}\n\nElementoA\t\tElementoB";

    for(int i=0;i<elementosValidos;i++){
        std::cout << "\n"<<elementoA[i] << "\t\t\t" << elementoB[i];
    }

    std::cout << "\n\n"<<matriz.toString();

}
