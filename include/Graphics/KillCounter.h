#pragma once
#include <QGraphicsItem>
#include "Player.h"

class KillCounter : public QGraphicsItem {
    Player* player_;
    QPixmap icon_;
public:
    explicit KillCounter(Player* player) : QGraphicsItem(), player_(player), icon_(":/counter.png") {
        icon_ = icon_.scaled(22, 20);
    }
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
