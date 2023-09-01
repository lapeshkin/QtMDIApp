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
    // Настраиваем скроллбары
    pMdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    pMdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // Устанавливаем Mdi Area в качестве центрального виджета
    setCentralWidget(pMdiArea);
}

QtMDIExample::~QtMDIExample()
{
}

void QtMDIExample::on_actionAddWindow_triggered()
{
    MapSubWindow* widget = new MapSubWindow(this);
    widget->setWindowNumber(++numSubWindows);
    // Добавляем виджет в качестве подокна в Mdi Area
    pMdiArea->addSubWindow(widget);
    // и показываем виджет
    widget->show();
}

void QtMDIExample::on_actionCloseAll_triggered()
{
    for (auto sw : pMdiArea->subWindowList())
    {
        sw->close();
    }
}

// в этот слот будут приходить уведомления о том, что в окно с номером numSubWindow отправлено сообщение strMessage
// слот должен найти нужное окно приконнектить к нему сигнал messageRetranslated, вызвать сигнал и отключить его
void QtMDIExample::retranslateMessage(const int numSubWindow, const QString& strMessage)
{
    MapSubWindow* pSubWindow = nullptr;

    for (QMdiSubWindow* s : pMdiArea->subWindowList())
    {
        MapSubWindow* p = qobject_cast<MapSubWindow*>(s->widget());
        if (p->getWindowNumber() == numSubWindow)
        {
            pSubWindow = p;
            break;
        }
    }

    if (!pSubWindow)
        return;

    QMetaObject::Connection connection = QObject::connect(this, &QtMDIExample::messageRetranslated, pSubWindow, &MapSubWindow::onMessageReceived);
    emit messageRetranslated(strMessage);
    QObject::disconnect(this, &QtMDIExample::messageRetranslated, pSubWindow, &MapSubWindow::onMessageReceived);

}
