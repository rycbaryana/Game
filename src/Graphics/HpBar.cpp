#include "HpBar.h"

QRectF HpBar::boundingRect() const {
    return QRectF(-creature_->boundingRect().width() / 2, -5, creature_->boundingRect().width(), 10);
}

void HpBar::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::black);
    painter->drawRect(boundingRect());
    painter->setBrush(Qt::red);
    auto healthRect = QRectF(boundingRect().topLeft(), QSize(boundingRect().width() * creature_->getHealth() / creature_->getMaxHealth() ,boundingRect().height()));
    painter->drawRect(healthRect);
};
