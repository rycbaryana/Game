#pragma once
#include "AbstractPlayer.h"
#include "Weapon.h"
#include "PassiveUpgrade.h"

class Player : public AbstractPlayer{
    std::vector<std::shared_ptr<Weapon>> weapons_;
    std::vector<std::shared_ptr<PassiveUpgrade>> passives_;
public:
    Player();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QRectF boundingRect() const override;
    const std::vector<std::shared_ptr<Weapon>>& getWeapons();
    const std::vector<std::shared_ptr<PassiveUpgrade>>& getPassives();
    std::vector<Upgrade*> getPossibleUpgrades();
    int kills{0};
};
