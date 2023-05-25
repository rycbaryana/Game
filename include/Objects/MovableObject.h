#pragma once
#include "GameObject.h"
#include "AnimationManager.h"

class MovableObject : public GameObject {
protected:
    MovableObject();
    double speed_;
    QPointF direction_;
    QPointF sightDirection_;
    AnimationManager animation_;
public:
    void setAnimation(AnimationManager& anim);
    void setSpeed(double);
    void setDirection(const QPointF&);
    double getSpeed() const;
    const QPointF& getSightDirection() const;
    const QPointF& getDirection() const;
    void move();
    void move(double speed, const QPointF& direction, bool animate = true);
};
