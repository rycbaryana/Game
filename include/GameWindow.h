#pragma once
#include <QMainWindow>
#include <QGraphicsView>

class GameWindow : public QMainWindow
{
public:
    GameWindow();
private:
    QGraphicsView* view;
};
