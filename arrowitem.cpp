#include "arrowitem.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QPen>
#include <cmath>
ArrowItem::ArrowItem(QPointF pointFrom, QPointF pointTo, QGraphicsItem* parent)
    :QGraphicsItem(parent){
    this->pointFrom = pointFrom;
    this->pointTo = pointTo;
    brush = QBrush(Qt::black);
}

ArrowItem::ArrowItem(qreal xFrom, qreal yFrom, qreal xTo, qreal yTo,QGraphicsItem* parent)
    :QGraphicsItem(parent){
    this->pointFrom = QPointF(xFrom,yFrom);
    this->pointTo = QPointF(xTo, yTo);
    brush = QBrush(Qt::black);
}

ArrowItem::ArrowItem(QPointF pointFrom, QPointF pointTo, QBrush brush, QGraphicsItem* parent)
    :QGraphicsItem(parent){
    this->pointFrom = pointFrom;
    this->pointTo = pointTo;
    this->brush = brush;
}

QRectF ArrowItem::boundingRect() const {
    qreal minX = qMin(pointFrom.x(), pointTo.x());
    qreal minY = qMin(pointFrom.y(), pointTo.y());
    qreal maxX = qMax(pointFrom.x(), pointTo.x());
    qreal maxY = qMax(pointFrom.y(), pointTo.y());

    return QRectF(minX, minY, maxX - minX, maxY - minY);
}
int ArrowItem::type() const {
    return Type;
}


void ArrowItem::createArrayForPolygon(QPointF array[]){
    float relation = ArrowItem::relationWithArrow();
    int x = pointTo.x();
    int y = pointTo.y();
    array[0]=QPointF(x,y);

    if(relation > 7){
        QPointF Sv1(pointTo-pointFrom);
        qreal modulo = sqrt(pow(Sv1.x(),2)+pow(Sv1.y(),2));
        QPointF unitary((Sv1.x()/modulo)*7,
                        ((Sv1.y()/modulo))*7);
        QPointF unitary2(Sv1-unitary);
        QPointF temp((unitary2.x()+pointFrom.x()),
                     ((unitary2.y())+pointFrom.y()));
        QPointF Sv (temp-pointTo);
        array[1] = QPointF(Sv.y()+Sv.x()+pointTo.x(),((Sv.x())*-1)+Sv.y()+pointTo.y());
        array[2] = QPointF(((Sv.y())*-1)+Sv.x()+pointTo.x(),Sv.x()+Sv.y()+pointTo.y());

    } else {
        QPointF temp(((pointTo.x()-pointFrom.x())*.9)+pointFrom.x(),
                     ((pointTo.y()-pointFrom.y())*.9)+pointFrom.y());
        QPointF Sv (temp-pointTo);
        array[1] = QPointF(Sv.y()+Sv.x()+pointTo.x(),((Sv.x())*-1)+Sv.y()+pointTo.y());
        array[2] = QPointF(((Sv.y())*-1)+Sv.x()+pointTo.x(),Sv.x()+Sv.y()+pointTo.y());
    }


}

void ArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setBrush(brush);
    painter->setPen(brush.color());
    painter->drawLine(pointFrom,pointTo);
    QPointF points[3];
    ArrowItem::createArrayForPolygon(points);
    painter->drawPolygon(points,3);


}

float ArrowItem::relationWithArrow(){
    int x = pointTo.x()-pointFrom.x();
    int y = pointTo.y()-pointFrom.y();

    float module = sqrt(pow(x,2)+pow(y,2));



    return module*.10;
}

void ArrowItem::setBrush(const QBrush&newBrush){
    brush = newBrush;
    update();
}

QPointF ArrowItem::getPointFrom(){
    return pointFrom;
}

QPointF ArrowItem::getPointTo(){
    return pointTo;
}
