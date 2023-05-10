#include "Model.h"
#include "GameWindow.h"

Model::Model() : player(new Player) {
}

void Model::updateModel() {
    player->move();
    for (auto* enemy : enemies) {
        auto vec = player->getPos() - enemy->getPos();
        double dst = vecLength(vec);
        double minDst = (player->boundingRect().width() + enemy->boundingRect().width()) / 2 + 5;
        enemy->setDirection(vec);
        enemy->move((minDst / dst >= 1 ? qMax(-5.0, -qPow((minDst / dst), 5)) : 1) * enemy->getSpeed(), vec);
        if (minDst / dst >= 1) enemy->attack(player);

        QSizeF size = enemy->boundingRect().size() + QSize(10, 10);
        QRectF searchRect = QRectF(enemy->getPos() - QPointF(size.width() / 2, size.height() / 2), size);
        auto enemiesNearby = enemy->scene()->items(searchRect);
        for (auto* object : enemiesNearby) {
            auto collidingEnemy = dynamic_cast<Enemy*>(object);
            if (collidingEnemy == nullptr)
                continue ;
            auto dir = enemy->getPos() - collidingEnemy->getPos();
            dst = vecLength(dir);
            minDst = (enemy->boundingRect().width() + collidingEnemy->boundingRect().width()) / 2 + 1;
            collidingEnemy->move(qMin(3.0, qPow(minDst / dst, 5)) * collidingEnemy->getSpeed(), -dir);
        }
    }
    for (auto*& projectile : projectiles) {
        projectile->move();
        if (vecLength(projectile->getPos() - player->getPos()) > sqrt(2) * GameWindow::size) {
            delete projectile;
            projectile = nullptr;
            continue;
        }
        auto collidingEnemies = getCollision<Enemy>(projectile);
        if (!collidingEnemies.empty()) {
            auto* enemy = collidingEnemies.front();
            enemy->damage(projectile->getDamage());
            if (!enemy->isAlive()) {
                erase_if(enemies, [enemy](auto* obj) {return enemy == obj;});
                delete enemy;
            }
            delete projectile;
            projectile = nullptr;
        }
    }
    erase_if(projectiles, [](auto* obj){return obj == nullptr;});
    for (auto* item : getCollision<Item>(player)) {
        itemPickUp(item);
        delete item;
    }
}

void Model::itemPickUp(Item* item) {
    auto type = item->getType();
    if (type == xp1 || type == xp5 || type == xp10) {
        player->addXp(static_cast<int>(type));
    }
}
