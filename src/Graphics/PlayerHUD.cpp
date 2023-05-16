#include "PlayerHUD.h"

PlayerHUD::PlayerHUD(Player* player, QWidget* parent) : QGraphicsView(parent) {
    int width;
    int height;
    width = parent->width();
    height = parent->height();
    resize(width, height);
    auto* scene = new QGraphicsScene(0, 0, width, height, this);
    xp = new XpBar(player, width);
    waveCounter = new QGraphicsTextItem("Wave 0");
    scene->addItem(xp);
    scene->addItem(waveCounter);


    setScene(scene);
    setFrameShape(QFrame::NoFrame);
    QPalette pal;
    pal.setColor(QPalette::Base, Qt::transparent);
    setPalette(pal);
}
