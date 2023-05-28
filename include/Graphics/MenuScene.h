#pragma once
#include <QGraphicsScene>
#include <QPushButton>
#include <QResizeEvent>

class MenuScene : public QGraphicsScene {
    Q_OBJECT
public:
    MenuScene(QWidget* parent);
    QPushButton* startButton;
    QPushButton* soundButton;
    QPushButton* languageButton;
    QPushButton* exitButton;
    void drawBackground(QPainter* painter, const QRectF& rect) override;
signals:
    void start();
    void exit();
};
