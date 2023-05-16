#pragma once
#include "Creature.h"
#include "Weapon.h"

class Player : public Creature {
    const int maxLevel = 80;
    int xp_ = 0;
    int level_ = 1;
    std::vector<std::shared_ptr<Weapon>> weapons_;
public:
    std::vector<std::shared_ptr<Weapon>> possibleWeapons;
    std::vector<int> neededXp;
    int getXp();
    void addXp(int xp);
    int getLevel() const;
    Player();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QRectF boundingRect() const override;
    const std::vector<std::shared_ptr<Weapon>>& getWeapons();
};
