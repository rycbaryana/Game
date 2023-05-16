#include "UpgradeOption.h"
#include <QPainter>
#include "GameWindow.h"

UpgradeOption::UpgradeOption(Upgrade* upgrade, QGraphicsItem* parent) : upgrade_(upgrade), QGraphicsItem(parent) { }

void UpgradeOption::paint(
    QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget
) {
    painter->setBrush(Qt::red);
    painter->drawRect(boundingRect());
    painter->drawText(boundingRect(), upgrade_->levelDescription[upgrade_->getLevel()]);
}

QRectF UpgradeOption::boundingRect() const {
    return QRectF(-100, -50, 200, 100);
}

void UpgradeOption::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    upgrade_->levelUp();
    parentItem()->hide();
    for (auto* child : parentItem()->childItems()) {
        delete child;
    }
}

