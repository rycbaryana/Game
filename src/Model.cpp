#include "Model.h"

Model::Model() : player(new Player) { }

void Model::updateModel() {
    player->move();
    player->setPos(player->getPos());
    for (auto enemy : enemies) {
        auto vec = player->getPos() - enemy->getPos();
        enemy->setDirection({vec.x(), vec.y()});
        enemy->move();
        enemy->setPos(enemy->getPos());
    }
}

