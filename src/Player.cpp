#include "Player.h"
#include <QPainter>

Player::Player() : Creature(100) {
    xp_ = 0;
    speed_ = 5;
}

void Player::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setPen({Qt::black, 1});
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawRect(boundingRect());
}

QRectF Player::boundingRect() const {
    return QRectF(-25, -25, 50, 50);
}

