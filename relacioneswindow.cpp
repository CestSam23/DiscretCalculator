#include "relacioneswindow.h"
#include "ui_relacioneswindow.h"
#include "conjunto.h"
#include "relacion.h"
#include "hassdiagramcreator.h"
#include "classdiagramcreator.h"
#include <QGraphicsTextItem>


relacionesWindow::relacionesWindow(Conjunto *conjunto,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::relacionesWindow)
{
    this->conjunto = conjunto;
    relacion = new Relacion(*conjunto);
    ui->setupUi(this);

    lay = new QVBoxLayout();
    ui->QAreaComponentes->setLayout(lay);

    connect(ui->QLElementoA,&QLineEdit::returnPressed,this,&relacionesWindow::focusToElementB);
    connect(ui->QLElementoB,&QLineEdit::returnPressed,this,&relacionesWindow::on_QBAdd_clicked);

    widgetMatriz = new QWidget;

    widgetMatriz -> setStyleSheet("background-color:#AEB4A6;");
    layoutMatriz = new QGridLayout(widgetMatriz);
    //Stylesheet widget
    ui->QAreaMatriz->setWidget(widgetMatriz);
    ui->QBOrdenar->setEnabled(false);

    scene = new QGraphicsScene(this);
    ui->QAreaDiagrama->setScene(scene);
}

relacionesWindow::~relacionesWindow()
{
    delete ui;
}

void relacionesWindow::on_QBAdd_clicked()
{
    std::string elementoA, elementoB;
    elementoA = ui->QLElementoA->text().toStdString();
    elementoB = ui->QLElementoB->text().toStdString();
    if(elementoA!=""&&elementoB!=""){
        if(relacion->setElementos(elementoA,elementoB)!=0){
            //Añadir a Matriz el elemento
            QPushButton *buton1 = new QPushButton(QString::fromStdString("("+elementoA+","+elementoB+")"));
            buton1->setStyleSheet("	background-color: #B27A62;color: white; border-radius: 3px;");
            //Stylesheet
            lay->addWidget(buton1);
            ui->QLElementoA->setText(QString::fromStdString(""));
            ui->QLElementoB->setText(QString::fromStdString(""));
            relacionesWindow::focusToElementA();
        } else {
            //De alguna forma mostrar error
        }
    } else {
        relacionesWindow::focusToElementA();
    }
}


void relacionesWindow::on_QBComprobar_clicked()
{
    relacion->update();
    int originalCount = ui->QCBPropiedades->count();
    for(int i=0;i<originalCount;i++){
        ui->QCBPropiedades->removeItem(0);
    }
    //Relaciones
    if(relacion->funcion()){
        ui->QCBPropiedades->addItem(QString::fromStdString("Funcion"));
    }
    if(relacion->sobreyectiva()){
        ui->QCBPropiedades->addItem(QString::fromStdString("Sobreyectiva"));
    }
    if(relacion->inyectiva()){
        ui->QCBPropiedades->addItem(QString::fromStdString("Inyectiva"));
    }
    if(relacion->biyectiva()){
        ui->QCBPropiedades->addItem(QString::fromStdString("Biyectiva"));
    }

    //Matriz
    QPushButton *boton1;

    for(int i=0;i<relacion->getMatriz().getCardinalidad();i++){
        for(int j=0;j<relacion->getMatriz().getCardinalidad();j++){

            if(relacion->getMatriz().getValor(i,j)==true){
                boton1 = new QPushButton(QString::fromStdString("1"));
            } else {
                boton1 = new QPushButton(QString::fromStdString("0"));
            }
            boton1->setStyleSheet("	background-color: #B27A62;color: white; border-radius: 3px;");
            layoutMatriz->addWidget(boton1,i,j);
        }
    }


    if(relacion->ordenParcial()){
        ui->QBOrdenar->setEnabled(true);
        HassDiagramCreator *hass = new HassDiagramCreator(ui->QAreaDiagrama,*relacion,relacion->getMatriz());
        hass->createHassDiagram(scene);
        hass->createConnections(scene);

        diagrama = hass;
        ui->QCBPropiedades->addItem(QString::fromStdString("Relacion de Orden Parcial"));

    } else if(relacion->equivalencia()){
        ui->QBOrdenar->setEnabled(false);
        ClassDiagramCreator classD(ui->QAreaDiagrama,*relacion,relacion->getMatriz());
        classD.createClassDiagram(scene);
        ui->QCBPropiedades->addItem(QString::fromStdString("Relacion de Equivalencia"));
    }else {
        ui->QBOrdenar->setEnabled(false);
    }


}


void relacionesWindow::on_QBOrdenar_clicked(){
    diagrama->topologicSortWithAnimation(scene);
}



void relacionesWindow::focusToElementA(){
    ui->QLElementoA->setFocus();
}

void relacionesWindow::focusToElementB(){
    ui->QLElementoB->setFocus();
}

