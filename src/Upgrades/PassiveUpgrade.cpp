#include "PassiveUpgrade.h"

PassiveUpgrade::PassiveUpgrade(UpgradeType type, AbstractPlayer* player) : type_(type) {
    player_ = player;
    maxLevel = type == Amount ? 2 : 5;
    QMap<UpgradeType, QString> typeName = {{Damage, "Damage"}, {Amount, "Amount"}};
    QMap<UpgradeType, QString> typeDescription = {{Damage, "Raises inflicted damage by 10%."}, {Amount, {"Shoots additional projectile."}}};
    name = typeName[type];
    sprite = QPixmap(":/Whip.png");
    levelDescription.insert(levelDescription.begin(), maxLevel, typeDescription[type]);
}

void PassiveUpgrade::levelUp() {
    ++level_;
    switch (type_) {
        case Damage:
            player_->dmgBonus += 0.1;
            break ;
        case Amount:
            player_->amountBonus += 1;
            break ;
        case MaxHealth:
            player_->addMaxHealth(20);
            break ;
        case Cooldown:
            player_->cooldownReduction += 0.1;
            break ;
    }
}
