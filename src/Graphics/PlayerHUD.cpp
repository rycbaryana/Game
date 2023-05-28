#include "PlayerHUD.h"

PlayerHUD::PlayerHUD(Player* player, QWidget* parent) : QGraphicsView(parent) {
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    int width;
    int height;
    width = parent->width();
    height = parent->height();
    resize(width, height);
    auto* scene = new QGraphicsScene(0, 0, width, height, this);
    xp = new XpBar(player, width);
    waveCounter = new QGraphicsTextItem(QObject::tr("Wave 0"));
    waveCounter->setDefaultTextColor(Qt::gray);
    killCounter = new KillCounter(player);
    scene->addItem(xp);
    scene->addItem(waveCounter);
    scene->addItem(killCounter);

    setScene(scene);
    setFrameShape(QFrame::NoFrame);
    QPalette pal;
    pal.setColor(QPalette::Base, Qt::transparent);
    setPalette(pal);
}
