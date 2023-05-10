#include "Enemy.h"
#include <QGraphicsScene>

Enemy::Enemy(int baseDamage, int maxHealth, ItemType xp) : Creature(maxHealth), baseDamage_(baseDamage), timer_(std::make_unique<QDeadlineTimer>()), xp_(xp){}

int Enemy::getDamage() const {
    return baseDamage_;
}

void Enemy::attack(Creature* target) {
    if (!timer_->hasExpired()) return;
    target->damage(baseDamage_);
    timer_->setRemainingTime(delay_);
}

Item* Enemy::dropXp() {
    return new Item(pos_, xp_);
}

Enemy::~Enemy() {
    scene()->addItem(dropXp());
}

