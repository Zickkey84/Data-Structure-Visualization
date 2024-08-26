#pragma once

#include <iostream>
#include <vector>
#include <random>
#include "HashGraph.h"

inline std::vector<int> generateRandomArray(int n) {
    std::vector<int> randomArray;
    for (int i = 0; i < n; i++) {
        randomArray.push_back(rand() % 1000);
    }
    return randomArray;
}

inline Hash generateRandomHash(int x) {

}