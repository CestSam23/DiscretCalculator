#ifndef RELACIONESWINDOW_H
#define RELACIONESWINDOW_H

#include <QMainWindow>
#include "conjunto.h"
#include "relacion.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QGraphicsScene>
#include "hassdiagramcreator.h"

namespace Ui {
class relacionesWindow;
}

class relacionesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit relacionesWindow(Conjunto *conjunto, QWidget *parent = nullptr);
    ~relacionesWindow();

private slots:
    void on_QBAdd_clicked();

    void on_QBComprobar_clicked();

    void on_QBOrdenar_clicked();

private:
    Conjunto *conjunto;
    Relacion *relacion;
    QVBoxLayout *lay;
    QGridLayout *layoutMatriz;
    QWidget *widgetMatriz;
    Ui::relacionesWindow *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *nodos;
    QGraphicsTextItem *etiqueta;
    QList <QGraphicsTextItem*> etiquetas;
    QList <QGraphicsEllipseItem*> ellipses;
    HassDiagramCreator *diagrama;

    int differentElements(int toDetermine[],int numberOfElements);

    void addHassDiagram();
    void focusToElementA();
    void focusToElementB();

};

#endif // RELACIONESWINDOW_H
