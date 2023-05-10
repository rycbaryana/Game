#include "Creature.h"

bool Creature::isAlive() const {
    return health_ > 0;
}

int Creature::getHealth() const {
    return health_;
}

int Creature::getMaxHealth() const {
    return maxHealth_;
}

void Creature::heal(int heal) {
    health_ = std::min(health_ + heal, maxHealth_);
}

void Creature::damage(int damage) {
    health_ = std::max(health_ - damage, 0);
}

Creature::Creature(int maxHealth) : maxHealth_(maxHealth), health_(maxHealth) { }

Creature::Creature() : Creature(0) { }
