#include "Item.h"
#include <QPainter>

QRectF Item::boundingRect() const {
    return QRectF(-5, -5, 10, 10);
}

void Item::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setBrush(Qt::green);
    painter->drawRect(boundingRect());
}

ItemType Item::getType() const {
    return type_;
}
