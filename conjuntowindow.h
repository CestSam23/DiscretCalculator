#ifndef CONJUNTOWINDOW_H
#define CONJUNTOWINDOW_H

#include <QMainWindow>
#include "conjunto.h"
#include <QVBoxLayout>
#include <QCloseEvent>
namespace Ui {
class conjuntoWindow;
}

class conjuntoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit conjuntoWindow(Conjunto *conjunto, QWidget *parent = nullptr);

    ~conjuntoWindow();


private slots:
        void on_QBendList_clicked();
    void on_QBaddItem_clicked();



private:
    int posicionArrayElementos;
    std::string arrayElementos[50];
    QVBoxLayout *lay;
    Conjunto *conjunto;
    Ui::conjuntoWindow *ui;
    void closeEvent(QCloseEvent *event);
};

#endif // CONJUNTOWINDOW_H
