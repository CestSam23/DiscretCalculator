#ifndef GRAPHMENU_H
#define GRAPHMENU_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QWidget>
#include <QPushButton>
#include "registrobanderas.h"
#include "graphbuilder.h"

namespace Ui {
class GraphMenu;
}

class GraphMenu : public QMainWindow{
    Q_OBJECT

public:
    explicit GraphMenu(QWidget *parent = nullptr);
    ~GraphMenu();

private slots:
    void on_actionAddEllipse_triggered();
    void on_actionOneDirectionalConection_triggered();
    void on_actionSelect_triggered();
    void on_actionBidirectionalConection_triggered();
    void on_actionSelectVertices_changed();

private:
    enum class Modes;
    GraphBuilder *graphBuilder;
    RegistroBanderas registroBanderas;
    Modes mode;
    QPointF *pointTo, *pointFrom;
    QGraphicsScene *scene;
    QList <QPushButton *> vertices;

    int Vi, Vj, Ni, Nj, Vcount, Ncount;
    QGridLayout *layVertices, *layNodes;
    QWidget *widgetVertices, *widgetNodes;

    void updateVerticesScreen();
    void updateNodesScreen();
    bool eventFilter(QObject *obj, QEvent *event);
    void mouseClickedOnScene(QMouseEvent *event);
    Ui::GraphMenu *ui;
};

#endif // GRAPHMENU_H
