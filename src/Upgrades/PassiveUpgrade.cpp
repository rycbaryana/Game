#include "PassiveUpgrade.h"

PassiveUpgrade::PassiveUpgrade(UpgradeType type, AbstractPlayer* player) : type_(type) {
    player_ = player;
    maxLevel = type == Amount ? 2 : 5;
    std::vector<QString> names = {QObject::tr("Damage"), QObject::tr("Amount"), QObject::tr("Max Health"), QObject::tr("Cooldown")};
    std::vector<QString> descriptions = {QObject::tr("Raises inflicted damage by 10%."), QObject::tr("Shoots additional projectile."), QObject::tr("Max health increases by 20."), QObject::tr("Reduces all cooldown by 8%.")};
    name = names[type];
    sprite = QPixmap(":/passive.png");
    levelDescription.insert(levelDescription.begin(), maxLevel, descriptions[type]);
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
            player_->cooldownReduction += 0.08;
            break ;
    }
}
