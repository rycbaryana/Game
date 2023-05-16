#pragma once
#include <QGraphicsView>
#include "Player.h"
#include "XpBar.h"

class PlayerHUD : public QGraphicsView {
public:
    explicit PlayerHUD(Player* player, QWidget* parent = nullptr);
    QGraphicsTextItem* waveCounter;
    XpBar* xp;
};
