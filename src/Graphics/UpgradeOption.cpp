#include "UpgradeOption.h"
#include <QPainter>
#include "GameWindow.h"

UpgradeOption::UpgradeOption(Upgrade* upgrade, QGraphicsItem* parent)
    : upgrade_(upgrade), QGraphicsItem(parent) {
    setAcceptHoverEvents(true);
}

void UpgradeOption::paint(
    QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget
) {
    painter->setFont(QFont(painter->font().family(), 15));
    painter->setBrush(QColor(139, 139, 139));
    painter->drawRect(boundingRect());
    QPixmap icon;
    if (upgrade_->sprite.width() > upgrade_->sprite.height()) {
        icon = upgrade_->sprite.scaledToWidth(48);
    } else {
        icon = upgrade_->sprite.scaledToHeight(48);
    }
    painter->drawPixmap(boundingRect().topLeft() + QPointF((48 - icon.width()) / 2, (48 - icon.height()) / 2), icon);
    painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/frame_small.png"));
    if (hovered_) {
        painter->drawPixmap(boundingRect().width() / 2 - 32 - 10, -16, QPixmap(":/arrow.png").scaled(32, 32).transformed(QTransform::fromScale(-1, 1)));
    }
    painter->drawText(
        boundingRect().topLeft() + QPointF(icon.width() * 1.5, painter->fontMetrics().height()),
        upgrade_->name
    );
    QString status = upgrade_->getLevel() == 0 ? tr("New!") : tr("lvl %1").arg(upgrade_->getLevel() + 1);
    painter->save();
    if (upgrade_->getLevel() == 0) painter->setPen(Qt::yellow);
    painter->drawText(boundingRect().topLeft() + QPointF(icon.width() * 2 + painter->fontMetrics().horizontalAdvance(upgrade_->name), painter->fontMetrics().height()), status);
    painter->restore();
    painter->drawText(
        boundingRect().topLeft() + QPointF(2, 48 + painter->fontMetrics().height()),
        upgrade_->levelDescription[upgrade_->getLevel()]
    );
}

QRectF UpgradeOption::boundingRect() const {
    return QRectF(
        -parentItem()->boundingRect().width() / 2, -50, parentItem()->boundingRect().width() - 20, 100
    );
}

void UpgradeOption::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    upgrade_->levelUp();
    parentItem()->hide();
    emit unpause();
}

void UpgradeOption::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    hovered_ = true;
    update();
}

void UpgradeOption::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    hovered_ = false;
    update();
}

Upgrade* UpgradeOption::getUpgrade() const {
    return upgrade_;
}
