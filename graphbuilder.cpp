#include "graphbuilder.h"
#include "arrowitem.h"
#include <cmath>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTransform>
#include <QPolygonF>
#include <QPen>
#include <QList>
#include <queue>
#include <unordered_map>

GraphBuilder::GraphBuilder(QGraphicsScene *scene){
    this->scene = scene;
    QGraphicsLineItem *rect1 = new QGraphicsLineItem(0,0,419,0);
    QGraphicsLineItem *rect2 = new QGraphicsLineItem(0,0,0,481);
    QGraphicsLineItem *rect3 = new QGraphicsLineItem(419,0,419,0);
    QGraphicsLineItem *rect4 = new QGraphicsLineItem(0,481,0,481);
    scene->addItem(rect1);
    scene->addItem(rect2);
    scene->addItem(rect3);
    scene->addItem(rect4);

    relationCounter=0;
}


void GraphBuilder::addNode(QPointF coordinates){
    QGraphicsEllipseItem *elipse = new QGraphicsEllipseItem(coordinates.x(),coordinates.y(),10,10);
    elipse->setBrush(Qt::red);
    elipses.append(elipse);
    elipse->setZValue(1);
    scene->addItem(elipse);
    std::string text = assignLabel();
    QGraphicsTextItem *label = scene->addText(QString::fromStdString(text));
    label->setPos(coordinates.x(),coordinates.y()-20);

    labels.append(label);
    relation.addElemento(text);
    relationCounter++;
}

void GraphBuilder::focusItems(QPointF coordinates){
    itemsAt = scene->items(createPolygon(coordinates),Qt::ItemSelectionMode::IntersectsItemShape);
    for(int i=0; i<itemsAt.size();i++){
        if(itemsAt[i]->type()==ArrowItem::Type){
            ArrowItem *arrowItem = qgraphicsitem_cast<ArrowItem *>(itemsAt[i]);
            if (arrowItem) {
                QPointF pointFrom = arrowItem->getPointFrom();
                QPointF pointTo = arrowItem->getPointTo();

                double margin = 10;

                if (!(std::abs(coordinates.x() - pointTo.x()) <= margin &&
                     std::abs(coordinates.y() - pointTo.y()) <= margin)){
                    arrowItem->setBrush(Qt::red);
                }
            }
        } else if (itemsAt[i] -> type() == QGraphicsLineItem::Type){
            QGraphicsLineItem *lineItem = qgraphicsitem_cast<QGraphicsLineItem *>(itemsAt[i]);
            if (lineItem) {
                lineItem->setPen(QPen(Qt::red));
            }
        } else if(itemsAt[i] -> type() == QGraphicsEllipseItem::Type){
            QGraphicsEllipseItem *elipseItem = qgraphicsitem_cast<QGraphicsEllipseItem *>(itemsAt[i]);
            if(elipseItem && elipseItem->boundingRect().height()>20){
                elipseItem->setPen(QPen(Qt::red));
            }
        }
    }

}

void GraphBuilder::unFocusItems(){
    for(int i=0;i<itemsAt.size();i++){
        if(itemsAt[i]->type()==ArrowItem::Type){
            ArrowItem *arrowItem = qgraphicsitem_cast<ArrowItem *>(itemsAt[i]);
            if (arrowItem) {
                arrowItem->setBrush(Qt::black);
            }
        } else if (itemsAt[i] -> type() == QGraphicsLineItem::Type){
            QGraphicsLineItem *lineItem = qgraphicsitem_cast<QGraphicsLineItem *>(itemsAt[i]);
            if (lineItem) {
                lineItem->setPen(QPen(Qt::black));
            }
        } else if(itemsAt[i] -> type() == QGraphicsEllipseItem::Type){
            QGraphicsEllipseItem *elipseItem = qgraphicsitem_cast<QGraphicsEllipseItem *>(itemsAt[i]);
            if(elipseItem && elipseItem->boundingRect().height()>20){
                elipseItem->setPen(QPen(Qt::black));
            }
        }
    }
}

