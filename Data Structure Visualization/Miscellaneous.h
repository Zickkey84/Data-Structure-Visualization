#pragma once

#include <iostream>
#include <vector>
#include <random>
#include "HashGraph.h"
#include "SFML/Graphics.hpp"

inline std::vector<int> generateRandomArray(int n) {
    std::vector<int> randomArray;
    for (int i = 0; i < n; i++) {
        randomArray.push_back(rand() % 1000);
    }
    return randomArray;
}

inline float length(sf::Vector2f v) { return round(sqrt(v.x * v.x + v.y * v.y)); }

inline sf::Vector2f normalize(sf::Vector2f v) {
    float len = sqrt(v.x * v.x + v.y * v.y);
    return { round(v.x / len), round(v.y / len) };
}

