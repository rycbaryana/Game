#pragma once
#include "Enemy.h"

class SimpleEnemy : public Enemy {
public:
    SimpleEnemy();
    explicit SimpleEnemy(const QPointF& pos);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QRectF boundingRect() const override;
};
