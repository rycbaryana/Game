#include "MovableObject.h"

void MovableObject::setSpeed(double speed) {
    speed_ = speed;
}

void MovableObject::setDirection(const QPointF& direction) {
    direction_ = direction;
}

double MovableObject::getSpeed() const {
    return speed_;
}

const QPointF& MovableObject::getDirection() const {
    return direction_;
}

void MovableObject::move() {
    auto length = sqrt(QPointF::dotProduct(direction_, direction_));
    if (length == 0) return;
    pos_.setX(pos_.x() + speed_ * direction_.x() / length);
    pos_.setY(pos_.y() - speed_ * direction_.y() / length);
}

void MovableObject::setMove(bool move) {
    move_ = move;
}

bool MovableObject::isMoving() {
    return move_;
}
