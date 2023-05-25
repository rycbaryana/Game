#pragma once
#include "Item.h"

class XpItem : public Item {
    int xp_;
public:
    XpItem(const QPointF& pos, int xp) : xp_(xp), Item(pos, ItemType::xp) {}
    int getXp() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect() const override;
};
