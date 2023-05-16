#pragma once
#include <QString>

class Upgrade {
public:
    virtual void levelUp() = 0;
    int getLevel() const {return level_;};

    std::vector<QString> levelDescription;
protected:
    int level_ = 0;
};