#pragma once
#include "Player.h"
#include <SimpleEnemy.h>
#include <QDeadlineTimer>

class Model {
public:
    Model();
    void updateModel();
    Player* player;
    std::vector<Enemy*> enemies;
    std::vector<Projectile*> projectiles;
};