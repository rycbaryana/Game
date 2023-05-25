#include "Projectile.h"

int Projectile::getDamage() const {
    return damage_;
}

bool Projectile::hasExpired() const {
    return timer_->hasExpired();
}

void Projectile::startCountdown() {
    timer_->setRemainingTime(duration_);
}

int Projectile::getPierce() const {
    return pierce_;
}

bool Projectile::isForever() const {
    return timer_->remainingTime() == -1;
}

bool Projectile::canKill() const {
    return pierced_ < pierce_;
}

void Projectile::increasePierced() {
    ++pierced_;
}
