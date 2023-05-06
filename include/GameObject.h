#pragma once
#include <QPointF>
class GameObject {
protected:
    QPointF pos_;
public:
    void setPosition(double x, double y);
    const QPointF& getPos() const;
};
