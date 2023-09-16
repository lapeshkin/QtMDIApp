#include <QGridLayout>
#include <QLabel>
#include <QMdiSubWindow>

#include "QtMDIExample.h"
#include "MapSubWindow.h"

QtMDIExample::QtMDIExample(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    numSubWindows = 0;

    pMdiArea = new QMdiArea(this);

    pMdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    pMdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // Устанавливаю Mdi Area в качестве центрального виджета
    setCentralWidget(pMdiArea);
}

QtMDIExample::~QtMDIExample()
{
}

void QtMDIExample::on_actionAddWindow_triggered()
{
    MapSubWindow* widget = new MapSubWindow(this);

    pMdiArea->addSubWindow(widget);

    widget->show();
}

void QtMDIExample::on_actionCloseAll_triggered()
{
    for (auto sw : pMdiArea->subWindowList())
    {
        sw->close();
    }
}

