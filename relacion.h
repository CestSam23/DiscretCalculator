//Relacion.h

#ifndef RELACION_H
#define RELACION_H

#include <string>
#include "Conjunto.h"
#include "Matriz.h"
#include <QList>
class Relacion{
private:
    std::string elementoA[100];
    std::string elementoB[100];
    std::string elementos[100];
    Conjunto conjunto;
    Matriz matriz;
    int elementosValidos;

public:
    Relacion(Conjunto conjunto);
    Relacion();
    //Funciones propias
    void update();
    bool simetrica();
    bool reflexiva();
    bool antisimetrica();
    bool transitiva();
    bool funcion();
    bool inyectiva();
    bool sobreyectiva();
    bool biyectiva();
    bool ordenParcial();
    bool equivalencia();
    int gradoVertice(std::string vertice);
    void toString();



    //Getters y Setters
    int getElementosValidos();
    std::string getElementoA(int pos);
    std::string getElementoB(int pos);
    QList<std::string> getElementos();
    Conjunto getConjunto();
    Matriz getMatriz();
    void setElementosValidos(int elementosValidos);
    void setElementoA(int pos, std::string elementoA);
    void setElementoB(int pos, std::string elementoB);
    void setConjunto(Conjunto conjunto);
    int setElementos(std::string elementoA, std::string elementoB);
    void addElemento(std::string elemento);
    Conjunto* getRealConjunto();
    bool pertenencia(std::string elementoA, std::string elementoB);

};



#endif //RELACION_H
