#include "View.h"
#include <QWheelEvent>

void View::wheelEvent(QWheelEvent* event) {
    event->accept();
}

View::View(QWidget* parent) : QGraphicsView(parent) {
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setDragMode(QGraphicsView::NoDrag);
    setFrameShape(QGraphicsView::NoFrame);
    scale(1, -1);
    const int maxSize = 10000;
    scene = new QGraphicsScene(-maxSize, -maxSize, 2 * maxSize, 2 * maxSize, this);
    scene->addLine(-maxSize, 0, maxSize, 0, {Qt::red});
    scene->addLine(0, -maxSize, 0, maxSize,{Qt::red});
    setScene(scene);
}
