#pragma once

#include <QGraphicsView>
#include <QGraphicsItemGroup>


class MapGraphicView : public QGraphicsView
{
    Q_OBJECT

public:
    MapGraphicView(QWidget* parent);
    ~MapGraphicView();

private:
    /* Перегружаем событие изменения размера окна,
     * чтобы перехватывать его
     * */
    void resizeEvent(QResizeEvent* event);
    void draw();
    void deleteItemsFromGroup(QGraphicsItemGroup* group);

private:
    QGraphicsScene* scene;     
    QGraphicsItemGroup* group_1;   
    QGraphicsItemGroup* group_2;   
};

