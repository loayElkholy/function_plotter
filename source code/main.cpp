#include "function_plotter.h"

#include <QApplication>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    function_plotter w;
    w.show();
    return a.exec();
}
