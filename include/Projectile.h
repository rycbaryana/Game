#pragma once
#include "MovableObject.h"

class Projectile : public MovableObject {
protected:
    int damage_;
public:
    int getDamage() const;
};
