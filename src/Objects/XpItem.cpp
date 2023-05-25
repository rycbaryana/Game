#include "XpItem.h"
#include <QPainter>

int XpItem::getXp() const {
    return xp_;
}

void XpItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    QPixmap pm;
    if (xp_ <= 2) {
        pm.load(":/xp1.png");
    } else if (xp_ <= 9) {
        pm.load(":/xp2.png");
    } else {
        pm.load(":/xp3.png");
    }
    painter->scale(1, -1);
    painter->drawPixmap(boundingRect().topLeft(), pm.scaled(boundingRect().size().toSize()));
}

QRectF XpItem::boundingRect() const {
    QSizeF size = {11, 14};
    size *= 1.5;
    return QRectF(QPointF(-size.width() / 2, -size.height() / 2), size);
}
