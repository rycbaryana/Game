#pragma once
#include <QGraphicsView>
#include "PlayerHUD.h"

class View : public QGraphicsView {
public:
    explicit View(QWidget* parent = nullptr);
    void wheelEvent(QWheelEvent* event) override;

    QGraphicsScene* scene;
    PlayerHUD* hud;
};
