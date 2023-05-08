#include "Player.h"
#include "HpBar.h"
#include "Missile.h"
#include <QPainter>


Player::Player() : Creature(100) {
    xp_ = 0;
    speed_ = 5;
    weapons_.push_back(std::make_unique<Missile>());
    auto* hp = new HpBar(this);
    hp->setPos(0, -boundingRect().height() / 2 - hp->boundingRect().height() / 2 - 5);
}

void Player::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setPen({Qt::black, 1});
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawRect(boundingRect());
}

QRectF Player::boundingRect() const {
    return QRectF(-25, -25, 50, 50);
}

const std::vector<std::unique_ptr<Weapon>>& Player::getWeapons() {
    return weapons_;
}
