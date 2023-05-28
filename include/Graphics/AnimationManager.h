#pragma once
#include <QPixmap>

class AnimationManager {
    std::vector<QPixmap> frames_;
    int currentState_{0};
    int width_;
    int height_;
    int gap_;
    int speed_;
public:
    AnimationManager(const QPixmap& frames, int count, int speed, int width, int height, int gap);
    AnimationManager(const QPixmap& sprite);
    AnimationManager() = default;
    const QPixmap& getCurrentFrame() const;
    bool isActive() const ;
    void nextFrame();
};
