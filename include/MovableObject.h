#pragma once
#include "GameObject.h"

class MovableObject : public GameObject {
protected:
    MovableObject();
    double speed_;
    QPointF direction_;
public:
    void setSpeed(double);
    void setDirection(const QPointF&);
    double getSpeed() const;
    const QPointF& getDirection() const;
    void move();
    void move(double speed, const QPointF& direction);
};
