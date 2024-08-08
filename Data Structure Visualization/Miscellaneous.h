#pragma once

#include <iostream>
#include <vector>
#include <random>

inline std::vector<int> generateRandomArray(int n) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distrib(0, 999);

    std::vector<int> randomArray;
    for (int i = 0; i < n; ++i) {
        randomArray.push_back(distrib(gen));
    }

    return randomArray;
}