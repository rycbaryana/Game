#include "GameWindow.h"
#include "PlayerHUD.h"
#include <QGraphicsLineItem>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QTimer>
#include <QMediaPlayer>
#include "QSettings"
#include <QAudioOutput>

enum Keys {
    W = 17,
    A = 30,
    S = 31,
    D = 32,
    Up = 328,
    Left = 331,
    Down = 336,
    Right = 333,
    Esc = 1,
};

GameWindow::GameWindow() : QMainWindow(), view(new View(this)), model(std::make_unique<Model>()) {
    setFocusPolicy(Qt::StrongFocus);

    view->scene->addItem(model->player);
    connect(model->player, &AbstractPlayer::levelledUp, [this]{
        upgradeMenu->showMenu();
    });

    auto* hud = new PlayerHUD(model->player, this);
    view->hud = hud;
    hud->hide();

    upgradeMenu = new UpgradeMenu(model->player, hud->scene());
    connect(upgradeMenu, &UpgradeMenu::pause, this, &GameWindow::pause);
    connect(upgradeMenu, &UpgradeMenu::unpause, this, &GameWindow::unpause);

    gameTimer = new QTimer(this);
    gameTimer->setInterval(16);
    connect(gameTimer, &QTimer::timeout, [this]() {updateFrame(); });

    waveChangeTimer = new QTimer(this);
    waveChangeTimer->setInterval(60'000);
    connect(waveChangeTimer, &QTimer::timeout, [this]() {
        waveChangeTimer->setInterval(60'000);
        if (currentWave.id == model->waves.size() - 1) return;
        setWave(model->waves[currentWave.id + 1]);
    });

    spawnTimer = new QTimer(this);
    connect(spawnTimer, &QTimer::timeout, [this]() {spawnEnemies(); });
    setWave(model->waves.front());

    connect(view, &View::gameStarted, this, &GameWindow::startGame);
    setCentralWidget(view);
}

void GameWindow::keyPressEvent(QKeyEvent* event) {
    auto key = event->nativeScanCode();
    auto [x, y] = model->player->getDirection();
    QMap<int, QPointF> keys = {
        {Keys::W, {x, 1}}, {Keys::S, {x, -1}}, {Keys::D, {1, y}}, {Keys::A, {-1, y}}};
    if (keys.contains(key)) {
        model->player->setDirection(keys[key]);
    }
    if (key == Keys::Esc) {
        exit(0);
    }
}
    
void GameWindow::keyReleaseEvent(QKeyEvent* event) {
    auto key = event->nativeScanCode();
    auto [x, y] = model->player->getDirection();
    if (key == Keys::W && y == 1 || key == Keys::S && y == -1)
        y = 0;
    else if (key == Keys::D && x == 1 || key == Keys::A && x == -1)
        x = 0;
    else
        return;
    model->player->setDirection({x, y});
}

void GameWindow::updateFrame() {
    model->updateModel();
    for (auto& weapon : model->player->getWeapons()) {
        if (weapon->getLevel() == 0)
            continue ;
        auto* projectile = weapon->activateWeapon(model->enemies);
        if (projectile == nullptr)
            continue;
        model->projectiles.push_back(projectile);
        view->scene->addItem(projectile);
    }
    if (!model->player->isAlive()) exit(0);

    QPainterPath pickup;
    pickup.addEllipse(model->player->pos(), model->player->pickupRange, model->player->pickupRange);
    for (auto* object : view->scene->items(pickup)) {
        auto* item = dynamic_cast<Item*>(object);
        if (item == nullptr)
            continue ;
        model->itemPickUp(item);
        delete item;
    }

    view->centerOn(model->player);
    view->scene->update();
    update();
}

void GameWindow::setWave(const Wave& wave) {
    currentWave = wave;
    spawnTimer->setInterval(currentWave.delay);
    view->hud->waveCounter->setPlainText(QObject::tr("Wave %1").arg(currentWave.id));
}

void GameWindow::spawnEnemies() {
    auto& enemies = model->enemies;
    if (enemies.size() > maxEnemies) return;
    double a = sqrt(2) * width() / 2;
    double b = sqrt(2) * height() / 2;
    int delta = currentWave.minAmount - enemies.size();
    int ids = currentWave.enemiesId.size();
    if (ids == 0 ) return;
    int toSpawn = std::max(1, (delta +  ids - 1) / ids);
    for (int i = 0; i < toSpawn; ++i) {
        for (auto id : currentWave.enemiesId) {
            double angle = QRandomGenerator::global()->generateDouble() * 2 * M_PI;
            QPointF pos = {model->player->getPos() + QPointF(a * cos(angle), b * sin(angle))};
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
    if (!view->hud) return;
    view->hud->resize(size());
    view->hud->scene()->setSceneRect(0, 0, width(), height());
    view->hud->xp->setWidth(width());
    view->hud->killCounter->setPos(width() - 3 * view->hud->killCounter->boundingRect().width(), view->hud->xp->boundingRect().height());
    upgradeMenu->setPos(width() / 2, height() / 2);
    model->width = width();
    model->height = height();
}

void GameWindow::startGame() {
    gameTimer->start();
    spawnTimer->start();
    waveChangeTimer->start();

    QSettings settings;
    if (settings.value("sound", true).toBool()) {
        auto* player = new QMediaPlayer(this);
        player->setAudioOutput(new QAudioOutput(this));
        int ost = QRandomGenerator::global()->bounded(3);
        player->setSource(QUrl::fromLocalFile(QString("qrc:/ost%1.mp3").arg(ost)));
        player->setLoops(QMediaPlayer::Infinite);
        player->play();
    }
}
