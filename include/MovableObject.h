#pragma once
#include "GameObject.h"

class MovableObject : public GameObject {
protected:
    double speed_;
    QPointF direction_;
    bool move_ = false;
public:
    void setSpeed(double);
    void setDirection(const QPointF&);
    double getSpeed() const;
    const QPointF& getDirection() const;
    void setMove(bool move);
    bool isMoving();
    void move();
};
