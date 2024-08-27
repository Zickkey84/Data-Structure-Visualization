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
    return { v.x / len, v.y / len };
}

inline std::string charToString(char a) {
    std::string res;
    res.push_back(a);
    return res;
}

inline void generateRandomString(int x, std::vector<std::string>& v) {
    while (x--) {
        int k = rand() % 6 + 1;
        std::string characters = "abcdefghijklmnopqrstuvwxyz";
        std::string randomString;
        for (int i = 0; i < k; i++) {
            randomString += characters[std::rand() % characters.size()];
        }
        v.push_back(randomString);
    }
}