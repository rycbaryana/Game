#pragma once
#include "Creature.h"
#include <QGraphicsItem>

class Enemy : public Creature, public QGraphicsItem {
protected:
    explicit Enemy(int maxHealth);
};
