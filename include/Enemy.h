#pragma once
#include "Creature.h"
#include <QDeadlineTimer>

class Enemy : public Creature {
    const int delay_ = 200;
protected:
    int baseDamage_;
    std::unique_ptr<QDeadlineTimer> timer_;
    Enemy(int baseDamage, int maxHealth);
public:
    void attack(Creature*);
    int getDamage() const;
};
