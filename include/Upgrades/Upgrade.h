#pragma once
#include <QString>

class Upgrade {
protected:
    int level_ = 0;
    virtual void levelUp() = 0;
    virtual QString description() const = 0;
};