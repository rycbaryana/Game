#pragma once
#include <QGraphicsItem>
#include "Upgrade.h"

class UpgradeOption : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    explicit UpgradeOption(Upgrade* upgrade, QGraphicsItem* parent);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    Upgrade* getUpgrade() const;
private:
    Upgrade* upgrade_;
    bool hovered_ = false;
signals:
    void unpause();
};
