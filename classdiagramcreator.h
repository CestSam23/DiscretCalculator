#ifndef CLASSDIAGRAMCREATOR_H
#define CLASSDIAGRAMCREATOR_H
#include "matriz.h"
#include "relacion.h"
#include <QGraphicsScene>
#include <QGraphicsView>

class ClassDiagramCreator{
private:
    int numberOfGroups;
    int *elementsPerRow;
    int *rowPositions;
    int yPartitions;
    QGraphicsView *canva;
    Matriz matrix;
    Matriz uniqueMatrix;
    Relacion relacion;

    int getDifferentRows();
    void deleteEqualRows();
    void updateElements();

public:

    ClassDiagramCreator(QGraphicsView *canva,Relacion relacion, Matriz matriz);
    void createClassDiagram(QGraphicsScene *scene);

};

#endif // CLASSDIAGRAMCREATOR_H
