#include "View.h"
#include "MenuScene.h"
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
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    const int maxSize = 10000;
    auto* menu = new MenuScene(this);
    setScene(menu);
    scene = new QGraphicsScene(-maxSize, -maxSize, 2 * maxSize, 2 * maxSize, this);
    connect(menu, &MenuScene::start, [this] {
        scale(1, -1);
        setScene(scene);
        hud->show();
        emit gameStarted();
        QPixmap bg;
        bg.load(":/background.png");
        scene->setBackgroundBrush(QBrush(bg.scaled(bg.size() * 1.5).transformed(QTransform::fromScale(1, -1))));
    });
    connect(menu, &MenuScene::exit, [this] {
        exit(0);
    });
}
