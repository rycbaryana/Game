#pragma once
#include <QGraphicsItem>
#include "Player.h"

class UpgradeMenu : public QObject, public QGraphicsItem {
    int width = 400;
    int height = 400;
    Q_OBJECT
public:
    explicit UpgradeMenu(Player* player, QGraphicsScene* scene);
    void addUpgrades();
    void showMenu();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
private:
    Player* player_;
signals:
    void pause();
    void unpause();
};
