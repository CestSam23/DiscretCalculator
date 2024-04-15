#ifndef CONJUNTO_H
#define CONJUNTO_H
#include <string>
#include <QList>

class Conjunto {
private:

    std::string elemento[100];
    int elementosValidos;
    //void validarConjunto();

public:
    Conjunto();

    std::string getElemento(int numElemento);

    int getElementosValidos();

    QList<std::string> getElementsList();

    void setElementosValidos(int elementosValidos);

    void setElementos(int numElemento, std::string elemento);

    void setElemento(std::string elemento);

    Conjunto unionC(Conjunto conjuntoB);

    Conjunto interseccion(Conjunto conjuntoB);

    Conjunto productoCruz(Conjunto conjuntoB);

    Conjunto diferencia(Conjunto conjuntoB);

    void setElemento(int posicion, std::string elemento);

    int pertenencia(std::string elemento);

    void relaciones(Conjunto conjuntoB);

    void subconjuntos(Conjunto conjuntoB, int nSubConjuntos);

    void validarConjunto();

    void toString();
};

#endif // CONJUNTO_H
