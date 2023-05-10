#include "GameWindow.h"
#include "SimpleEnemy.h"
#include "PlayerHUD.h"
#include <QGraphicsLineItem>
#include <QKeyEvent>
#include <QTimer>

GameWindow::GameWindow() : QMainWindow(), view(new View(this)), model(std::make_unique<Model>()) {
    setFocusPolicy(Qt::StrongFocus);
    resize(2 * size, 2 * size);

    view->scene->addItem(model->player);
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    auto* hud = new PlayerHUD(model->player, view);
    view->hud = hud;

    auto* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this]() { updateFrame(); });
    timer->start(16);

    setCentralWidget(view);
}

void GameWindow::keyPressEvent(QKeyEvent* event) {
    auto key = event->key();
    auto [x, y] = model->player->getDirection();
    QMap<int, QPointF> keys = {
        {Qt::Key_W, {x, 1}}, {Qt::Key_S, {x, -1}}, {Qt::Key_D, {1, y}}, {Qt::Key_A, {-1, y}}};
    if (keys.contains(key)) {
        model->player->setDirection(keys[key]);
    }
}

void GameWindow::keyReleaseEvent(QKeyEvent* event) {
    auto key = event->key();
    auto [x, y] = model->player->getDirection();
    if (key == Qt::Key_W && y == 1 || key == Qt::Key_S && y == -1)
        y = 0;
    else if (key == Qt::Key_D && x == 1 || key == Qt::Key_A && x == -1)
        x = 0;
    else
        return;
    model->player->setDirection({x, y});
}

void GameWindow::updateFrame() {
    model->updateModel();

    for (auto& weapon : model->player->getWeapons()) {
        auto* projectile = weapon->activateWeapon(model->player->getPos(), model->enemies);
        if (projectile == nullptr)
            continue;
        model->projectiles.push_back(projectile);
        view->scene->addItem(projectile);
    }
    view->centerOn(model->player);
    view->scene->update();
    update();
}

void GameWindow::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        auto* e = new SimpleEnemy(view->mapToScene(event->pos()));
        view->scene->addItem(e);
        model->enemies.push_back(e);
    }
}