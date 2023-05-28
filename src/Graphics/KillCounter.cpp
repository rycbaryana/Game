#include "KillCounter.h"
#include "QPainter"

QRectF KillCounter::boundingRect() const {
    double width = icon_.width();
    double height = icon_.height();
    return QRectF(-width  / 2, -height / 2, width, height);
}

void KillCounter::paint(
    QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget
) {
    painter->setFont(QFont(painter->font().family(), 14));
    painter->drawPixmap(boundingRect().topLeft(), icon_);
    painter->setPen(Qt::white);
    painter->drawText(boundingRect().topLeft() + QPointF(icon_.width(), painter->fontMetrics().height() / 2.0 + 2), QString::number(player_->kills));
}
