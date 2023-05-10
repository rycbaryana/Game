#pragma once
#include "Creature.h"
#include "Weapon.h"

class Player : public Creature {
    int xp_ = 0;
    int level_ = 1;
    std::vector<std::unique_ptr<Weapon>> weapons_;
public:
    std::vector<int> neededXp;
    int getXp();
    void addXp(int xp);
    int getLevel();
    Player();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QRectF boundingRect() const override;
    const std::vector<std::unique_ptr<Weapon>>& getWeapons();
};
