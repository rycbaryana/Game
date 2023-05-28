#include "XpBar.h"
#include <QPainter>

QRectF XpBar::boundingRect() const {
    return QRectF(0, 0, width_, height_);
}

void XpBar::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setBrush(Qt::blue);
    painter->setPen(Qt::NoPen);
    auto xpRect = QRectF(
        0, 0, width_ * player_->getXp() / player_->neededXp[player_->getLevel()], height_);
    painter->drawRect(xpRect);
    painter->setPen(Qt::black);
    painter->setFont(QFont("times", 15));
    QString levelString = QObject::tr("Level %1").arg(player_->getLevel());;
    painter->setPen(Qt::gray);
    painter->drawText(width_ / 2 - painter->fontMetrics().horizontalAdvance(levelString) / 2, height_ / 2 + painter->font().pointSize() / 2.,
        levelString
    );
}

void XpBar::setWidth(int width) {
    width_ = width;
}
