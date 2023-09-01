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
    // ����������� ����������
    pMdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    pMdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // ������������� Mdi Area � �������� ������������ �������
    setCentralWidget(pMdiArea);
}

QtMDIExample::~QtMDIExample()
{
}

void QtMDIExample::on_actionAddWindow_triggered()
{
    MapSubWindow* widget = new MapSubWindow(this);
    widget->setWindowNumber(++numSubWindows);
    // ��������� ������ � �������� ������� � Mdi Area
    pMdiArea->addSubWindow(widget);
    // � ���������� ������
    widget->show();
}

void QtMDIExample::on_actionCloseAll_triggered()
{
    for (auto sw : pMdiArea->subWindowList())
    {
        sw->close();
    }
}

// � ���� ���� ����� ��������� ����������� � ���, ��� � ���� � ������� numSubWindow ���������� ��������� strMessage
// ���� ������ ����� ������ ���� ������������� � ���� ������ messageRetranslated, ������� ������ � ��������� ���
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
