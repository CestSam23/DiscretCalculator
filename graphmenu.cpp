#include "graphmenu.h"
#include "ui_graphmenu.h"
#include <QLayout>
#include <QLayoutItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QMouseEvent>
#include <QMessageBox>
enum class GraphMenu::Modes{
    none,
    ellipse,
    unidirectional,
    bidirectional,
    loop,
    vertices,
    selection
};

GraphMenu::GraphMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphMenu)
{
    Vi=Vj=Ni=Nj=Vcount=Ncount=0;

    widgetVertices = new QWidget;
    widgetNodes = new QWidget;

    layVertices = new QGridLayout(widgetVertices);
    layNodes = new QGridLayout(widgetNodes);

    widgetVertices->setStyleSheet("background-color:#AEB4A6;");
    widgetNodes->setStyleSheet("background-color:#AEB4A6;");

    scene = new QGraphicsScene();
    graphBuilder = new GraphBuilder(scene);
    ui->setupUi(this);
    ui->SANodes->setWidget(widgetNodes);
    ui->SAVertices->setWidget(widgetVertices);
    ui->GVCanva->setScene(scene);
    ui->GVCanva->installEventFilter(this);

}

GraphMenu::~GraphMenu(){
    delete ui;
}

void GraphMenu::updateVerticesScreen(){
    QList <QGraphicsTextItem *> itemList = graphBuilder->getLabels();

    for(int i=Vcount;i<itemList.size();i++){
        QPushButton *boton1 = new QPushButton(QString::fromStdString(
                                              itemList[i]->toPlainText().toStdString()));
        boton1->setStyleSheet("	QPushButton{background-color: #B27A62;color: white; border-radius: 3px;} QPushButton:hover{background-color:#864F45;}");
        connect(boton1,&QPushButton::clicked,[this,boton1,i,itemList](){
            QMessageBox::information(nullptr,"Informacion del Vertice","Verice " + boton1->text() + "\nGrado: " + QString::number(graphBuilder->getRelation().gradoVertice(itemList[i]->toPlainText().toStdString()))
                                     ,QMessageBox::Ok);
        });
        vertices.append(boton1);
        if(i%4==0){
            Vi=0;
            Vj++;
        } else {
            Vi++;
        }
        layVertices->addWidget(boton1,Vi,Vj);
        Vcount++;
    }
}

void GraphMenu::updateNodesScreen(){
    QList <std::string> itemList = graphBuilder->getRelation().getElementos();

    for(int i=Ncount;i<itemList.size();i++){
        QPushButton *boton1 = new QPushButton(QString::fromStdString(itemList[i]));
        boton1->setStyleSheet("	background-color: #B27A62;color: white; border-radius: 3px;");

        if(i%4==0){
            Ni=0;
            Nj++;
        } else {
            Ni++;
        }
        layNodes->addWidget(boton1,Ni,Nj);
        Ncount++;
    }
}

void GraphMenu::mouseClickedOnScene(QMouseEvent *event){
    QPointF position = ui->GVCanva->mapToScene(event->pos());
    switch(mode){
        case Modes::ellipse:
            graphBuilder->addNode(position);
            updateVerticesScreen();
            break;
        case Modes::unidirectional:
            if(registroBanderas.getOneClickArrow()){
                pointTo = &position;
                double margin = 10;

                if (!(std::abs(pointFrom->x() - pointTo->x()) <= margin &&
                     std::abs(pointFrom->y() - pointTo->y()) <= margin)){

                    graphBuilder->addUnidirectional(*pointFrom,*pointTo);
                    ui->GVCanva->viewport()->update();
                    updateNodesScreen();
                }
                registroBanderas.setOneClickArrow(false);
                registroBanderas.setTwoClickArrow(false);
                ui->actionAddEllipse->setEnabled(true);
                ui->actionBidirectionalConection->setEnabled(true);
                ui->actionOneDirectionalConection->setEnabled(true);
                ui->actionSelect->setEnabled(true);
                ui->actionSelectVertices->setEnabled(true);
            } else {
                ui->actionAddEllipse->setEnabled(false);
                ui->actionBidirectionalConection->setEnabled(false);
                ui->actionOneDirectionalConection->setEnabled(false);
                ui->actionSelect->setEnabled(false);
                ui->actionSelectVertices->setEnabled(false);
                pointFrom = new QPointF(position);
                registroBanderas.setOneClickArrow(true);

            }
            break;
        case Modes::bidirectional:
            if(registroBanderas.getOneClickArrow()){
                pointTo = &position;

                double margin=10;
                registroBanderas.setOneClickArrow(false);
                registroBanderas.setTwoClickArrow(false);
                ui->actionAddEllipse->setEnabled(true);
                ui->actionBidirectionalConection->setEnabled(true);
                ui->actionOneDirectionalConection->setEnabled(true);
                ui->actionSelect->setEnabled(true);
                ui->actionSelectVertices->setEnabled(true);
                if((!(std::abs(pointFrom->x() - pointTo->x()) <= margin &&
                       std::abs(pointFrom->y() - pointTo->y()) <= margin))){

                    graphBuilder->addBidirectional(*pointFrom,*pointTo);
                    ui->GVCanva->viewport()->update();
                    updateNodesScreen();
                    break;
                }

                mode = Modes::loop;
                GraphMenu::mouseClickedOnScene(event);


            } else {
                ui->actionAddEllipse->setEnabled(false);
                ui->actionBidirectionalConection->setEnabled(false);
                ui->actionOneDirectionalConection->setEnabled(false);
                ui->actionSelect->setEnabled(false);
                ui->actionSelectVertices->setEnabled(false);
                pointFrom = new QPointF(position);
                registroBanderas.setOneClickArrow(true);

            }
            break;
        case Modes::selection:
            if(registroBanderas.getOneClickArrow()){
                pointTo = &position;
                double margin = 10;

                if (!(std::abs(pointFrom->x() - pointTo->x()) <= margin &&
                      std::abs(pointFrom->y() - pointTo->y()) <= margin)){

                    QList <QString> path = graphBuilder->findShortestPath(pointFrom,pointTo);
                    QMessageBox msgBox;
                    if(!path.isEmpty()){
                        std::string message = "Shortest path is: ";
                        for(int i=0;i<path.size();i++){
                            message += " " + path[i].toStdString();
                        }
                        msgBox.setText(QString::fromStdString(message));
                        msgBox.exec();
                    } else {
                        msgBox.setText("No shortest path");
                        msgBox.exec();
                    }

                }
                registroBanderas.setOneClickArrow(false);
                registroBanderas.setTwoClickArrow(false);
                ui->actionAddEllipse->setEnabled(true);
                ui->actionBidirectionalConection->setEnabled(true);
                ui->actionOneDirectionalConection->setEnabled(true);
                ui->actionSelect->setEnabled(true);
                ui->actionSelectVertices->setEnabled(true);
            } else {
                ui->actionAddEllipse->setEnabled(false);
                ui->actionBidirectionalConection->setEnabled(false);
                ui->actionOneDirectionalConection->setEnabled(false);
                ui->actionSelect->setEnabled(false);
                ui->actionSelectVertices->setEnabled(false);
                pointFrom = new QPointF(position);
                registroBanderas.setOneClickArrow(true);

            }


            break;
        case Modes::vertices:
            if(registroBanderas.getChangesOnVertices()){
                registroBanderas.setChangesOnVertices(false);
                graphBuilder->unFocusItems();

            }
            graphBuilder->focusItems(position);
            registroBanderas.setChangesOnVertices(true);
            break;
        case Modes::loop:

            graphBuilder->addLoop(position);
            updateNodesScreen();
            mode = Modes::bidirectional;
            break;
        case Modes::none:
            break;

    }
}

