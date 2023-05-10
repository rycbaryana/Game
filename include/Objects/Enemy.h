#pragma once
#include "Creature.h"
#include <QDeadlineTimer>
#include "Item.h"

class Enemy : public Creature {
    const int delay_ = 200;
protected:
    int baseDamage_;
    ItemType xp_;
    std::unique_ptr<QDeadlineTimer> timer_;
public:
    Enemy(int baseDamage, int maxHealth, ItemType xp);
    ~Enemy();
    void attack(Creature*);
    int getDamage() const;
    Item* dropXp();
};
