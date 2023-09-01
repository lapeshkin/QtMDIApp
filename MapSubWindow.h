#pragma once

#include <QWidget>
#include "ui_MapSubWindow.h"
#include "QtMDIExample.h" 
#include "MapGraphicView.h"


class MapSubWindow :
    public QWidget
{
    Q_OBJECT

public:
    MapSubWindow(QtMDIExample* pParent = nullptr);
    ~MapSubWindow();

    void    setWindowNumber(size_t num);
    size_t  getWindowNumber() const { return numSubWindow; };

signals:
    void messageSent(const int numSubWindow, const QString& strMessage);

public slots:
    void onMessageReceived(const QString& strMessage);
    void on_sendButton_clicked();

private:
    size_t numSubWindow;
    MapGraphicView* mapView;
    Ui::MapSubWindow ui;
};

