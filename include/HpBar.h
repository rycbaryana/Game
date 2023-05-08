#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include "Creature.h"

class HpBar : public QGraphicsItem {
private:
    Creature* creature_;
public:
    explicit HpBar(Creature* creature) : QGraphicsItem(creature), creature_(creature) {}
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
