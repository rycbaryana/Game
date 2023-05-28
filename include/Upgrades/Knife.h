#pragma once
#include "Weapon.h"
#include "Projectile.h"
class Knife : public Weapon {
public:
    explicit Knife(AbstractPlayer* player);
    Projectile* activateWeapon(const std::vector<Enemy*>& enemies) override;
    void levelUp() override;
};

class KnifeProjectile : public Projectile {
    const int size = 30;
public:
    KnifeProjectile(int damage, double speed, int pierce);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect() const override;
};