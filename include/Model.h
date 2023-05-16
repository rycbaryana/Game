#pragma once
#include "Player.h"
#include <QDeadlineTimer>
#include "Wave.h"

class Model {
public:
    Model();
    Player* player;
    std::vector<Enemy*> enemies;
    std::vector<Projectile*> projectiles;
    std::vector<Wave> waves;
    std::map<int, std::vector<double>> enemiesTable;
    int width;
    int height;
    void updateModel();
    void loadWaves();
    void loadEnemies();
    void itemPickUp(Item* item);
    Enemy* newEnemy(int id, const QPointF& pos);
};