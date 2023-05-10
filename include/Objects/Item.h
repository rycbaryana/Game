#pragma once
#include "GameObject.h"

enum ItemType {
    xp1 = 1,
    xp5 = 5,
    xp10 = 10,
    destruction,
};

class Item : public GameObject {
    const ItemType type_;
public:
    Item(const QPointF& pos, ItemType type) : GameObject(pos), type_(type) { }
    ItemType getType() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect() const override;
};
