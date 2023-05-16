#pragma once
#include "Creature.h"
#include <QDeadlineTimer>
#include "Item.h"

class Enemy : public Creature {
    const int delay_ = 200;

    int baseDamage_;
    ItemType xp_;
    int id_;
    std::unique_ptr<QDeadlineTimer> timer_;

public:
    Enemy(int id, const QPointF& pos);
    ~Enemy();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void attack(Creature*);
    int getDamage() const;
    int getId() const;
    void setStats(const std::vector<double>& stats);
    Item* dropXp();
};
