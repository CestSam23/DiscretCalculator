#ifndef PRINCIPALWINDOW_H
#define PRINCIPALWINDOW_H

#include <QMainWindow>
#include "conjunto.h"
#include "conjuntowindow.h"
#include "relacioneswindow.h"
#include "matriz.h"
#include "relacion.h"
#include "graphmenu.h"
#include <QGridLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class principalWindow; }
QT_END_NAMESPACE

class principalWindow : public QMainWindow
{
    Q_OBJECT

public:
    principalWindow(QWidget *parent = nullptr);
    ~principalWindow();
    void atClose();

private slots:

    void on_modifyB_clicked();
    void on_QBModifyA_clicked();
    void on_QBCalcular_clicked();

    void on_CbOperationPart_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    void productoCruzTemporal(Conjunto conjuntoA, Conjunto conjuntoB);
    int Ai,Aj,Bi,Bj,Ci,Cj;
    QGridLayout *layA,*layB,*layC;
    QWidget *wA,*wB,*wC;
    Conjunto conjuntoA;
    Conjunto conjuntoB;
    Conjunto conjuntoC;
    conjuntoWindow *ventanaConjunto;
    relacionesWindow *ventanaRelaciones;
    GraphMenu *ventanaGrafos;

    Ui::principalWindow *ui;

};
#endif // PRINCIPALWINDOW_H
