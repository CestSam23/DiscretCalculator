#ifndef ARROWITEM_H
#define ARROWITEM_H

#include <QGraphicsItem>
#include <QPen>
#include <QBrush>

class ArrowItem : public QGraphicsItem
{
private:
    QPointF pointFrom;
    QPointF pointTo;
    QBrush brush;
    float relationWithArrow();
    void createArrayForPolygon(QPointF array[]);

public:
    //New Line
    enum { Type = UserType + 1 };
    int type() const override;
    //End of new Lines
    ArrowItem(QPointF pointFrom, QPointF pointTo,QGraphicsItem* parent = NULL);
    ArrowItem(qreal xFrom, qreal yFrom, qreal xTo, qreal yTo,QGraphicsItem* parent = NULL);
    ArrowItem(QPointF pointFrom, QPointF pointTo, QBrush brush, QGraphicsItem* parent = NULL);

    QPointF getPointFrom();
    QPointF getPointTo();
    void setBrush(const QBrush&newBrush);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

};

#endif // ARROWITEM_H
