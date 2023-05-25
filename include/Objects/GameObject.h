#pragma once
#include <QPointF>
#include <QGraphicsItem>
class GameObject : public QGraphicsItem {
protected:
    GameObject();
    explicit GameObject(const QPointF& pos);
    QPointF pos_;
    QPixmap sprite_;
public:
    void setPosition(double x, double y);
    void setPosition(const QPointF& pos);
    const QPointF& getPos() const;
};

double vecLength(const QPointF& vec);

template<class T>
std::vector<T*> getCollision(GameObject* whoCollide) {
    auto allCollisions = whoCollide->collidingItems();
    std::vector<T*> collision;
    for (auto item : allCollisions) {
        auto object = dynamic_cast<T*>(item);
        if (object != nullptr) {
            collision.push_back(object);
        }
    }
    return collision;
}
