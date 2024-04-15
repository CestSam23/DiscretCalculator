#include "hassdiagramcreator.h"
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QPropertyAnimation>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <iostream>
#include "matriz.h"

HassDiagramCreator::HassDiagramCreator(QGraphicsView *canva, Relacion relacion, Matriz matriz) : matriz(matriz), relacion(relacion), unsortedMatrix(matriz),originalRelation(relacion){
    this->matriz = matriz;
    this->relacion = relacion;
    this->canva = canva;
    this->originalRelation = relacion;
    unsortedMatrix = matriz;
    repeatedFrequency = new double[(int)matriz.getCardinalidad()];
    numberElements = matriz.getCardinalidad();
    HassDiagramCreator::updateFrequency();
    yPartitions = differentElements();
    xPartitions = new int[yPartitions];

}

Matriz HassDiagramCreator::buildConnectionMatrix(Matriz toBuild){
    Matriz builded = toBuild;

    for(int i=0;i<builded.getCardinalidad();i++){
        builded.setValor(i,i,false);
    }

    Matriz matrix2 = builded.multiplicacion(builded);

    builded = builded.diferencia(matrix2);

    return builded;
}

void HassDiagramCreator::updateFrequency(){
    for(int i=0;i<numberElements;i++){
        repeatedFrequency[i]=0;
        for(int j=0;j<numberElements;j++){
            if(matriz.getValor(i,j)){
                repeatedFrequency[i]++;
            }
        }
    }
}

void HassDiagramCreator::sortFrequency(){
    int minimumPosition, minimum, temporal;
    std::string minimumString,temporalString;
    for(int comparing=0;comparing<numberElements-1;comparing++){
        minimumPosition=comparing;
        minimum=repeatedFrequency[comparing];
        minimumString=relacion.getConjunto().getElemento(comparing);
        for(int toCompare=comparing+1;toCompare<numberElements;toCompare++){
            if(minimum>repeatedFrequency[toCompare]){
                minimum=repeatedFrequency[toCompare];
                minimumString=relacion.getConjunto().getElemento(toCompare);
                minimumPosition = toCompare;
            }
        }
        temporal=repeatedFrequency[comparing];
        temporalString=relacion.getConjunto().getElemento(comparing);
        repeatedFrequency[comparing]=minimum;
        relacion.getRealConjunto()->setElemento(comparing,minimumString);
        repeatedFrequency[minimumPosition] = temporal;
        relacion.getRealConjunto()->setElemento(minimumPosition,temporalString);
    }
}

void HassDiagramCreator::updateXPartitions(){
    bool noEquals = true;
    int indexXPartitions = 0;

    for(int i=0;i<numberElements;i++){
        noEquals=true;

        for(int j=0;j<i;j++){
            if(repeatedFrequency[i]==repeatedFrequency[j]){
                noEquals=false;
            }
        }

        if(noEquals){
            xPartitions[indexXPartitions]=0;
            for(int k=0;k<numberElements;k++){
                if(repeatedFrequency[k]==repeatedFrequency[i]){
                    xPartitions[indexXPartitions]++;
                }
            }
            indexXPartitions++;
        }
    }
}

void HassDiagramCreator::createConnections(QGraphicsScene *Scene){
    Matriz connectionMatrix = HassDiagramCreator::buildConnectionMatrix(unsortedMatrix);
    for(int i=0;i<connectionMatrix.getCardinalidad();i++){
        for(int j=0;j<connectionMatrix.getCardinalidad();j++){
            if(connectionMatrix.getValor(i,j)){
                std::string elementoA = originalRelation.getConjunto().getElemento(i), elementoB=originalRelation.getConjunto().getElemento(j);
                int searcher=0; std::string searcherEtiqueta;
                while(searcher<etiquetas.size() && (searcherEtiqueta = etiquetas[searcher]->toPlainText().toStdString())!=elementoA){
                    searcher++;
                }
                QGraphicsEllipseItem *ellipseA, *ellipseB;
                if(searcher<ellipses.size()) ellipseA = ellipses[searcher];
                searcher=0;
                while(searcher<etiquetas.size() && (searcherEtiqueta=etiquetas[searcher]->toPlainText().toStdString())!=elementoB){
                    searcher++;
                }

                if(searcher<ellipses.size()) ellipseB = ellipses[searcher];

                //Coordenadas
                QPointF pointA = ellipseA->mapToScene(ellipseA->boundingRect().center());
                QPointF pointB = ellipseB->mapToScene(ellipseB->boundingRect().center());

                QGraphicsLineItem *connection = new QGraphicsLineItem(pointA.x(),pointA.y(),pointB.x(),pointB.y());
                connections.append(connection);
                Scene->addItem(connection);

            }
        }
    }
}

