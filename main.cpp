#include "QtMDIExample.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtMDIExample w;
    w.show();
    return a.exec();
}
