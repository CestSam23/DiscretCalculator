#include "conjuntowindow.h"
#include "ui_conjuntowindow.h"
#include "conjunto.h"
#include <QPushButton>
#include <QLayout>
#include <QMessageBox>

conjuntoWindow::conjuntoWindow(Conjunto *conjunto, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::conjuntoWindow)
{
    this->conjunto=conjunto;
    posicionArrayElementos=0;
    ui->setupUi(this);
    connect(ui->QInputItem,&QLineEdit::returnPressed,this,&conjuntoWindow::on_QBaddItem_clicked);
    lay = new QVBoxLayout();
    for(int i=0;i<conjunto->getElementosValidos();i++){
        QPushButton *buton1 = new QPushButton(QString::fromStdString(conjunto->getElemento(i)));
        buton1->setStyleSheet("	background-color: #B27A62;color: white; border-radius: 3px;");
        lay->addWidget(buton1);
    }

    ui->scrollAreaWidgetContents->setLayout(lay);


}

conjuntoWindow::~conjuntoWindow()
{
    delete ui;
}

void conjuntoWindow::on_QBaddItem_clicked()
{
    std::string lectura = ui->QInputItem->text().toStdString();
    if(lectura!=""){
        arrayElementos[posicionArrayElementos]=lectura;
        posicionArrayElementos++;
        QPushButton *elemento = new QPushButton(QString::fromStdString(lectura));
        elemento->setStyleSheet("	background-color: #B27A62;color: white; border-radius: 3px;");
        lay->addWidget(elemento);
        ui->QInputItem->setText("");
    }
}


void conjuntoWindow::on_QBendList_clicked()
{
    int seed=conjunto->getElementosValidos();
    for(int i=0;i<posicionArrayElementos;i++){
        conjunto->setElementos(i+seed,arrayElementos[i]);

    }
    conjunto->validarConjunto();
    QMessageBox::information(this,"Status","Items added correctly");
    close();
}

void conjuntoWindow::closeEvent(QCloseEvent *event)
{
    // Esta función se ejecutará al cerrar la ventana
    // Puedes realizar acciones específicas aquí antes de que la ventana se cierre

    // Por ejemplo, puedes emitir la señal destruida para activar la conexión en la ventana principal
    emit destroyed();

    // Llama a la función base para permitir el cierre
    QMainWindow::closeEvent(event);
}

