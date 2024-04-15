#include "matriz.h"
#include <iostream>

//Constructor
Matriz::Matriz(int cardinalidad){
    this->cardinalidad = cardinalidad;
    matriz = new bool*[cardinalidad];
    for(int i=0;i<cardinalidad;i++){
        matriz[i] = new bool[cardinalidad];
    }

    for(int i=0;i<cardinalidad;i++){
        for(int j=0;j<cardinalidad;j++){
            matriz[i][j] = false;
        }
    }
}


//Funciones propias
Matriz Matriz::multiplicacion(Matriz matriz2){
    Matriz m(cardinalidad);
    //Posicion a saber valor
    for(int i=0;i<cardinalidad;i++){
        for(int j=0;j<cardinalidad;j++){
            //Multiplicacion
            for(int k=0;k<cardinalidad;k++){
                if(matriz[i][k]*matriz2.getValor(k,j)){
                    m.setValor(i,j,true);
                    break;
                } else {
                    m.setValor(i,j,false);
                }
            }
        }
    }
    return m;
}

Matriz Matriz::diferencia(Matriz sustraendo){
    Matriz resta(cardinalidad);
    for(int i=0;i<cardinalidad;i++){
        for(int j=0;j<cardinalidad;j++){
            if(matriz[i][j]==1 && sustraendo.getValor(i,j)==1){
                resta.setValor(i,j,false);
            } else {
                resta.setValor(i,j,matriz[i][j]);
            }
        }
    }
    return resta;
}

Matriz Matriz::traspuesta(){
    Matriz m(cardinalidad);
    for(int i=0;i<cardinalidad;i++){
        for(int j=0;j<cardinalidad;j++){
            m.setValor(j,i,matriz[i][j]);
        }
    }

    return m;
}

bool Matriz::precedencia(Matriz matriz2){

    for(int i=0;i<cardinalidad;i++){
        for(int j=0;j<cardinalidad;j++){
            if(matriz[i][j]==true && matriz2.getValor(i,j)!=true){
                return false;
            }
        }
    }

    return true;
}

std::string Matriz::toString(){
    std::string toReturn="";

    for(int i=0;i<cardinalidad;i++){
        for(int j=0; j<cardinalidad; j++){
            if(matriz[i][j]){
                toReturn+="<True>\t\t";
            } else {
                toReturn+="<False>\t\t";
            }
        }
        toReturn+="\n";
    }

    return toReturn;
}

Matriz Matriz::interseccion(Matriz matriz2){
    //Comprobar que sean de la misma cardinalidad
    if(cardinalidad != matriz2.getCardinalidad()){
        return *this;
    }

    Matriz matrizIntersectada(cardinalidad);
    for(int i=0;i<cardinalidad; i++){
        for(int j=0;j<cardinalidad;j++){
            if(matriz[i][j] == true && matriz2.getValor(i,j)==true){
                matrizIntersectada.setValor(i,j,true);
            }
        }

    }
    return matrizIntersectada;
}

bool Matriz::igualdad(Matriz matriz2){
    //Comprobar que sean de la misma cardinalidad
    if(cardinalidad != matriz2.getCardinalidad()){
        return false;
    }

    for(int i=0;i<cardinalidad;i++){
        for(int j=0;j<cardinalidad;j++){
            if(matriz[i][j]!=matriz2.getValor(i,j)){
                return false;
            }
        }
    }

    return true;
}

//Getters y setters
bool Matriz::getValor(int fila, int columna){
    return matriz[fila][columna];
}

void Matriz::setValor(int fila, int columna, bool valor){
    matriz[fila][columna] = valor;
}

int Matriz::getCardinalidad(){
    return cardinalidad;
}

Conjunto Matriz::getConjunto(){
    return conjunto;

}
