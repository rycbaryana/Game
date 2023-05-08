#pragma once
#include "Upgrade.h"
#include "Projectile.h"
#include <QDeadlineTimer>
#include "Enemy.h"

class Weapon : public Upgrade {
protected:
    int baseDamage_;
    int cooldown_;
    int amount_;
    double speed_;
    std::unique_ptr<QDeadlineTimer> timer_;
public:
    Weapon();
    int getDamage() const;
    int getCooldown() const;
    int getAmount() const;
    double getSpeed() const;
    void startCooldown();
    bool isReady();
    virtual Projectile* activateWeapon(const QPointF& pos, const std::vector<Enemy*>&) = 0;
    virtual ~Weapon() = default;
};
