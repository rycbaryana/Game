#include "Knife.h"
#include <QPainter>

Knife::Knife(AbstractPlayer* player) {
    maxLevel = 8;
    baseDamage_ = 10;
    cooldown_ = 1000;
    amount_ = 1;
    delay_ = 150;
    speed_ = 6;
    level_ = 0;
    pirce_ = 1;
    player_ = player;
    sprite = QPixmap(":/Knife.png");
    name = QObject::tr("Ares Knives");

    levelDescription.push_back(QObject::tr("Fires quickly in the faced direction."));
    levelDescription.push_back(QObject::tr("Fires 1 more projectile."));
    levelDescription.push_back(QObject::tr("Fires 1 more projectile. Base Damage up by 5."));
    levelDescription.push_back(QObject::tr("Fires 1 more projectile."));
    levelDescription.push_back(QObject::tr("Passes through 1 more enemy."));
    levelDescription.push_back(QObject::tr("Fires 1 more projectile."));
    levelDescription.push_back(QObject::tr("Fires 1 more projectile. Base Damage up by 5."));
    levelDescription.push_back(QObject::tr("Passes through 1 more enemy."));
}

void Knife::levelUp() {
    ++level_;
    switch (level_) {
        case 2:
            ++amount_;
            break ;
        case 3:
            ++amount_;
            baseDamage_ += 5;
            break ;
        case 4:
            ++amount_;
            delay_ -= 20;
            break ;
        case 5:
            ++pirce_;
            break ;
        case 6:
            ++amount_;
            delay_ -= 20;
            break ;
        case 7:
            ++amount_;
            baseDamage_ += 5;
            break ;
        case 8:
            ++pirce_;
            delay_ -= 20;
            break ;
    }
}

Projectile* Knife::activateWeapon(const std::vector<Enemy*>& enemies) {
    if (!isReady()) return nullptr;
    auto* projectile = new KnifeProjectile(getDamage(), getSpeed(), pirce_);
    ++currentAmount_;
    if (player_->getDirection().isNull()) {
        auto [x, y] = player_->getSightDirection();
        if (y != 0) {
            projectile->setDirection({0, y});
        } else {
            projectile->setDirection({x, 0});
        }
    } else {
        projectile->setDirection(player_->getDirection());
    }
    projectile->setPosition(player_->getPos());
    startCooldown();
    return projectile;
}

KnifeProjectile::KnifeProjectile(int damage, double speed, int pierce) : Projectile(damage, speed, 0, pierce) {
    AnimationManager anim(QPixmap(":/Knife.png").scaledToWidth(size));
    setAnimation(anim);
}

void KnifeProjectile::paint(
    QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget
) {
    painter->scale(1, -1);
    painter->drawPixmap(boundingRect().topLeft(), animation_.getCurrentFrame().transformed(QTransform().rotateRadians(atan2(-getDirection().y(), getDirection().x()))));
}

QRectF KnifeProjectile::boundingRect() const {
    auto height = animation_.getCurrentFrame().scaledToWidth(size).height();
    return QRectF(-size/2, -height/2, size, height);
}

