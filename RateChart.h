#pragma once

#include <QGraphicsView>
#include <QWidget>
#include <QDate>

#include "RateMap.h"

//class RateChart : public QGraphicsView
class RateChart : public QWidget
{
    Q_OBJECT

public:
    RateChart(QWidget* parent);
    ~RateChart() {};

    QSize   minimumSizeHint() const override;
    //QSize   sizeHint() const override;
    void    draw(const QRect& rect);

    void setRateMap(RateMap* rateMap);

protected:
    void	paintEvent(QPaintEvent* event) override;
    void	resizeEvent(QResizeEvent* event) override;
    void    mouseMoveEvent(QMouseEvent* event) override;

private:
    void drawSin(QPainter& painter);    // draw sine wave
    void drawChart(QPainter& painter);  // draw currency rates chart
private:
    RateMap* pRateMap;

    int mouse_x;
    int mouse_y;
};

