#include "PlayerHUD.h"
#include "XpBar.h"

PlayerHUD::PlayerHUD(Player* player, QWidget* parent) : QGraphicsView(parent) {
    int size = GameWindow::size;
    auto* scene = new QGraphicsScene(0, 0, 2 * size, 75, this);
    auto* xp = new XpBar(player);
    scene->addItem(xp);


    setScene(scene);
    setFrameShape(QFrame::NoFrame);
    QPalette pal;
    pal.setColor(QPalette::Base, Qt::transparent);
    setPalette(pal);
}
