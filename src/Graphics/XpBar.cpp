#include "XpBar.h"
#include <QPainter>

QRectF XpBar::boundingRect() const {
    return QRectF(0, 0, width, height);
}

void XpBar::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setBrush(Qt::blue);
    painter->setPen(Qt::NoPen);
    auto xpRect = QRectF(
        0, 0, width * player_->getXp() / player_->neededXp[player_->getLevel()], height
    );
    painter->drawRect(xpRect);
    painter->setPen(Qt::black);
    painter->setFont(QFont("times", 15));
    QString levelString = QString("Level %1").arg(player_->getLevel());
    painter->drawText(QPointF(width / 2 - painter->fontMetrics().horizontalAdvance(levelString) / 2, height),
        levelString
    );
}
