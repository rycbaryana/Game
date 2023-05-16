#include "UpgradeMenu.h"
#include "UpgradeOption.h"
#include "GameWindow.h"
#include <QPainter>

UpgradeMenu::UpgradeMenu(Player* player, QGraphicsScene* scene) : player_(player) {
    setPos(scene->width() / 2, scene->height() / 2);
    scene->addItem(this);
    hide();
}

void UpgradeMenu::addUpgrades() {
    auto* opt1 = new UpgradeOption(player_->getWeapons().front().get(), this);
    auto* opt2 = new UpgradeOption(player_->getWeapons().front().get(), this);
    auto* opt3 = new UpgradeOption(player_->getWeapons().front().get(), this);
    opt1->setPos(0, -100);
    opt3->setPos(0, 100);
    connect(opt1, &QObject::destroyed, [this]{emit unpause();});
    connect(opt2, &QObject::destroyed, [this]{emit unpause();});
    connect(opt3, &QObject::destroyed, [this]{emit unpause();});
}

void UpgradeMenu::paint(
    QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget
) {
    painter->drawRect(boundingRect());
}

QRectF UpgradeMenu::boundingRect() const {
    return QRectF(-width / 2, -height / 2, width, height);
}

void UpgradeMenu::showMenu() {
    addUpgrades();
    show();
    emit pause();
}
