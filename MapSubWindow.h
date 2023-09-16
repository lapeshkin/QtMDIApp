#pragma once

#include <QWidget>
#include <QButtonGroup>
#include "ui_MapSubWindow.h"
#include "QtMDIExample.h" 
#include "MapGraphicView.h"
#include "RateMap.h"
#include "RateChart.h"


class MapSubWindow :
    public QWidget
{
    Q_OBJECT

public:
    MapSubWindow(QtMDIExample* pParent = nullptr);
    ~MapSubWindow();

    size_t  getWindowNumber() const { return numSubWindow; };

signals:
    void messageSent(const int numSubWindow, const QString& strMessage);

public slots:
    void on_loadButton_clicked();
    void on_selectFileButton_clicked();
    void on_radioButtonFromFile_toggled(bool bChecked);

private:
    Ui::MapSubWindow ui;

    size_t          numSubWindow;
    MapGraphicView* mapView;
    RateMap*        rateMap;
    RateChart*      rateChart;
    QButtonGroup    resourceButtonsGroup;

    QString     strFileResource;
    QString     strOnlineResource;
};

