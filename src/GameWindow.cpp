#include "GameWindow.h"
#include <QGraphicsLineItem>

GameWindow::GameWindow() : QMainWindow(), view(new QGraphicsView(this))
{
    resize(600, 600);
    auto* scene = new QGraphicsScene(view->contentsRect(), this);
    view->scale(1, -1);
    view->setScene(scene);
    setCentralWidget(view);
}
