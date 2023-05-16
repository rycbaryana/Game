#pragma once
#include <QGraphicsItem>
#include "Player.h"

class XpBar : public QGraphicsItem {
    const int height_ = 20;
    int width_;
    Player* player_;
public:
    explicit XpBar(Player* player, int width) : player_(player), width_(width) {}
    QRectF boundingRect() const override;
    void setWidth(int width);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
