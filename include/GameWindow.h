#pragma once
#include <QMainWindow>
#include "View.h"
#include "Player.h"
#include "Model.h"

class GameWindow : public QMainWindow {
public:
    static const int size = 400;
    GameWindow();
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void updateFrame();
private:
    View* view;
    std::unique_ptr<Model> model;
};
