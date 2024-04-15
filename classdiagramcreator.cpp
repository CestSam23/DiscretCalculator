#include "classdiagramcreator.h"
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <iostream>

ClassDiagramCreator::ClassDiagramCreator(QGraphicsView *canva,Relacion relacion, Matriz matriz) :
matrix(matriz),relacion(relacion), uniqueMatrix(matriz){

    this->matrix = matriz;
    this->relacion = relacion;
    this->canva = canva;

    numberOfGroups= getDifferentRows();
    elementsPerRow = new int[numberOfGroups];
    rowPositions = new int[numberOfGroups];
}


int ClassDiagramCreator::getDifferentRows(){
    int differentRows=0;
    bool equalRows = false;
    for(int i=0;i<matrix.getCardinalidad();i++){
        for(int j=0;j<matrix.getCardinalidad();j++){
            if(matrix.getValor(i,j)){
                equalRows = false;

                for(int compareRow=i+1;compareRow<matrix.getCardinalidad();compareRow++){
                    if(matrix.getValor(compareRow,j)){
                        equalRows = true;
                        break;
                    }
                }
                if(!equalRows) differentRows++;
                break;
            }
        }
    }

    return differentRows;
}

void ClassDiagramCreator::deleteEqualRows(){

    for(int i=0;i<uniqueMatrix.getCardinalidad();i++){
        for(int j=0;j<uniqueMatrix.getCardinalidad();j++){
            if(uniqueMatrix.getValor(i,j)){
                for(int compareRow=i+1;compareRow<uniqueMatrix.getCardinalidad();compareRow++){
                    if(uniqueMatrix.getValor(compareRow,j)){
                        for(int compareColumn=0;compareColumn<uniqueMatrix.getCardinalidad();compareColumn++){
                            uniqueMatrix.setValor(compareRow,compareColumn,false);
                        }
                    }
                }
                break;
            }
        }
    }
}

void ClassDiagramCreator::updateElements(){
    int positionOfElements=0;
    deleteEqualRows();
    for(int i=0;i<uniqueMatrix.getCardinalidad();i++){
        for(int j=0;j<uniqueMatrix.getCardinalidad();j++){
            if(uniqueMatrix.getValor(i,j)){
                elementsPerRow[positionOfElements]=1;
                rowPositions[positionOfElements]=i;
                for(int k=j+1;k<uniqueMatrix.getCardinalidad();k++){
                    if(uniqueMatrix.getValor(i,k)) elementsPerRow[positionOfElements]++;
                }
                positionOfElements++;
                break;
            }
        }
    }
}

void ClassDiagramCreator::createClassDiagram(QGraphicsScene *scene){
    updateElements();
    double particionesY = ((double)canva->height())/(numberOfGroups+1);
    double particionesX[numberOfGroups];
    QBrush brush(Qt::red); QPen pen(Qt::black);

    for(int i=0;i<numberOfGroups;i++) particionesX[i] = ((double)canva->width())/(elementsPerRow[i]+1);
    for(int i=0;i<numberOfGroups;i++){
        for(int j=0;j<elementsPerRow[i];j++){
            double toAddX = ((double)(j+1))*(particionesX[i]);
            double toAddY = ((double)(i+1))*(particionesY);
            QGraphicsEllipseItem *nodos = scene->addEllipse(0,0,10,10,pen,brush);
            nodos->setPos(QPointF(toAddX,toAddY));

        }
        int validValue=0;
        for(int j=0;j<elementsPerRow[i];j++){
            double toAddX = ((double)(j+1))*(particionesX[i]);
            double toAddY = ((double)(i+1))*(particionesY);
            for(validValue=validValue;validValue<uniqueMatrix.getCardinalidad();validValue++){
                if(uniqueMatrix.getValor(rowPositions[i],validValue)){
                    std::string sEtiqueta = relacion.getConjunto().getElemento(validValue);
                    QGraphicsTextItem *etiqueta = scene->addText(QString::fromStdString(sEtiqueta));
                    etiqueta->setPos(toAddX,toAddY-25);
                    validValue++;
                    break;
                }

            }

        }
        double toAddY = ((double(i+1))*particionesY);
        QPointF pointA(0,toAddY+15);
        QPointF pointB(canva->width(),toAddY+15);
        QGraphicsLineItem *connection = new QGraphicsLineItem(pointA.x(),pointA.y(),pointB.x(),pointB.y());
        scene->addItem(connection);


    }

}

