#pragma once
#include "Upgrade.h"
#include <QMap>

enum UpgradeType {
    Damage,
    Amount,
    MaxHealth,
    Cooldown,
};

class PassiveUpgrade : public Upgrade {
    UpgradeType type_;
public:
    explicit PassiveUpgrade(UpgradeType type, AbstractPlayer* player);
    void levelUp() override;
};
