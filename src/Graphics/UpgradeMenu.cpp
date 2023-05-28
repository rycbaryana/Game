#include "UpgradeMenu.h"
#include "UpgradeOption.h"
#include "GameWindow.h"
#include <QPainter>
#include <QRandomGenerator>

UpgradeMenu::UpgradeMenu(Player* player, QGraphicsScene* scene) : player_(player) {
    setPos(scene->width() / 2, scene->height() / 2);
    scene->addItem(this);
    hide();
}

void UpgradeMenu::generateUpgrades() {
    int padding = 10;
    auto upgrades = player_->getPossibleUpgrades();
    while (options_.size() < 3 && !upgrades.empty()) {
        int upgradeIndex = QRandomGenerator::global()->bounded(static_cast<int>(upgrades.size()));
        auto* option = new UpgradeOption(upgrades[upgradeIndex], this);
        option->setPos(padding, -option->boundingRect().height() + option->boundingRect().height() * options_.size());
        options_.push_back(option);
        erase_if(upgrades, [option](auto* obj) {return option->getUpgrade() == obj;});
        connect(option, &UpgradeOption::unpause, [this]{
            deleteUpgrades();
            emit unpause();
        });
    }
}

void UpgradeMenu::paint(
    QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget
) {
    painter->setBrush(QColor(75, 79, 116));
    painter->setPen({QColor(255, 204, 0), 3});
    painter->drawRect(boundingRect());
    QString lvlUp = tr("Level Up!");
    QString text = tr("Choose one upgrade");
    painter->setFont(QFont(painter->font().family(), 15));
    painter->setPen({Qt::black, 1});
    painter->drawText(-painter->fontMetrics().horizontalAdvance(lvlUp) / 2,-height / 2 + painter->fontMetrics().height(), lvlUp);
    painter->drawText(-painter->fontMetrics().horizontalAdvance(text) / 2,height / 2 - painter->fontMetrics().height(), text);
}

QRectF UpgradeMenu::boundingRect() const {
    return QRectF(-width / 2, -height / 2, width, height);
}

void UpgradeMenu::showMenu() {
    generateUpgrades();
    if (options_.empty()) {
        return ;
    }
    show();
    emit pause();
}

void UpgradeMenu::deleteUpgrades() {
    for (auto* option : options_) {
        delete option;
    }
    options_.clear();
}
