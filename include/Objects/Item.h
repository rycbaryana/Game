#pragma once
#include "GameObject.h"

enum ItemType {
    xp,
    destruction,
    vacuum
};

class Item : public GameObject {
    const ItemType type_;
public:
    Item(const QPointF& pos, ItemType type) : GameObject(pos), type_(type) { }
    ItemType getType() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect() const override;
};
