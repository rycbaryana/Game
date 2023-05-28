#pragma once
#include "Creature.h"

class AbstractPlayer : public QObject, public Creature {
    Q_OBJECT
protected:
    const int maxLevel = 80;
    int xp_ = 0;
    int level_ = 1;

public:
    double dmgBonus = 1.0;
    int amountBonus = 0;
    double cooldownReduction = 0;
    double pickupRange = 75;
    std::vector<int> neededXp;
    AbstractPlayer();
    int getXp() const;
    void addXp(int xp);
    int getLevel() const;
signals:
    void levelledUp();
};
