#pragma once
#include "Weapon.h"

class Missile : public Weapon {
public:
    Missile();
    Projectile* activateWeapon(const QPointF& pos, const std::vector<Enemy*>& enemies) override;
    void levelUp() override;
};

class MissileProjectile : public Projectile {
    const int size = 20;
public:
    MissileProjectile(int damage, int speed);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
};
