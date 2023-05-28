#include "Lightning.h"
#include <QPainter>
#include <QRandomGenerator>

Lightning::Lightning(AbstractPlayer* player) {
    maxLevel = 8;
    baseDamage_ = 10;
    cooldown_ = 4000;
    amount_ = 2;
    delay_ = 200;
    speed_ = 0;
    level_ = 0;
    pirce_ = 0;
    duration_ = 150;
    areaBonus_ = 1.0;
    sprite = QPixmap(":/Lightning.png");
    name = QObject::tr("The Ring of Zeus");
    player_ = player;

    levelDescription.push_back(
        QObject::tr("Strikes at random enemies.")
    );
    levelDescription.push_back(QObject::tr("Fires 1 more projectile."));
    levelDescription.push_back(QObject::tr("Area increased. Base Damage up by 10."));
    levelDescription.push_back(QObject::tr("Fires 1 more projectile."));
    levelDescription.push_back(QObject::tr("Area increased. Base Damage up by 20."));
    levelDescription.push_back(QObject::tr("Fires 1 more projectile."));
    levelDescription.push_back(QObject::tr("Area increased. Base Damage up by 20."));
    levelDescription.push_back(QObject::tr("Fires 1 more projectile."));
}

void Lightning::levelUp() {
    ++level_;
    switch (level_) {
        case 2:
            ++amount_;
            break ;
        case 3:
            ++areaBonus_;
            baseDamage_ += 10;
            break ;
        case 4:
            ++amount_;
            break ;
        case 5:
            ++areaBonus_;
            baseDamage_ += 20;
            break ;
        case 6:
            ++amount_;
            break ;
        case 7:
            ++areaBonus_;
            baseDamage_ += 20;
            break ;
        case 8:
            ++amount_;
            break ;
    }
}

Projectile* Lightning::activateWeapon(const std::vector<Enemy*>& enemies) {
    if (!isReady() || enemies.empty())
        return nullptr;
    auto* projectile = new LightningProjectile(getDamage(), getSpeed(), duration_, pirce_, areaBonus_);
    ++currentAmount_;
    auto* enemy = enemies[QRandomGenerator::global()->bounded(static_cast<int>(enemies.size()))];
    projectile->setPosition(enemy->getPos());
    projectile->startCountdown();
    startCooldown();
    return projectile;
}

LightningProjectile::LightningProjectile(int damage, double speed, int duration, int pierce, double areaBonus)
    : Projectile(damage, speed, duration, pierce), areaBonus(areaBonus) {
    rod = QPixmap(":/lightning_rod.png");
    AnimationManager anim(QPixmap(":/lightning_projectile"));
    setAnimation(anim);
}

void LightningProjectile::paint(
    QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget
) {
    painter->scale(1, -1);
    auto coeff = static_cast<double>(duration_ - timer_->remainingTime()) / duration_;
    painter->drawPixmap(
        boundingRect().topLeft(),
        animation_.getCurrentFrame()
            .scaled(coeff * width * areaBonus, coeff * height * areaBonus)
    );
    painter->drawPixmap(-rod.width() / 2, -rod.height(), rod);
    painter->setPen(Qt::red);
}

QRectF LightningProjectile::boundingRect() const {
    auto coeff = static_cast<double>(duration_ - timer_->remainingTime()) / duration_;
    double curWidth = coeff * width * areaBonus;
    double curHeight = coeff * height * areaBonus;
    return QRectF(-curWidth / 2, -curHeight / 2, curWidth, curHeight);
}
