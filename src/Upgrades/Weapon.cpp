#include "Weapon.h"

int Weapon::getDamage() const {
    return baseDamage_;
}

int Weapon::getCooldown() const {
    return cooldown_;
}

int Weapon::getAmount() const {
    return amount_;
}

double Weapon::getSpeed() const {
    return speed_;
}

void Weapon::startCooldown() {
    timer_->setRemainingTime(cooldown_);
}

bool Weapon::isReady() {
    return timer_->hasExpired();
}

Weapon::Weapon() : timer_(std::make_unique<QDeadlineTimer>()){ }
