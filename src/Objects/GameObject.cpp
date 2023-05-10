#include "GameObject.h"

void GameObject::setPosition(double x, double y) {
    pos_.setX(x);
    pos_.setY(y);
    setPos(x, y);
}

const QPointF& GameObject::getPos() const {
    return pos_;
}

GameObject::GameObject() : pos_() { }

GameObject::GameObject(const QPointF& pos) : pos_(pos) {
    setPos(pos);
}

void GameObject::setPosition(const QPointF& pos) {
    pos_ = pos;
    setPos(pos);
}

double vecLength(const QPointF& vec) {
    return sqrt(QPointF::dotProduct(vec, vec));
}
