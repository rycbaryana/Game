#include "GameWindow.h"
#include "SimpleEnemy.h"
#include <QGraphicsLineItem>
#include <QKeyEvent>
#include <QTimer>

GameWindow::GameWindow() : QMainWindow(), view(new View(this)), model(std::make_unique<Model>()) {
    setFocusPolicy(Qt::StrongFocus);
    resize(2 * size, 2 * size);

    view->scene->addItem(model->player);

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
    auto& projectiles = model->projectiles;
    auto& enemies = model->enemies;
    auto& weapons = model->player->getWeapons();
    for (auto* enemy : enemies) {
        if (!enemy->isAlive()) {
            std::erase_if(enemies, [enemy](auto obj) { return enemy == obj; });
            view->scene->removeItem(enemy);
        }
    }
    for (auto* projectile : projectiles) {
        if (vecLength(projectile->getPos() - model->player->getPos()) > sqrt(2) * size) {
            std::erase_if(projectiles, [projectile](auto obj) { return obj == projectile; });
            view->scene->removeItem(projectile);
            continue;
        }
        auto collidingEnemies = getCollision<Enemy>(projectile);
        if (!collidingEnemies.empty()) {
            auto* enemy = collidingEnemies.front();
            enemy->damage(projectile->getDamage());
            std::erase_if(projectiles, [projectile](auto obj) { return obj == projectile; });
            view->scene->removeItem(projectile);
        }
    }
    for (auto& weapon : weapons) {
        auto* projectile = weapon->activateWeapon(model->player->getPos(), enemies);
        if (projectile == nullptr)
            continue;
        projectiles.push_back(projectile);
        view->scene->addItem(projectile);
    }
    if (!model->player->isAlive()) {
        close();
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
