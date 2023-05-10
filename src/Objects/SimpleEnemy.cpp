#include "SimpleEnemy.h"
#include <QPainter>

SimpleEnemy::SimpleEnemy() : Enemy(1, 10, xp1) {
    speed_ = 1;
}

void SimpleEnemy::paint(
    QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget
) {
    painter->setPen({Qt::red, 1});
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawRect(boundingRect());
}

QRectF SimpleEnemy::boundingRect() const {
    return QRectF(-10, -10, 20, 20);
}

SimpleEnemy::SimpleEnemy(const QPointF& pos) : SimpleEnemy() {
    pos_ = pos;
    setPos(pos);
}
