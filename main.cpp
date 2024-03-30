#include "mainwindow.h"
#include "muParser.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(700, 600);
    w.setWindowTitle("Integral Estimator");
    w.show();
    return a.exec();
}
