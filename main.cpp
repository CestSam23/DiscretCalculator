#include "principalwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    principalWindow w;
    w.show();
    return a.exec();

}
