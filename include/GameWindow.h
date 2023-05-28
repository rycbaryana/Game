#pragma once
#include <QMainWindow>
#include "View.h"
#include "Player.h"
#include "Model.h"
#include "Wave.h"
#include "UpgradeMenu.h"

class GameWindow : public QMainWindow {
    Q_OBJECT
public:
    const int maxEnemies = 300;
    GameWindow();
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void updateFrame();
    void setWave(const Wave& wave);
    void spawnEnemies();

    View* view;
    std::unique_ptr<Model> model;
    Wave currentWave;
    QTimer* spawnTimer;
    QTimer* gameTimer;
    QTimer* waveChangeTimer;
    UpgradeMenu* upgradeMenu;
public slots:
    void pause();
    void unpause();
    void startGame();
};
