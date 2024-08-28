#pragma once

#include "TreeNode.h"
#include <iostream>
#include "Color.h"

struct AVLTreeNode {
    AVLTreeNode* left;
    AVLTreeNode* right;
    const int value;
    int count;
    int height;

    TreeNode* vertex;

    AVLTreeNode(int value, sf::Vector2f position, float radius, int thickness, sf::Color fillColor, sf::Color textColor, sf::Font* font);
    void updateValues();
    int balanceFactor();

    AVLTreeNode* left_rotate();
    AVLTreeNode* right_rotate();
};

class AVLGraph
{
public:
    int _size;
    AVLTreeNode* root;

    sf::Font* font;
    float radius; int thickness;
    sf::Color fillColor, textColor;
    sf::Vector2f startposition;
    std::vector<sf::RectangleShape> Edgeslist;
    void balance(std::vector<AVLTreeNode**> path);
    void display(AVLTreeNode* cur, int depth = 0, int state = 0);

public:
    AVLGraph(sf::Vector2f startPosition, float radius, int thickness, colorTheme theme, sf::Font* font);
    ~AVLGraph();

    void insert(int value);
    bool Delete(int value);

    void clear();
    bool empty() const;
    int size() const;
    sf::RectangleShape getEdgeLine(sf::Vector2f startPosition, sf::Vector2f endPosition);
    sf::RectangleShape getEdgeLine2(sf::Vector2f startPosition, sf::Vector2f endPosition);
    void updatePosition(AVLTreeNode*& root, int level);
    void update();

    void render(sf::RenderTarget& target);
};

