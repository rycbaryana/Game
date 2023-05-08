#include "Model.h"

Model::Model() : player(new Player) {
}

void Model::updateModel() {
    player->move();

    auto collision = getCollision<Enemy>(player);
    for (auto* e : collision) {
        double dist = vecLength(player->getPos() - e->getPos());
        double minDist = (player->boundingRect().width() + e->boundingRect().width()) / 2;
        e->move(qMax(1.0, qPow(minDist / dist, player->boundingRect().width() / e->boundingRect().width())) * e->getSpeed(), -e->getDirection());
        e->attack(player);
    }
    for (auto* enemy : enemies) {
        auto vec = player->getPos() - enemy->getPos();
        enemy->setDirection(vec);
        enemy->move();
        auto collidingEnemies = getCollision<Enemy>(enemy);
        for (auto* e : collidingEnemies) {
            auto dir = enemy->getPos() - e->getPos();
            double dist = vecLength(dir);
            double minDist = (enemy->boundingRect().width() + e->boundingRect().width()) / 2;
            e->move(qMax(1.0, qPow(minDist / dist, 1)) * e->getSpeed(), -dir);
        }


    }
    for (auto* projectile : projectiles) {
        projectile->move();
    }
}