void GraphBuilder::addBidirectional(QPointF pointFrom, QPointF pointTo){
    QGraphicsItem *itemFrom, *itemTo;
    if((itemFrom=scene->itemAt(pointFrom,QTransform()))!=nullptr&&
            (itemTo=scene->itemAt(pointTo,QTransform())) !=nullptr&&
            itemFrom->type() == QGraphicsEllipseItem::Type&&
            itemTo->type() == QGraphicsEllipseItem::Type){

        QPen *black = new QPen();
        black->setColor(Qt::black);


        QGraphicsLineItem *conection1 = new QGraphicsLineItem(pointFrom.x(),pointFrom.y(),pointTo.x(),pointTo.y());

        QGraphicsEllipseItem *elipseFrom = qgraphicsitem_cast<QGraphicsEllipseItem *>(itemFrom);
        QGraphicsEllipseItem *elipseTo = qgraphicsitem_cast<QGraphicsEllipseItem *>(itemTo);

        scene->addItem(conection1);
        bidirectional.append(conection1);

        int positionFrom = positionOfElement(elipseFrom);
        int positionTo = positionOfElement(elipseTo);

        relation.setElementos(labels[positionFrom]->toPlainText().toStdString(),
                              labels[positionTo]->toPlainText().toStdString());
        relation.setElementos(labels[positionTo]->toPlainText().toStdString(),
                              labels[positionFrom]->toPlainText().toStdString());

        relation.update();
    }
}

void GraphBuilder::addUnidirectional(QPointF pointFrom, QPointF pointTo){
    QGraphicsItem *itemFrom, *itemTo;
    if((itemFrom=scene->itemAt(pointFrom,QTransform()))!=nullptr&&
        (itemTo=scene->itemAt(pointTo,QTransform()))!=nullptr&&
        itemFrom->type() == QGraphicsEllipseItem::Type&&
        itemTo->type() == QGraphicsEllipseItem::Type){

        ArrowItem *connection = new ArrowItem(pointFrom,pointTo);
        scene->addItem(connection);
        unidirectional.append(connection);

        QGraphicsEllipseItem *elipseFrom = qgraphicsitem_cast<QGraphicsEllipseItem *>(itemFrom);
        QGraphicsEllipseItem *elipseTo = qgraphicsitem_cast<QGraphicsEllipseItem *>(itemTo);
        int positionFrom = positionOfElement(elipseFrom);
        int positionTo = positionOfElement(elipseTo);
        relation.setElementos(labels[positionFrom]->toPlainText().toStdString(),
                              labels[positionTo]->toPlainText().toStdString());

        relation.update();
    }
}

std::string GraphBuilder::assignLabel(){
    std::string toReturn;
    if(relationCounter>=26){
        int firstPart=(relationCounter/26)+64;
        toReturn.append(1,(char)firstPart);
        toReturn.append(1,(char)((relationCounter%26))+65);
    } else {
        toReturn.append(1,(char)relationCounter+65);
    }
    return toReturn;

}

void GraphBuilder::addLoop(QPointF coordinates){

    QGraphicsItem *itemFrom;
    if((itemFrom=scene->itemAt(coordinates,QTransform()))!=nullptr&&
        itemFrom->type() == QGraphicsEllipseItem::Type){


        // Calcular las coordenadas del centro del círculo desplazado 30 unidades a la izquierda
        QPointF centroDesplazado(coordinates.x() - 12, coordinates.y());

        // Calcular el radio del círculo (distancia entre el punto original y el centro desplazado)
        qreal radio = std::sqrt(std::pow(centroDesplazado.x() - coordinates.x(), 2) +
                                std::pow(centroDesplazado.y() - coordinates.y(), 2));

        // Crear el objeto QGraphicsEllipseItem para el círculo
        QGraphicsEllipseItem *loop =
            new QGraphicsEllipseItem(centroDesplazado.x() - radio, centroDesplazado.y() - radio, radio * 2, radio * 2);

        scene->addItem(loop);
        loops.append(loop);
        loops.append(loop);

        QGraphicsEllipseItem *elipseFrom = qgraphicsitem_cast<QGraphicsEllipseItem *>(itemFrom);
        int positionFrom = positionOfElement(elipseFrom);
        relation.setElementos(labels[positionFrom]->toPlainText().toStdString(),
                              labels[positionFrom]->toPlainText().toStdString());

        relation.update();
    }
}

