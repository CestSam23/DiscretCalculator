#include "principalwindow.h"
#include "./ui_principalwindow.h"
#include "conjuntowindow.h"
#include "relacioneswindow.h"
#include "graphmenu.h"
#include <QLayout>
#include <QPushButton>
#include <QLayoutItem>

principalWindow::principalWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::principalWindow)
{
    Conjunto conjuntoA;
    Conjunto conjuntoB;
    Conjunto conjuntoC;

    Ai=Aj=Bi=Bj=Ci=Cj=0;
    ui->setupUi(this);

    wA = new QWidget;
    wB = new QWidget;
    wC = new QWidget;

    layA = new QGridLayout(wA);
    layB = new QGridLayout(wB);
    layC = new QGridLayout(wC);

    wA->setStyleSheet("background-color:#AEB4A6;");
    wB->setStyleSheet("background-color:#AEB4A6;");
    wC->setStyleSheet("background-color:#AEB4A6;");

    ui->scrollArea_A->setWidget(wA);
    ui->scrollArea_B->setWidget(wB);
    ui->scrollArea_C->setWidget(wC);
}

principalWindow::~principalWindow()
{
    delete ui;
}

void principalWindow::on_QBModifyA_clicked(){
    ventanaConjunto  = new conjuntoWindow(&conjuntoA, this);
    connect(ventanaConjunto,&conjuntoWindow::destroyed,this,&principalWindow::atClose);
    ventanaConjunto->show();

}

void principalWindow::on_modifyB_clicked(){
    ventanaConjunto = new conjuntoWindow(&conjuntoB, this);
    connect(ventanaConjunto,&conjuntoWindow::destroyed,this,&principalWindow::atClose);
    ventanaConjunto->show();


}

void principalWindow::atClose(){
   Ai=Aj=Bi=Bj=0;

    for(int i=0;i<conjuntoA.getElementosValidos();i++){
        QPushButton *boton1 = new QPushButton(QString::fromStdString(conjuntoA.getElemento(i)));
        boton1->setStyleSheet("	background-color: #B27A62;color: white; border-radius: 3px;");
        if(i%4==0){
            Ai=0;
            Aj++;
        } else {
            Ai++;
        }
        layA->addWidget(boton1,Aj,Ai);


    }
    for(int i=0;i<conjuntoB.getElementosValidos();i++){
         QPushButton *boton2 = new QPushButton(QString::fromStdString(conjuntoB.getElemento(i)));
        boton2->setStyleSheet("	background-color: #B27A62;color: white; border-radius: 3px;");
        if(i%4==0){
            Bi=0;
            Bj++;
        } else {
            Bi++;
        }
        layB->addWidget(boton2,Bj,Bi);
    }

}



