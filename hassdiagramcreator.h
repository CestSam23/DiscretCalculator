#ifndef HASSDIAGRAMCREATOR_H
#define HASSDIAGRAMCREATOR_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include "matriz.h"
#include "relacion.h"

class HassDiagramCreator{
private:

    QGraphicsView *canva;
    int numberElements;
    int *xPartitions;
    int yPartitions;
    Matriz matriz;
    Matriz unsortedMatrix;
    Relacion relacion;
    Relacion originalRelation;
    double* repeatedFrequency;

    void updateFrequency();
    void updateXPartitions();
    void sortFrequency();
    int differentElements();
    Matriz buildConnectionMatrix(Matriz toBuild);


public:
    QList <QGraphicsTextItem*> etiquetas;
    QList <QGraphicsEllipseItem*> ellipses;
    QList <QGraphicsLineItem*> connections;
    //Constructor
    HassDiagramCreator(QGraphicsView *canva,Relacion relacion, Matriz matriz);
    //Own Functions
    void createHassDiagram(QGraphicsScene *scene);
    void createConnections(QGraphicsScene *scene);
    void topologicSort(QGraphicsScene *scene);
    void topologicSortWithAnimation(QGraphicsScene *scene);
    //Getters and Setters
};

#endif // HASSDIAGRAMCREATOR_H
