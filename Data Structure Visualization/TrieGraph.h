#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "TreeNode.h"
#include "Color.h"
#include "Miscellaneous.h"
#include <functional>

class TrieGraph
{
public:
    int maxSize;
    sf::Font* font;
    float radius; int thickness;
    sf::Color fillColor, textColor;
    int root;
    sf::Vector2f startPosition;
    std::map <int, TreeNode*> nodes;
    std::map <int, std::pair<sf::RectangleShape, sf::Text>> EdgeList;
    TrieGraph(sf::Vector2f startPosition, float radius, int thickness, sf::Font* font, colorTheme theme, int maxSize);
    ~TrieGraph();
    int getParent(int id);
    int getMexID();
    int findEdge(int id, std::string weight);
    int countString();
    void clear();
    std::pair <sf::RectangleShape, sf::Text> getEdgeLine(sf::Vector2f startPosition, sf::Vector2f endPosition, std::string weight);

    void DFS(int id, int height, std::vector <std::pair<int, int> >& tour);
    void arrangeTrieTree();

    bool insertString(std::string str);
    bool deleteString(std::string str);
    bool searchString(std::string str);

    void update();
    void render(sf::RenderTarget& target);
};

