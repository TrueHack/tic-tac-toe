#include <QtGui/QApplication>
#include "mainwindow.h"
#include "map.h"


int MapSize = 3;
std::vector<std::vector<Cell*> > cells;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
