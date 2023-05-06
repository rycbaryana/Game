#pragma once
#include "MovableObject.h"

class Creature : public MovableObject {
protected:
    int maxHealth_;
    int health_;
public:
    bool isAlive() const;
    int getHealth() const;
    int getMaxHealth() const;
    void heal(int);
    void damage(int);
};
