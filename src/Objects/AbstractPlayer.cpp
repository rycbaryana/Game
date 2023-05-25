#include "AbstractPlayer.h"

int AbstractPlayer::getXp() const {
    return xp_;
}

void AbstractPlayer::addXp(int xp) {
    xp_ += xp;
    if (xp_ >= neededXp[level_]) {
        xp_ -= neededXp[level_];
        ++level_;
    }
}

int AbstractPlayer::getLevel() const {
    return level_;
}

AbstractPlayer::AbstractPlayer() : Creature(100), neededXp(maxLevel + 1) {
    int inc = 10;
    neededXp[1] = 5;
    for (int i = 2; i <= 80; ++i) {
        if ((i - 1) % 20 == 0) {
            inc += 3;
        }
        neededXp[i] = neededXp[i - 1] + inc;
    }
}
