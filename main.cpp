#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    //QStringList styles = QStyleFactory::keys();
    //QApplication::setStyle(QStyleFactory::create("Windows"));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