void GraphMenu::on_actionAddEllipse_triggered(){
    bool actionEllipseTriggered = ui->actionAddEllipse->isChecked();
    if(actionEllipseTriggered){
        mode = Modes::ellipse;
        ui->actionBidirectionalConection->setChecked(false);
        ui->actionOneDirectionalConection->setChecked(false);
        ui->actionSelect->setChecked(false);
        ui->actionSelectVertices->setChecked(false);
    } else {
        mode = Modes::none;
    }
}

void GraphMenu::on_actionOneDirectionalConection_triggered(){
    bool actionUnidirectionalTriggered = ui->actionOneDirectionalConection->isChecked();
    if(actionUnidirectionalTriggered){
        mode = Modes::unidirectional;
        ui->actionBidirectionalConection->setChecked(false);
        ui->actionAddEllipse->setChecked(false);
        ui->actionSelect->setChecked(false);
        ui->actionSelectVertices->setChecked(false);
    } else {
        mode = Modes::none;
    }
}

void GraphMenu::on_actionSelect_triggered(){
    bool actionSelectTriggered = ui->actionSelect->isChecked();
    if(actionSelectTriggered){
        mode = Modes::selection;
        ui->actionBidirectionalConection->setChecked(false);
        ui->actionOneDirectionalConection->setChecked(false);
        ui->actionAddEllipse->setChecked(false);
        ui->actionSelectVertices->setChecked(false);
    } else {
        mode = Modes::none;
    }
}

void GraphMenu::on_actionSelectVertices_changed()
{
    bool actionVerticesTriggered = ui->actionSelectVertices->isChecked();
    if(actionVerticesTriggered){
        mode = Modes::vertices;
        ui->actionBidirectionalConection->setChecked(false);
        ui->actionOneDirectionalConection->setChecked(false);
        ui->actionSelect->setChecked(false);
        ui->actionAddEllipse->setChecked(false);
    } else if((mode == Modes::bidirectional || mode == Modes::unidirectional ||
                mode == Modes::ellipse       || mode == Modes::selection) && registroBanderas.getChangesOnVertices()){
        graphBuilder->unFocusItems();

        registroBanderas.setChangesOnVertices(false);

    }  else if((mode == Modes::vertices) && registroBanderas.getChangesOnVertices()){
        registroBanderas.setChangesOnVertices(false);
        graphBuilder->unFocusItems();


    }else if((mode == Modes::bidirectional || mode == Modes::unidirectional ||
                mode == Modes::ellipse       || mode == Modes::selection)){

    } else {
        mode = Modes::none;

    }
}

void GraphMenu::on_actionBidirectionalConection_triggered(){
    bool actionBidirectionalTriggered = ui->actionBidirectionalConection->isChecked();
    if(actionBidirectionalTriggered){
        mode = Modes::bidirectional;
        ui->actionAddEllipse->setChecked(false);
        ui->actionOneDirectionalConection->setChecked(false);
        ui->actionSelect->setChecked(false);
        ui->actionSelectVertices->setChecked(false);
    } else {
        mode = Modes::none;
    }
}

bool GraphMenu::eventFilter(QObject *obj, QEvent *event){
    if (obj == ui->GVCanva && event->type() == QEvent::MouseButtonPress) {
        // El evento de clic en el QGraphicsView ha ocurrido
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        mouseClickedOnScene(mouseEvent);
        return true;  // Indica que el evento ha sido manejado
    }

    // Deja que el objeto base maneje otros eventos
    return QObject::eventFilter(obj, event);
}