int GraphBuilder::positionOfElement(QGraphicsEllipseItem *toSearch){
    int i=0;
    while(i!=elipses.size()){
        if(elipses[i] == toSearch){
            return i;
        }
        i++;
    }
    return -1;
}

QPolygonF GraphBuilder::createPolygon(QPointF center){
    double angleStep = 2*M_PI/5;
    QPolygonF polygon;
    for(int i=0;i<5;++i){
        double angle = i*angleStep;
        double x = center.x() + 15*std::cos(angle);
        double y = center.y() + 15*std::sin(angle);
        polygon << QPointF(x,y);
    }

    return polygon;
}

Relacion GraphBuilder::getRelation(){
    return relation;
}

QList<QGraphicsTextItem*> GraphBuilder::getLabels(){
    return labels;
}



QList<QString> GraphBuilder::findShortestPath(QPointF *pointFrom, QPointF *pointTo) {
    QString start; QString end;
    QList<QGraphicsItem*> listFrom,listTo;
    listFrom = scene->items(createPolygon(*pointFrom),Qt::ItemSelectionMode::IntersectsItemShape);
    listTo = scene->items(createPolygon(*pointTo),Qt::ItemSelectionMode::IntersectsItemShape);

    for(int i=0; i<listFrom.size();i++){
        if(listFrom[i]->type()==QGraphicsTextItem::Type){
            QGraphicsTextItem *textFrom = qgraphicsitem_cast<QGraphicsTextItem *>(listFrom[i]);
            start=textFrom->toPlainText();
        }
    }
    for(int i=0; i<listTo.size();i++){
        if(listTo[i]->type()==QGraphicsTextItem::Type){
            QGraphicsTextItem *textTo = qgraphicsitem_cast<QGraphicsTextItem *>(listTo[i]);
            end=textTo->toPlainText();
        }
    }

    QList<QString> path;

    // Verificar que los nodos de inicio y fin existan
    int startIndex = -1, endIndex = -1;
    for (int i = 0; i < labels.size(); ++i) {
        if (labels[i]->toPlainText() == start) {
            startIndex = i;
        }
        if (labels[i]->toPlainText() == end) {
            endIndex = i;
        }
    }

    if (startIndex == -1 || endIndex == -1) {
        // Nodo de inicio o fin no encontrado
        return path;
    }

    // Algoritmo de búsqueda en anchura (BFS)
    std::queue<int> bfsQueue;
    std::unordered_map<int, int> parentMap;

    bfsQueue.push(startIndex);
    parentMap[startIndex] = -1;

    while (!bfsQueue.empty()) {
        int current = bfsQueue.front();
        bfsQueue.pop();

        if (current == endIndex) {
            // Construir el camino desde el nodo de inicio hasta el nodo de fin
            int node = endIndex;
            while (node != -1) {
                path.prepend(labels[node]->toPlainText());
                node = parentMap[node];
            }
            return path;
        }

        for (int i = 0; i < labels.size(); ++i) {
            if (relation.getMatriz().getValor(current, i) && parentMap.find(i) == parentMap.end()) {
                // El nodo no ha sido visitado
                bfsQueue.push(i);
                parentMap[i] = current;
            }
        }
    }

    // No se encontró un camino
    return path;
}
