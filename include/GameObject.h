#pragma once
#include <QPointF>
class GameObject {
protected:
    GameObject();
    explicit GameObject(const QPointF& pos);
    QPointF pos_;
public:
    void setPosition(double x, double y);
    const QPointF& getPos() const;
};
