#pragma once
#include "Creature.h"
#include "QGraphicsItem"

class Player : public Creature, public QGraphicsItem {
    int xp_;
public:
    Player();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QRectF boundingRect() const override;
};
