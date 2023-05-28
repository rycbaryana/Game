#include "Enemy.h"
#include <QGraphicsScene>
#include <QPainter>

int Enemy::getDamage() const {
    return baseDamage_;
}

void Enemy::attack(Creature* target) {
    if (!timer_->hasExpired()) return;
    target->damage(baseDamage_);
    timer_->setRemainingTime(delay_);
}

XpItem* Enemy::dropXp() {
    auto* xp = new XpItem(pos_, xp_);
    xp->setZValue(-1);
    return xp;
}

Enemy::~Enemy() {
    scene()->addItem(dropXp());
}

int Enemy::getId() const {
    return id_;
}

void Enemy::paint(
    QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget
) {
    painter->scale(1, -1);
    double scaleFactor = 1.75;
    double x = (sightDirection_.x() >= 0 ? -1 : 1);
    painter->drawPixmap(boundingRect().topLeft(), animation_.getCurrentFrame().scaled(scaleFactor * width_, scaleFactor * height_).transformed(QTransform::fromScale(x, 1)));
}

QRectF Enemy::boundingRect() const {
    return QRectF(-width_ / 2.0, -height_/2.0, width_, height_);
}

Enemy::Enemy(int id, const QPointF& pos) : timer_(std::make_unique<QDeadlineTimer>()), id_(id){
    setPosition(pos);
}

void Enemy::setStats(const std::vector<double>& stats) {
    if (stats.size() != 7) return;
    baseDamage_ = static_cast<int>(stats[0]);
    maxHealth_ = static_cast<int>(stats[1]);
    health_ = maxHealth_;
    speed_ = stats[2];
    xp_ = static_cast<int>(stats[3]);
    width_ = static_cast<int>(stats[4]);
    height_ = static_cast<int>(stats[5]);

    AnimationManager anim(QPixmap(QString(":/enemy_%1.png").arg(id_)), 4, speed_, width_, height_, stats[6]);
    setAnimation(anim);
}
