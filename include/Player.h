#pragma once
#include "Creature.h"
#include "Weapon.h"

class Player : public Creature {
    int xp_;
    std::vector<std::unique_ptr<Weapon>> weapons_;
public:
    Player();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QRectF boundingRect() const override;
    const std::vector<std::unique_ptr<Weapon>>& getWeapons();
};
