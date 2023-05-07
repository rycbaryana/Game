#pragma once
#include "Player.h"
#include <SimpleEnemy.h>

class Model {
public:
    Model();
    void updateModel();
    template<class T>
    std::vector<T*> getCollision(QGraphicsItem*);
    Player* player;
    std::vector<Enemy*> enemies;
};

template<class T>
std::vector<T*> Model::getCollision(QGraphicsItem* whoCollide) {
    auto allCollisions = whoCollide->collidingItems();
    std::vector<T*> collision;
    for (auto item : allCollisions) {
        auto object = dynamic_cast<T*>(item);
        if (object != nullptr) {
            collision.push_back(object);
        }
    }
    return collision;
}