#include "Enemy.h"

Enemy::Enemy(int baseDamage, int maxHealth) : Creature(maxHealth), baseDamage_(baseDamage), timer_(std::make_unique<QDeadlineTimer>()) {}

int Enemy::getDamage() const {
    return baseDamage_;
}

void Enemy::attack(Creature* target) {
    if (!timer_->hasExpired()) return;
    target->damage(baseDamage_);
    timer_->setRemainingTime(delay_);
}
