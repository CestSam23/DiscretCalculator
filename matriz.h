//Matriz.h
#ifndef MATRIZ_H
#define MATRIZ_H

#include <string>
#include "Conjunto.h"

class Matriz{
private:
    bool** matriz;
    int cardinalidad;
    Conjunto conjunto;

public:
    //Constructor
    Matriz(int cardinalidad);
    Matriz();

    //Funciones Propias
    bool precedencia(Matriz matriz2);
    bool igualdad(Matriz matriz2);
    Matriz multiplicacion(Matriz matriz2);
    Matriz traspuesta();
    Matriz interseccion(Matriz matriz2);
    Matriz diferencia(Matriz sustraendo);
    std::string toString();


    //Getters y Setter
    bool getValor(int fila, int columna);
    void setValor(int fila, int columna, bool valor);
    int getCardinalidad();
    Conjunto getConjunto();

};
#endif
