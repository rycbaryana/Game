#pragma once
#include <QGraphicsView>
#include "Player.h"
#include "XpBar.h"
#include "KillCounter.h"

class PlayerHUD : public QGraphicsView {
    Q_OBJECT
public:
    explicit PlayerHUD(Player* player, QWidget* parent = nullptr);
    QGraphicsTextItem* waveCounter;
    KillCounter* killCounter;
    XpBar* xp;
};
