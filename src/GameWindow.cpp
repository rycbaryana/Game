#include "GameWindow.h"
#include <QGraphicsLineItem>
#include <QKeyEvent>
#include <QTimer>

GameWindow::GameWindow() : QMainWindow(), view(new View(this)), model(std::make_unique<Model>()) {
    setFocusPolicy(Qt::StrongFocus);
    resize(800, 800);

    view->scene->addItem(&model->player);

    auto* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this]() { updateFrame(); });
    timer->start(16);

    setCentralWidget(view);
}

void GameWindow::keyPressEvent(QKeyEvent* event) {
    auto key = event->key();
    auto [x, y] = model->player.getDirection();
    QMap<int, QPointF> keys = {
        {Qt::Key_W, {x, 1}}, {Qt::Key_S, {x, -1}}, {Qt::Key_D, {1, y}}, {Qt::Key_A, {-1, y}}};
    if (keys.contains(key)) {
        model->player.setDirection(keys[key]);
    }
}

void GameWindow::keyReleaseEvent(QKeyEvent* event) {
    auto key = event->key();
    auto [x, y] = model->player.getDirection();
    if (key == Qt::Key_W && y == 1 || key == Qt::Key_S && y == -1)
        y = 0;
    else if (key == Qt::Key_D && x == 1 || key == Qt::Key_A && x == -1)
        x = 0;
    else
        return;
    model->player.setDirection({x, y});
}

void GameWindow::updateFrame() {
    model->player.move();
    model->player.setPos(model->player.getPos());
    view->centerOn(&model->player);
    view->scene->update();
    update();
}
