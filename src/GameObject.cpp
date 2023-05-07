#include "GameObject.h"

void GameObject::setPosition(double x, double y) {
    pos_.setX(x);
    pos_.setY(y);
}

const QPointF& GameObject::getPos() const {
    return pos_;
}

GameObject::GameObject() : pos_() { }

GameObject::GameObject(const QPointF& pos) : pos_(pos) { }
