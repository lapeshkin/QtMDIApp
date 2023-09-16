#include "RateChart.h"


#include "QPainter"
#include "QPaintEvent"
#include "QTMath"

//RateChart::RateChart(QWidget* parent) :
//    QGraphicsView(parent)
RateChart::RateChart(QWidget* parent) :
    QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    pRateMap = nullptr;

    mouse_x = mouse_y = 0;
    setMouseTracking(true);
};

void RateChart::setRateMap(RateMap* rateMap)
{
    if (pRateMap)
    {
        delete pRateMap;
        pRateMap = nullptr;
    }

    pRateMap = rateMap;
}

void RateChart::paintEvent(QPaintEvent* event)
{
    //QPainter painter(this);
    //painter.fillRect(event->rect(), Qt::black);

    QPixmap pixmap(size());
    QPainter painter;

    painter.begin(&pixmap);

    //drawSin(painter);
    drawChart(painter);

    painter.end();

    // Do processing on pixmap here

    painter.begin(this);
    painter.drawPixmap(0, 0, pixmap);
    painter.end();
}

void RateChart::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
}

void RateChart::mouseMoveEvent(QMouseEvent* event)
{
    mouse_x = event->x();
    mouse_y = event->y();
    //update();
    repaint();
}


void RateChart::draw(const QRect& rect)
{
    QPainter painter(this);
    painter.setOpacity(0);
    painter.fillRect(rect, Qt::black);
}

QSize RateChart::minimumSizeHint() const
{
    return QSize(100, 100);
}

//QSize RateChart::sizeHint() const
//{
//    //return minimumSizeHint();
//    return QSize(100, 100);
//}

void RateChart::drawSin(QPainter& painter)
{
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(10, height() - 10);

    QPen pen(Qt::darkGreen);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawLine(0, 0, width() - 20, 0);
    painter.drawLine(0, 0, 0, -height() + 20);

    QVector<QPointF> points(width());
    QPointF point;

    float kx = 2 * M_PI / width();
    float ky = height() / 2.f;

    for (int n = 0; n < width(); n++)
    {
        //painter.drawPoint(n, qSin(n * kx) * ky - (height() / 2.f));
        point.setX(n);
        point.setY(qSin(n * kx) * ky - (height() / 2.f));
        points.push_back(point);
    }

    painter.drawLines(points);

}

void RateChart::drawChart(QPainter& painter)
{
    const int margin_left = 10;
    const int margin_right = 10;
    const int margin_top = 10;
    const int margin_bottom = 10;
    const int padding_left = 0;
    const int padding_right = 0;
    const int padding_top = 0;
    const int padding_bottom = 0;

    int available_width = width() - (margin_left + margin_right + padding_left + padding_right);
    int available_height = height() - (margin_top + margin_bottom + padding_top + padding_bottom);
    int height_0 = height() - margin_bottom;

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(margin_left, height() - margin_top);

    QPen pen(Qt::darkGreen);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawLine(0, 0, width() - (margin_left + margin_right), 0);
    painter.drawLine(0, 0, 0, -height() + margin_top + margin_bottom);

    if (!pRateMap) return;

    int numDays = pRateMap->getNumDays();
    if (!numDays) return;

    qreal ratesDifference = pRateMap->getMax() - pRateMap->getMin();
    if (!ratesDifference) return;

    pen.setWidth(3);

    qreal kDays = available_width / (qreal)numDays;
    qreal kRates = available_height / ratesDifference;

    QVector<QPointF> points(width());
    QPointF point;
    bool    bFirstPoint = true;

    qreal lastValue = pRateMap->getRate(pRateMap->getFirstDate());
    qreal minValue  = pRateMap->getMin();

    QDate day = pRateMap->getFirstDate();
    while (day <= pRateMap->getLastDate())
    {
        int nDay = pRateMap->getFirstDate().daysTo(day);

        qreal val = pRateMap->getRate(day);
        if (!val)
            val = lastValue;

        float posX = nDay * kDays;
        float posY = -(val - minValue) * kRates;

        point.setX(posX);
        point.setY(posY);
        points.push_back(point);

        if (!bFirstPoint)
            points.push_back(point);

        bFirstPoint = false;
        lastValue = val;
        day = day.addDays(1);
    }

    painter.drawLines(points);

    // draw  horizontal and vertical mouse lines
    if (mouse_x && mouse_y)
    {
        pen.setColor(Qt::red);
        pen.setWidth(2);
        painter.setPen(pen);

        float  posX = mouse_x - margin_left;
        float  posY = -height() + margin_top + mouse_y;
        //painter.drawLine(0, posY, width() - margin_left - margin_right, posY); // horizontal
        painter.drawLine(posX, 0, posX, -height() + margin_top + margin_bottom); // vertical

        int nDays = round(posX / kDays);
        QDate xDay = pRateMap->getFirstDate().addDays(nDays);
        qreal val = pRateMap->getRate(xDay);
        posY = -(val - minValue) * kRates;
        painter.drawLine(0, posY, width() - margin_left - margin_right, posY); // horizontal

    }
}