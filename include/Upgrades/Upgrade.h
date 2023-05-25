#pragma once
#include <QString>
#include <QPixmap>
#include "AbstractPlayer.h"

class Upgrade {
public:
    int maxLevel;
    virtual void levelUp() = 0;
    int getLevel() const {return level_;};
    std::vector<QString> levelDescription;
    QString name;
    QPixmap sprite;
protected:
    int level_ = 0;
    AbstractPlayer* player_;
};