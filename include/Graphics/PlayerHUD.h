#pragma once
#include <QGraphicsView>
#include "Player.h"

class PlayerHUD : QGraphicsView {
public:
    explicit PlayerHUD(Player* player, QWidget* parent = nullptr);
};
