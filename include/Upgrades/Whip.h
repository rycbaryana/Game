#pragma once
#include "Weapon.h"
#include "Enemy.h"

class Whip : public Weapon {
public:
    explicit Whip(AbstractPlayer* player);
    Projectile* activateWeapon(const std::vector<Enemy*>& enemies) override;
    void levelUp() override;
};

class WhipProjectile : public Projectile {
    const int width = 147 * 1.5;
    const int height = 22 * 1.5;
public:
    WhipProjectile(int damage, double speed, int duration, int pierce);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
};
