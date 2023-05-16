#pragma once
#include <QGraphicsItem>
#include "Upgrade.h"

class UpgradeOption : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    explicit UpgradeOption(Upgrade* upgrade, QGraphicsItem* parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    Upgrade* upgrade_;
};
