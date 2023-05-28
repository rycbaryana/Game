#pragma once
#include <QGraphicsItem>
#include "Player.h"
#include "UpgradeOption.h"

class UpgradeMenu : public QObject, public QGraphicsItem {
    int width = 600;
    int height = 500;
    Q_OBJECT
public:
    explicit UpgradeMenu(Player* player, QGraphicsScene* scene);
    void generateUpgrades();
    void showMenu();
    void deleteUpgrades();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
private:
    std::vector<UpgradeOption*> options_;
    Player* player_;
signals:
    void pause();
    void unpause();
};
