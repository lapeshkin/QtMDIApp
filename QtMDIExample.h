#pragma once

#include <QtWidgets/QMainWindow>
#include <QMdiArea>
#include "ui_QtMDIExample.h"
#include <vld.h>

class QtMDIExample : public QMainWindow
{
    Q_OBJECT

public:
    QtMDIExample(QWidget *parent = nullptr);
    ~QtMDIExample();

    QMdiArea* getMdiArea() const { return pMdiArea; };


signals:
    void messageRetranslated(const QString& strMessage);

public slots:
    void on_actionAddWindow_triggered();
    void on_actionCloseAll_triggered();

    // в этот слот будут приходить уведомления о том, что в окно с номером numSubWindow отправлено сообщение strMessage
    // слот должен найти нужное окно приконнектить к нему сигнал messageRetranslated, вызвать сигнал и отключить его
    void retranslateMessage(const int numSubWindow, const QString& strMessage);

private:
    Ui::QtMDIExampleClass ui;
//  мои переменные
    size_t      numSubWindows;
    QMdiArea*   pMdiArea;
};
