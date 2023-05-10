#include "Player.h"
#include "HpBar.h"
#include "Missile.h"
#include <QPainter>
#include "XpBar.h"

Player::Player() : Creature(100), neededXp(81) {
    speed_ = 5;
    weapons_.push_back(std::make_unique<Missile>());

    auto* hpBar = new HpBar(this);
    hpBar->setPos(0, -boundingRect().height() / 2 - hpBar->boundingRect().height() / 2 - 5);

    auto* xpBar = new XpBar(this);
    xpBar->setPos(0, 400 - xpBar->boundingRect().height() / 2);

    int inc = 10;
    neededXp[1] = 5;
    for (int i = 2; i <= 80; ++i) {
        if ((i - 1) % 20 == 0) {
            inc += 3;
        }
        neededXp[i] = neededXp[i - 1] + inc;
    }
}

void Player::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setPen({Qt::black, 2});
    painter->drawRect(boundingRect());
}

QRectF Player::boundingRect() const {
    return QRectF(-25 - 1, -25 - 1, 50 + 2, 50 + 2);
}

const std::vector<std::unique_ptr<Weapon>>& Player::getWeapons() {
    return weapons_;
}

int Player::getXp() {
    return xp_;
}

void Player::addXp(int xp) {
    xp_ += xp;
    if (xp_ >= neededXp[level_]) {
        xp_ -= neededXp[level_];
        ++level_;
    }
}

int Player::getLevel() {
    return level_;
}
