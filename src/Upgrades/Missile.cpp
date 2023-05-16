#include "Missile.h"
#include <QPainter>

void MissileProjectile::paint(
    QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget
) {
    painter->setPen({Qt::red, 5});
    painter->drawPath(shape());
}

QRectF MissileProjectile::boundingRect() const {
    return QRectF(-size/2, -size/2, size, size);
}

MissileProjectile::MissileProjectile(int damage, int speed) {
    damage_ = damage;
    speed_ = speed;
}

QPainterPath MissileProjectile::shape() const {
    auto [x, y] = getDirection();
    double angle = atan2(y, x);
    QPointF bl = {0, 0};
    QPainterPath shape(bl);
    shape.lineTo(bl + size * QPointF(cos(angle), sin(angle)));
    return shape;
}

Projectile* Missile::activateWeapon(const QPointF& pos, const std::vector<Enemy*>& enemies) {
    if (!isReady() || enemies.empty()) return nullptr;
    auto* projectile = new MissileProjectile(baseDamage_, speed_);
    ++currentAmount_;
    Enemy* closestEnemy = *std::min_element(
        enemies.begin(), enemies.end(),
        [&](const auto lhs, const auto rhs) {
            return vecLength(lhs->getPos() - pos)
                < vecLength(rhs->getPos() - pos);
        }
    );
    projectile->setDirection(closestEnemy->getPos() - pos);
    projectile->setPosition(pos);
    startCooldown();
    return projectile;
}

Missile::Missile() {
    baseDamage_ = 10;
    cooldown_ = 1000;
    amount_ = 1;
    delay_ = 100;
    speed_ = 7;
    level_ = 0;
    levelDescription.push_back("Missile lvl 1");
    levelDescription.push_back("Missile lvl 2");
    levelDescription.push_back("Missile lvl 3");
    levelDescription.push_back("Missile lvl 4");
    levelDescription.push_back("Missile lvl 5");
    levelDescription.push_back("Missile lvl 6");
    levelDescription.push_back("Missile lvl 7");
    levelDescription.push_back("Missile lvl 8");
}

void Missile::levelUp() {
    ++level_;
    if (level_ == 2) {
        ++amount_;
    }
}
