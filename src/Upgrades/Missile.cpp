#include "Missile.h"
#include <QPainter>


void MissileProjectile::paint(
    QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget
) {
    painter->scale(1, -1);
    painter->drawPixmap(boundingRect().topLeft(), animation_.getCurrentFrame().scaledToWidth(size).transformed(QTransform().rotateRadians(atan2(-getDirection().y(), getDirection().x()))));
}

QRectF MissileProjectile::boundingRect() const {
    auto height = animation_.getCurrentFrame().scaledToWidth(size).height();
    return QRectF(-size/2, -height/2, size, height);
}

MissileProjectile::MissileProjectile(int damage, double speed, int pierce) : Projectile(damage, speed, 0, pierce) {
    AnimationManager anim(QPixmap(":/missile_projectile.png"), 2, speed, 27, 15, 0);
    setAnimation(anim);
}

Projectile* Missile::activateWeapon(const std::vector<Enemy*>& enemies) {
    if (!isReady() || enemies.empty()) return nullptr;
    auto* projectile = new MissileProjectile(getDamage(), getSpeed(), pirce_);
    ++currentAmount_;
    Enemy* closestEnemy = *std::min_element(
        enemies.begin(), enemies.end(),
        [&](const auto lhs, const auto rhs) {
            return vecLength(lhs->getPos() - player_->getPos())
                < vecLength(rhs->getPos() - player_->getPos());
        }
    );
    projectile->setDirection(closestEnemy->getPos() - player_->getPos());
    projectile->setPosition(player_->getPos());
    startCooldown();
    return projectile;
}

Missile::Missile(AbstractPlayer* player) {
    maxLevel = 8;
    baseDamage_ = 10;
    cooldown_ = 1000;
    amount_ = 1;
    delay_ = 100;
    speed_ = 4;
    level_ = 0;
    pirce_ = 1;
    player_ = player;
    sprite = QPixmap(":/Missile.png");
    name = QObject::tr("Artemis Arrow");

    levelDescription.push_back(QObject::tr("Fires at the nearest enemy."));
    levelDescription.push_back(QObject::tr("Fires 1 more projectile."));
    levelDescription.push_back(QObject::tr("Cooldown reduced by 0.2 seconds."));
    levelDescription.push_back(QObject::tr("Fires 1 more projectile."));
    levelDescription.push_back(QObject::tr("Base Damage up by 10."));
    levelDescription.push_back(QObject::tr("Fires 1 more projectile."));
    levelDescription.push_back(QObject::tr("Passes through 1 more enemy."));
    levelDescription.push_back(QObject::tr("Base Damage up by 10."));
}

void Missile::levelUp() {
    ++level_;
    switch (level_) {
        case 2:
            ++amount_;
            break ;
        case 3:
            cooldown_ -= 200;
            break ;
        case 4:
            ++amount_;
            break ;
        case 5:
            baseDamage_ += 10;
            break ;
        case 6:
            ++amount_;
            break ;
        case 7:
            ++pirce_;
            break ;
        case 8:
            baseDamage_ += 10;
            break ;
    }
}
