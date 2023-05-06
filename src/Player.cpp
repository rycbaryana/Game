#include "Player.h"
#include <QPainter>

Player::Player() {
    xp_ = 0;
    pos_ = {0, 0};
    maxHealth_ = 100;
    health_ = maxHealth_;
    speed_ = 5;
    direction_ = {0, 0};
}

void Player::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setPen({Qt::black, 1});
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawRect(boundingRect());
}

QRectF Player::boundingRect() const {
    return QRectF(-25, -25, 50, 50);
}

