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

Item* Enemy::dropXp() {
    return new Item(pos_, xp_);
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
    painter->setPen({Qt::red, 1});
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawRect(boundingRect());
}

QRectF Enemy::boundingRect() const {
    return QRectF(-10, -10, 20, 20);
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
    xp_ = static_cast<ItemType>(stats[3]);
}