void HassDiagramCreator::createHassDiagram(QGraphicsScene *Scene){

    HassDiagramCreator::sortFrequency();
    HassDiagramCreator::updateXPartitions();

    double particionesY =((double)canva->height())/(yPartitions+1);
    double particionesX[yPartitions];
    QBrush brush(Qt::red); QPen pen(Qt::black);

    for(int i=0;i<yPartitions;i++) particionesX[i] = ((double)canva->width())/(xPartitions[i]+1);

    int indexItems=0;
    for(int i=0;i<yPartitions;i++){
        for(int j=0;j<xPartitions[i];j++){
            double toAddX = ((double)(j+1))*particionesX[i];
            double toAddY = ((double)(i+1))*particionesY;
            QGraphicsEllipseItem *nodos = Scene->addEllipse(0,0,10,10,pen,brush);
            QGraphicsTextItem *etiqueta = Scene->addText(QString::fromStdString(relacion.getConjunto().getElemento(indexItems)));
            indexItems++;
            etiqueta->setPos(toAddX,toAddY-25);
            nodos->setPos(QPointF(toAddX,toAddY));
            etiquetas.append(etiqueta) ;
            ellipses.append(nodos);
        }
    }


}

void HassDiagramCreator::topologicSort(QGraphicsScene *scene){
    double particionesY = ((double)canva->height())/(matriz.getCardinalidad()+1);
    double particionesX = canva->width()/2;

    for(int i=0;i<matriz.getCardinalidad();i++){
        QGraphicsEllipseItem *elipse = ellipses[i];
        QGraphicsTextItem *etiqueta = etiquetas[i];

        double toAddX = particionesX;
        double toAddY = ((double)(i+1))*particionesY;

        QPointF elipsePoint(toAddX,toAddY);
        QPointF etiquetaPoint(toAddX,toAddY-15);

        elipse->setPos(elipsePoint);
        etiqueta->setPos(etiquetaPoint);

    }
}

void HassDiagramCreator::topologicSortWithAnimation(QGraphicsScene *scene){
    int limit = connections.size();

    for(int i=0;i<limit;i++){
        QGraphicsLineItem *conection = connections[0];
        scene->removeItem(conection);
        connections.removeFirst();
    }

    double particionesY = ((double)canva->height())/(matriz.getCardinalidad()+1);
    double particionesX = canva->width()/2;

    QTimeLine *previousTimer = nullptr;

    for(int i=0;i<matriz.getCardinalidad();i++){
        QGraphicsEllipseItem *elipse = ellipses[i];
        QGraphicsTextItem *etiqueta = etiquetas[i];

        double toAddX = particionesX;
        double toAddY = ((double)(i+1))*particionesY;

        QPointF elipsePoint(toAddX,toAddY);
        QPointF etiquetaPoint(toAddX+15,toAddY-8);

        QTimeLine *timer = new QTimeLine(1000);
        timer->setFrameRange(0, 100);

        QGraphicsItemAnimation *animationElipse = new QGraphicsItemAnimation;
        animationElipse->setItem(elipse);
        animationElipse->setTimeLine(timer);
        animationElipse->setPosAt(1, elipsePoint);

        QGraphicsItemAnimation *animationEtiqueta = new QGraphicsItemAnimation;
        animationEtiqueta->setItem(etiqueta);
        animationEtiqueta->setTimeLine(timer);
        animationEtiqueta->setPosAt(1, etiquetaPoint);

        // Si hay un temporizador anterior, conecta su señal finished() a la ranura start() del temporizador actual
        if (previousTimer) {
            QObject::connect(previousTimer, &QTimeLine::finished, timer, &QTimeLine::start);
        } else {
            // Si no hay un temporizador anterior, este es el primer temporizador, así que lo iniciamos manualmente
            timer->start();
        }

        // El temporizador actual se convierte en el temporizador anterior para la próxima iteración
        previousTimer = timer;
    }
}





int HassDiagramCreator::differentElements(){
    int differentElements=1;
    bool Equals = false;

    if(numberElements==1) return 1;

    for(int comparing=1;comparing<numberElements;comparing++){
        Equals=false;
        for(int toCompare=0;toCompare<comparing;toCompare++){
            if(repeatedFrequency[comparing]==repeatedFrequency[toCompare]){
                Equals=true;
                break;
            }
        }
        if(!Equals){
            differentElements++;
        }
    }
    return differentElements;
}
