#include "Model.h"
#include "GameWindow.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "XpItem.h"

Model::Model() : player(new Player) {
    loadWaves();
    loadEnemies();
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
            collidingEnemy->move(qMin(3.0, qPow(minDst / dst, 5)) * collidingEnemy->getSpeed(), -dir, false);
        }
    }
    auto pred = [](auto* obj){return obj == nullptr;};
    for (auto*& projectile : projectiles) {
        projectile->move();
        if (vecLength(projectile->getPos() - player->getPos()) > sqrt(2) * qMax(width, height) || projectile->hasExpired()) {
            delete projectile;
            projectile = nullptr;
            continue;
        }
        auto collidingEnemies = getCollision<Enemy>(projectile);
        if (!collidingEnemies.empty()) {
            size_t size = collidingEnemies.size();
            for (size_t i = 0; (projectile->canKill() || projectile->getPierce() == 0) && i < size; ++i) {
                auto* enemy = collidingEnemies[i];
                enemy->damage(projectile->getDamage());
                if (!enemy->isAlive()) {
                    erase_if(enemies, [enemy](auto* obj) {return enemy == obj;});
                    delete enemy;
                }
                projectile->increasePierced();
            }
            if (projectile->isForever() && !projectile->canKill()) {
                delete projectile;
                projectile = nullptr;
            }
        }
    }
    erase_if(projectiles, pred);
}

void Model::itemPickUp(Item* item) {
    auto type = item->getType();
    if (type == xp) {
         player->addXp(dynamic_cast<XpItem*>(item)->getXp());
    }
}

void Model::loadWaves() {
    QFile wavesFile(":/json/waves.json");
    wavesFile.open(QIODevice::ReadOnly);
    QJsonDocument wavesJson(QJsonDocument::fromJson(wavesFile.readAll()));
    QJsonArray wavesArray = wavesJson.array();
    for (int i = 0; i < wavesArray.size(); ++i) {
        auto waveObj = wavesArray[i].toObject();
        Wave wave{i, waveObj["delay"].toInt(), waveObj["minAmount"].toInt(), {}};
        auto ids = waveObj["enemies"].toArray();
        for (auto id : ids) {
            wave.enemiesId.push_back(id.toInt());
        }
        waves.push_back(wave);
    }

    wavesFile.close();
}

Enemy* Model::newEnemy(int id, const QPointF& pos) {
    auto* enemy = new Enemy(id, pos);
    enemy->setStats(enemiesTable[id]);
    return enemy;
}

void Model::loadEnemies() {
    QFile enemiesFile(":/json/enemies.json");
    enemiesFile.open(QIODevice::ReadOnly);
    QJsonDocument enemiesJson(QJsonDocument::fromJson(enemiesFile.readAll()));
    QJsonArray enemiesArr = enemiesJson.array();
    for (int i = 0; i < enemiesArr.size(); ++i) {
        auto enemy = enemiesArr[i].toObject();
        enemiesTable[i] = {};
        enemiesTable[i].push_back(enemy["baseDamage"].toInt());
        enemiesTable[i].push_back(enemy["maxHealth"].toInt());
        enemiesTable[i].push_back(enemy["speed"].toDouble());
        enemiesTable[i].push_back(enemy["xp"].toInt());
    }
    enemiesFile.close();
}
