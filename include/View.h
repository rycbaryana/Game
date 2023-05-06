#pragma once
#include <QGraphicsView>

class View : public QGraphicsView {
public:
    explicit View(QWidget* parent = nullptr);
    void wheelEvent(QWheelEvent* event) override;

    QGraphicsScene* scene;
};
