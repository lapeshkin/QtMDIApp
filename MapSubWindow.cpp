#include <QGridLayout>
#include <QLabel>
#include "MapSubWindow.h" 

MapSubWindow::MapSubWindow(QtMDIExample* pParent) :
	QWidget(pParent->getMdiArea())
{
    ui.setupUi(this);

    setProperty("numSubWindow", 0);
    numSubWindow = 0;

    mapView = new MapGraphicView(this);
    ui.mapLayout->addWidget(mapView);

    // Устанавливаю заголовок окна
    this->setWindowTitle("Sub Window");

    QtMDIExample* p = qobject_cast<QtMDIExample*>(pParent);

   
    QObject::connect(this, &MapSubWindow::messageSent, qobject_cast<QtMDIExample*>(pParent), &QtMDIExample::retranslateMessage);

}

MapSubWindow::~MapSubWindow()
{
}

void MapSubWindow::setWindowNumber(size_t num)
{
    numSubWindow = num;
    ui.labelSubWindowNumber->setText(QString::number(numSubWindow));

}

void MapSubWindow::onMessageReceived(const QString& strMessage)
{
    ui.labelMessageText->setText(strMessage);
}

void MapSubWindow::on_sendButton_clicked()
{
    qInfo("on_actionSendMessage_triggered");
    qDebug("on_actionSendMessage_triggered");

    emit messageSent(ui.lineWindowNumber->text().toInt(), ui.lineMessageText->text());

}

