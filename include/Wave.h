#pragma once
#include <vector>

struct Wave {
    int id;
    int delay;
    int minAmount;
    std::vector<int> enemiesId;
};