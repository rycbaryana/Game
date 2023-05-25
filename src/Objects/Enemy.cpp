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
    painter->drawPixmap(boundingRect().topLeft(), animation_.getCurrentFrame().scaled(40, 40));
}

QRectF Enemy::boundingRect() const {
    return QRectF(-20, -20, 40, 40);
}

Enemy::Enemy(int id, const QPointF& pos) : timer_(std::make_unique<QDeadlineTimer>()), id_(id){
    setPosition(pos);
}

void Enemy::setStats(const std::vector<double>& stats) {
    if (stats.size() != 4) return;
    baseDamage_ = static_cast<int>(stats[0]);
    maxHealth_ = static_cast<int>(stats[1]);
    health_ = maxHealth_;
    speed_ = stats[2];
    xp_ = static_cast<int>(stats[3]);

    AnimationManager anim(QPixmap(QString(":/enemy_%1.png").arg(id_)), 4, speed_, 25, 23, 0);
    setAnimation(anim);
}
