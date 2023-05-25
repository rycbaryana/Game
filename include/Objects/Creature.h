#pragma once
#include "MovableObject.h"

class Creature : public MovableObject {
protected:
    explicit Creature(int maxHealth);
    int maxHealth_;
    int health_;
public:
    Creature();
    bool isAlive() const;
    int getHealth() const;
    int getMaxHealth() const;
    void heal(int);
    void damage(int);
    void addMaxHealth(int);
};
