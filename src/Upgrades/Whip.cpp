#include "Whip.h"
#include <QPainter>

Whip::Whip(AbstractPlayer* player) {
    maxLevel = 8;
    baseDamage_ = 10;
    cooldown_ = 1350;
    amount_ = 1;
    delay_ = 200;
    speed_ = 0;
    level_ = 0;
    pirce_ = 0;
    duration_ = 150;
    sprite = QPixmap(":/Whip.png");
    name = "Whip";
    player_ = player;

    levelDescription.push_back(
        QObject::tr("Attacks horizontally, passes through enemies. Make them cry.")
    );
    levelDescription.push_back(QObject::tr("Fires 1 more projectile."));
    levelDescription.push_back(QObject::tr("Base Damage up by 5"));
    levelDescription.push_back(QObject::tr("Base Damage up by 5."));
    levelDescription.push_back(QObject::tr("Base Damage up by 5."));
    levelDescription.push_back(QObject::tr("Base Damage up by 5."));
    levelDescription.push_back(QObject::tr("Base Damage up by 5."));
    levelDescription.push_back(QObject::tr("Base Damage up by 5."));
}

void Whip::levelUp() {
    ++level_;
    switch (level_) {
        case 2:
            ++amount_;
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            baseDamage_ += 5;
            break;
    }
}

Projectile* Whip::activateWeapon(const std::vector<Enemy*>& enemies) {
    if (!isReady())
        return nullptr;
    auto* projectile = new WhipProjectile(getDamage(), getSpeed(), duration_, pirce_);
    ++currentAmount_;
    double x = player_->getSightDirection().x() >= 0 ? 1 : -1;
    projectile->setDirection(currentAmount_ % 2 == 1 ? QPointF(x, 0) : QPointF(-x, 0));
    projectile->setPosition(player_->getPos() + QPointF(0, projectile->boundingRect().height() * ((currentAmount_ - 1) / 2)));
    projectile->startCountdown();
    startCooldown();
    return projectile;
}

void WhipProjectile::paint(
    QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget
) {
    painter->scale(1, -1);
    auto coeff = static_cast<double>(duration_ - timer_->remainingTime()) / duration_;
    painter->drawPixmap(
        boundingRect().topLeft(),
        animation_.getCurrentFrame()
            .scaled(coeff * width, coeff * height)
            .transformed(QTransform::fromScale(direction_.x() >= 0 ? 1 : -1, 1))
    );
}

QRectF WhipProjectile::boundingRect() const {

    auto coeff = static_cast<double>(duration_ - timer_->remainingTime()) / duration_;
    double curWidth = coeff * width;
    double curHeight = coeff * height;
    if (direction_.x() >= 0) {
        return QRectF(0, -curHeight / 2, curWidth, curHeight);
    } else {
        return QRectF(-curWidth, -curHeight / 2, curWidth, curHeight);
    }
}

WhipProjectile::WhipProjectile(int damage, double speed, int duration, int pierce)
    : Projectile(damage, speed, duration, pierce) {
    AnimationManager anim(QPixmap(":/slash.png"));
    setAnimation(anim);
}

QPainterPath WhipProjectile::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
