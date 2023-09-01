#include "MapGraphicView.h"

MapGraphicView::MapGraphicView(QWidget* parent)
    : QGraphicsView(parent)
{

    /* Немного поднастроим отображение виджета и его содержимого */
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключим скроллбар по горизонтали
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключим скроллбар по вертикали
    this->setAlignment(Qt::AlignCenter);                        // Делаем привязку содержимого к центру
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    // Растягиваем содержимое по виджету

    /* Также зададим минимальные размеры виджета
     * */
    this->setMinimumHeight(100);
    this->setMinimumWidth(100);

    scene = new QGraphicsScene();   // Инициализируем сцену для отрисовки
    this->setScene(scene);          // Устанавливаем сцену в виджет

    group_1 = new QGraphicsItemGroup(); // Инициализируем первую группу элементов
    group_2 = new QGraphicsItemGroup(); // Инициализируем вторую группу элементов

    scene->addItem(group_1);            // Добавляем первую группу в сцену
    scene->addItem(group_2);            // Добавляем вторую группу в сцену

    //timer = new QTimer();               // Инициализируем Таймер
    //timer->setSingleShot(true);
    //// Подключаем СЛОТ для отрисовки к таймеру
    //connect(timer, SIGNAL(timeout()), this, SLOT(slotAlarmTimer()));
    //timer->start(50);                   // Стартуем таймер на 50 миллисекунд
}

MapGraphicView::~MapGraphicView()
{
    if (scene)
    {
        // сцена сама удалит все включенные в неё элементы
        delete scene;
        scene = nullptr;
    }
}

void MapGraphicView::resizeEvent(QResizeEvent* event)
{
    //timer->start(50);   // Как только событие произошло стартуем таймер для отрисовки
    draw();
    QGraphicsView::resizeEvent(event);  // Запускаем событие родителького класса
}

void MapGraphicView::deleteItemsFromGroup(QGraphicsItemGroup* group)
{
    /* Перебираем все элементы сцены, и если они принадлежат группе,
     * переданной в метод, то удаляем их
     * */
    foreach(QGraphicsItem * item, scene->items(group->boundingRect())) {
        if (item->group() == group) {
            delete item;
        }
    }
}

void MapGraphicView::draw()
{
    /* Удаляем все элементы со сцены,
     * если они есть перед новой отрисовкой
     * */
    deleteItemsFromGroup(group_1);
    deleteItemsFromGroup(group_2);

    int width = this->width();      // определяем ширину нашего виджета
    int height = this->height();    // определяем высоту нашего виджета

    /* Устанавливаем размер сцены по размеру виджета
     * Первая координата - это левый верхний угол,
     * а Вторая - это правый нижний угол
     * */
    scene->setSceneRect(0, 0, width, height);

    /* Приступаем к отрисовке произвольной картинки
     * */
    QPen penBlack(Qt::black); // Задаём чёрную кисть
    QPen penRed(Qt::red);   // Задаём красную кисть

    /* Нарисуем черный прямоугольник
     * */
    group_1->addToGroup(scene->addLine(20, 20, width - 20, 20, penBlack));
    group_1->addToGroup(scene->addLine(width - 20, 20, width - 20, height - 20, penBlack));
    group_1->addToGroup(scene->addLine(width - 20, height - 20, 20, height - 20, penBlack));
    group_1->addToGroup(scene->addLine(20, height - 20, 20, 20, penBlack));

    /* Нарисуем красный квадрат
     * */
    int sideOfSquare = (height > width) ? (width - 60) : (height - 60);
    int centerOfWidget_X = width / 2;
    int centerOfWidget_Y = height / 2;

    group_2->addToGroup(scene->addLine(centerOfWidget_X - (sideOfSquare / 2),
        centerOfWidget_Y - (sideOfSquare / 2),
        centerOfWidget_X + (sideOfSquare / 2),
        centerOfWidget_Y - (sideOfSquare / 2),
        penRed));

    group_2->addToGroup(scene->addLine(centerOfWidget_X + (sideOfSquare / 2),
        centerOfWidget_Y - (sideOfSquare / 2),
        centerOfWidget_X + (sideOfSquare / 2),
        centerOfWidget_Y + (sideOfSquare / 2),
        penRed));

    group_2->addToGroup(scene->addLine(centerOfWidget_X + (sideOfSquare / 2),
        centerOfWidget_Y + (sideOfSquare / 2),
        centerOfWidget_X - (sideOfSquare / 2),
        centerOfWidget_Y + (sideOfSquare / 2),
        penRed));

    group_2->addToGroup(scene->addLine(centerOfWidget_X - (sideOfSquare / 2),
        centerOfWidget_Y + (sideOfSquare / 2),
        centerOfWidget_X - (sideOfSquare / 2),
        centerOfWidget_Y - (sideOfSquare / 2),
        penRed));
}