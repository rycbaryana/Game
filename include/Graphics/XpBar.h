#pragma once
#include <QGraphicsItem>
#include "Player.h"
#include "GameWindow.h"

class XpBar : public QGraphicsItem {
    const int height = 20;
    const int width = 2 * GameWindow::size;
    Player* player_;
public:
    explicit XpBar(Player* player, QGraphicsItem* parent = nullptr) : QGraphicsItem(parent), player_(player) {}
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
