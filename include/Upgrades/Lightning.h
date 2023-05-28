#pragma once
#include "Weapon.h"

class Lightning : public Weapon {
    double areaBonus_;
public:
    explicit Lightning(AbstractPlayer* player);
    Projectile* activateWeapon(const std::vector<Enemy*>& enemies) override;
    void levelUp() override;
};

class LightningProjectile : public Projectile {
    const int width = 25;
    const int height = 24;
    double areaBonus;
    QPixmap rod;
public:
    LightningProjectile(int damage, double speed, int duration, int pierce, double areaBonus);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect() const override;
};
