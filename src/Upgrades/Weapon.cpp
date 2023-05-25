#include "Weapon.h"

int Weapon::getDamage() const {
    return baseDamage_ * player_->dmgBonus;
}

int Weapon::getCooldown() const {
    return cooldown_ * (1 - player_->cooldownReduction);
}

int Weapon::getAmount() const {
    return amount_ + player_->amountBonus;
}

double Weapon::getSpeed() const {
    return speed_;
}

void Weapon::startCooldown() {
    if (currentAmount_ == getAmount()) {
        currentAmount_ = 0;
        timer_->setRemainingTime(getCooldown());
    } else {
        timer_->setRemainingTime(delay_);
    }
}

bool Weapon::isReady() {
    return timer_->hasExpired();
}

Weapon::Weapon() : timer_(std::make_unique<QDeadlineTimer>()){ }
