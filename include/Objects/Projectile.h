#pragma once
#include "MovableObject.h"
#include <QDeadlineTimer>

class Projectile : public MovableObject {
protected:
    int damage_;
    int duration_;
    int pierce_;
    int pierced_{0};
    std::unique_ptr<QDeadlineTimer> timer_;
public:
    Projectile(int damage, double speed, int duration, int pierce) : damage_(damage), duration_(duration), pierce_(pierce), timer_(std::make_unique<QDeadlineTimer>(QDeadlineTimer::Forever)) {speed_ = speed;};
    int getDamage() const;
    int getPierce() const;
    bool canKill() const;
    void increasePierced();
    bool hasExpired() const;
    bool isForever() const;
    void startCountdown();
};
