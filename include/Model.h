#pragma once
#include "Player.h"
#include <SimpleEnemy.h>
#include <QDeadlineTimer>

class Model {
public:
    Model();
    Player* player;
    std::vector<Enemy*> enemies;
    std::vector<Projectile*> projectiles;

    void updateModel();
    void itemPickUp(Item* item);
};