void principalWindow::on_QBCalcular_clicked()
{
    Conjunto conjuntoC;
    QLayoutItem *item;
    while((item = layC->takeAt(0))){
        delete item->widget();
        delete item;
    }
    Ci=Cj=0;
    int aPart = ui->CbAPart->currentIndex();
    int bPart = ui->CbBPart->currentIndex();
    int operationPart = ui->CbOperationPart->currentIndex();

    switch(operationPart){
        case 0: //Union
            if(aPart==0 && bPart==0){           //A y A
                conjuntoC = conjuntoA.unionC(conjuntoA);
            } else if(aPart==0 && bPart==1){    //A y B
                conjuntoC = conjuntoA.unionC(conjuntoB);
            } else if(aPart==1 && bPart==0){    //B y A
                conjuntoC = conjuntoB.unionC(conjuntoA);
            } else if(aPart==1 && bPart==1){    //B y B
                conjuntoC = conjuntoB.unionC(conjuntoB);
            }
            break;
        case 1: //Interseccion
            if(aPart==0 && bPart==0){           //A y A
                conjuntoC = conjuntoA.interseccion(conjuntoA);
            } else if(aPart==0 && bPart==1){    //A y B
                conjuntoC = conjuntoA.interseccion(conjuntoB);
            } else if(aPart==1 && bPart==0){    //B y A
                conjuntoC = conjuntoB.interseccion(conjuntoA);
            } else if(aPart==1 && bPart==1){    //B y B
                conjuntoC = conjuntoB.interseccion(conjuntoB);
            }
            break;
        case 2: //Producto Cruz
            if(aPart==0 && bPart==0){           //A y A
                productoCruzTemporal(conjuntoA,conjuntoA);
            } else if(aPart==0 && bPart==1){    //A y B
                productoCruzTemporal(conjuntoA,conjuntoB);
            } else if(aPart==1 && bPart==0){    //B y A
                productoCruzTemporal(conjuntoB,conjuntoA);
            } else if(aPart==1 && bPart==1){    //B y B
                productoCruzTemporal(conjuntoB,conjuntoB);
            }
            break;
        case 3: //Diferencia
            if(aPart==0 && bPart==0){           //A y A
                conjuntoC = conjuntoA.diferencia(conjuntoA);
            } else if(aPart==0 && bPart==1){    //A y B
                conjuntoC = conjuntoA.diferencia(conjuntoB);
            } else if(aPart==1 && bPart==0){    //B y A
                conjuntoC = conjuntoB.diferencia(conjuntoA);
            } else if(aPart==1 && bPart==1){    //B y B
                conjuntoC = conjuntoB.diferencia(conjuntoB);
            }
            break;
        case 4: //Relaciones
            if(aPart==0){           //A y A
                ventanaRelaciones = new relacionesWindow(&conjuntoA);
                ventanaRelaciones->show();
            } else if(aPart==1){    //B y B
                ventanaRelaciones = new relacionesWindow(&conjuntoB);
                ventanaRelaciones->show();
            }
            break;
        default:
            break;

    }
    if(operationPart!=2){
        for(int i=0;i<conjuntoC.getElementosValidos();i++){
            QPushButton *boton1 = new QPushButton(QString::fromStdString(conjuntoC.getElemento(i)));
            boton1->setStyleSheet("	background-color: #B27A62;color: white; border-radius: 3px;");
            if(i%3==0){
                Ci=0;
                Cj++;
            } else {
                Ci++;
            }
            layC->addWidget(boton1,Cj,Ci);
        }
    }
}


void principalWindow::on_CbOperationPart_currentIndexChanged(int index)
{
    if(index==4){
        ui->CbBPart->setDisabled(true);
        ui->CbBPart->setStyleSheet("text-decoration: line-through; font: 290 9pt \"Microsoft YaHei UI\";}");
    } else {
        ui->CbBPart->setDisabled(false);
        ui->CbBPart->setStyleSheet("	color: black;font: 700 9pt \"Microsoft YaHei UI\";");
    }
}

void principalWindow::productoCruzTemporal(Conjunto conjuntoA, Conjunto conjuntoB){
    //Asegurarse que no hay elementos repetidos
    conjuntoA.validarConjunto(); conjuntoB.validarConjunto();
    int Ci=0, Cj=0,k=0;
    for(int i=0; i<conjuntoA.getElementosValidos();i++){
        for(int j=0; j<conjuntoB.getElementosValidos();j++){
            QPushButton *boton1 = new QPushButton(QString::fromStdString("("+conjuntoA.getElemento(i)+","+conjuntoB.getElemento(j)+")"));
            boton1->setStyleSheet("	background-color: #B27A62;color: white; border-radius: 3px;");
            if(k%3==0){
                Ci=0;
                Cj++;
            } else {
                Ci++;
            }
            layC->addWidget(boton1,Cj,Ci);
            k++;
        }

    }
}


void principalWindow::on_pushButton_clicked(){
    ventanaGrafos = new GraphMenu();
    ventanaGrafos->show();
}

