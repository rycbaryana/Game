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
    setRenderHints(QPainter::Antialiasing| QPainter::SmoothPixmapTransform);
    setFocusPolicy(Qt::NoFocus);
    scale(1, -1);
    const int maxSize = 10000;
    scene = new QGraphicsScene(-maxSize, -maxSize, 2 * maxSize, 2 * maxSize, this);
    setScene(scene);
    QPixmap bg;
    bg.load(":/background.png");
    scene->setBackgroundBrush(QBrush(bg.scaled(bg.size() * 1.5).transformed(QTransform::fromScale(1, -1))));
}
