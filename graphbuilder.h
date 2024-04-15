#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsEllipseItem>
#include "relacion.h"
#include "arrowitem.h"

class GraphBuilder{
private:
    Relacion relation;
    int relationCounter;
    QGraphicsScene *scene;
    QList <QGraphicsEllipseItem*> elipses; //Nodos
    QList <QGraphicsLineItem*> bidirectional;
    QList <ArrowItem*> unidirectional;
    QList <QGraphicsTextItem*> labels;
    QList <QGraphicsItem *> itemsAt;
    QList <QGraphicsEllipseItem *> loops;

    int positionOfElement(QGraphicsEllipseItem *toSearch);
    QPolygonF createPolygon(QPointF center);
    std::string assignLabel();

public:
    GraphBuilder(QGraphicsScene *scene);
    void addNode(QPointF coordinates);
    void addBidirectional(QPointF pointFrom, QPointF pointTo);
    void addUnidirectional(QPointF pointFrom, QPointF pointTo);
    void addLoop(QPointF coordinates);
    void focusItems(QPointF coordinates);
    void unFocusItems();
    QList<QString> findShortestPath(QPointF *pointFrom, QPointF *pointTo);


    Relacion getRelation();
    QList<QGraphicsTextItem*> getLabels();
    void deleteItemAt();
    void getItemAt();
    void getNodeAt();



};

#endif // GRAPHBUILDER_H
