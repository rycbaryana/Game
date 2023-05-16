#include "GameWindow.h"
#include "PlayerHUD.h"
#include <QGraphicsLineItem>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QTimer>

GameWindow::GameWindow() : QMainWindow(), view(new View(this)), model(std::make_unique<Model>()) {
    setFocusPolicy(Qt::StrongFocus);
    resize(800, 800);

    view->scene->addItem(model->player);

    auto* hud = new PlayerHUD(model->player, this);
    view->hud = hud;

    upgradeMenu = new UpgradeMenu(model->player, hud->scene());
    connect(upgradeMenu, &UpgradeMenu::pause, this, &GameWindow::pause);
    connect(upgradeMenu, &UpgradeMenu::unpause, this, &GameWindow::unpause);

    gameTimer = new QTimer(this);
    gameTimer->setInterval(16);
    connect(gameTimer, &QTimer::timeout, [this]() {updateFrame(); });
    gameTimer->start();

    spawnTimer = new QTimer(this);
    connect(spawnTimer, &QTimer::timeout, [this]() {spawnEnemies(); });
    spawnTimer->start();

    setWave(model->waves.front());

    waveChangeTimer = new QTimer(this);
    waveChangeTimer->setInterval(60'000);
    connect(waveChangeTimer, &QTimer::timeout, [this]() {
        waveChangeTimer->setInterval(60'000);
        if (currentWave.id == model->waves.size() - 1) return;
        setWave(model->waves[currentWave.id + 1]);
    });
    waveChangeTimer->start();


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
    auto& enemies = model->enemies;
    for (auto& weapon : model->player->getWeapons()) {
        auto* projectile = weapon->activateWeapon(model->player->getPos(), model->enemies);
        if (projectile == nullptr)
            continue;
        model->projectiles.push_back(projectile);
        view->scene->addItem(projectile);
    }

    int level = model->player->getLevel();
    for (auto* item : getCollision<Item>(model->player)) {
        model->itemPickUp(item);
        delete item;
    }
    if (model->player->getLevel() != level) {
        upgradeMenu->showMenu();
    }

    view->centerOn(model->player);
    view->scene->update();
    update();
}

void GameWindow::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        auto* e = model->newEnemy(0, view->mapToScene(event->pos()));
        view->scene->addItem(e);
        model->enemies.push_back(e);
    }
}

void GameWindow::setWave(const Wave& wave) {
    currentWave = wave;
    spawnTimer->setInterval(currentWave.delay);
    view->hud->waveCounter->setPlainText(QString("Wave %1").arg(currentWave.id));
}

void GameWindow::spawnEnemies() {
    auto& enemies = model->enemies;
    if (enemies.size() > maxEnemies) return;
    double radius = sqrt(2) * width() / 2;
    int delta = currentWave.minAmount - enemies.size();
    int ids = currentWave.enemiesId.size();
    int toSpawn = std::max(1, (delta +  ids - 1) / ids);
    for (int i = 0; i < toSpawn; ++i) {
        for (auto id : currentWave.enemiesId) {
            double angle = QRandomGenerator::global()->generateDouble() * 2 * M_PI;
            QPointF pos = {model->player->getPos() + QPointF(radius * cos(angle), radius * sin(angle))};
            auto* enemy = model->newEnemy(id, pos);
            view->scene->addItem(enemy);
            enemies.push_back(enemy);
        }
    }
}

void GameWindow::pause() {
    gameTimer->stop();
    spawnTimer->stop();
    waveChangeTimer->setInterval(waveChangeTimer->remainingTime());
    waveChangeTimer->stop();
}

void GameWindow::unpause() {
    gameTimer->start();
    spawnTimer->start();
    waveChangeTimer->start();
}

void GameWindow::resizeEvent(QResizeEvent* event) {
    view->hud->resize(size());
    view->hud->scene()->setSceneRect(0, 0, width(), height());
    view->hud->xp->setWidth(width());
    upgradeMenu->setPos(width() / 2, height() / 2);
    model->width = width();
    model->height = height();
}
