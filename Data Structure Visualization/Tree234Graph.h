#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Color.h"
#include <set>
#include "Miscellaneous.h"

struct Node234 {
    sf::RectangleShape rect;
    int value;
    sf::Font* font;
    sf::Vector2f position;
    sf::Color fillColor, textColor;
    sf::Text valueText;
    float size, thickness;
    Node234(sf::Vector2f position, int value , sf::Font* font, sf::Color fillColor, sf::Color textColor, float size, float thickness);

    //Setters
    void setPosition(float newX, float newY);
    void setPosition(sf::Vector2f newPosition);
    void setSize(float newPercent);
    void setValue(int newValue);

    //Getters
    sf::Vector2f getPosition();
    int getValue();
    void render(sf::RenderTarget& target);
};

struct Group234 {
    std::vector <int> nodes;
    std::vector <int> listEdge;

    float size, thickness;
    Group234(std::vector <int> nodes, float size, float thickness);

    void setEdge(int pos, int id);
    bool isLeaf();
    sf::Vector2f getSize();
};

class Tree234Graph
{

public:
    sf::Font* font;
    std::map <int, Node234*> nodes;
    std::map <int, Group234*> groups;
    std::vector<sf::RectangleShape> Edgeslist;
    int root;
    sf::Color fillColor, textColor;
    float size; float thickness;
    sf::Vector2f startPosition;

    Tree234Graph(sf::Vector2f startPosition, sf::Font* font, colorTheme theme, float size, float thickness);
    ~Tree234Graph();
    int getGroupID(int id);
    int getParentGroup(int id);
    int getMexNodeID();
    int getMexGroupID();
    std::vector <int> getMexNodeIDs(int size);
    std::vector <int> getMexGroupIDs(int size);
    sf::RectangleShape getEdgeLine(sf::Vector2f startPosition, sf::Vector2f endPosition);
    sf::Vector2f getPosition(int idGroup);
    std::vector <int> getEdges(int idGroup);
    sf::Vector2f getStartEdgePosition(int idGroup, int pos, sf::Vector2f curPosition);
    sf::Vector2f getEndEdgePosition(int idGroup, sf::Vector2f curPosition);
   
    void clear();
    void DFS(int id, int height, std::vector <std::vector <std::vector <int> > >& tour);
    void arrangeBTree();
    void setPosition(int idGroup, sf::Vector2f position);
    void setEdge(int idGroup, int pos, int id);

    void insertNode(int idGroup, int idNode);
    bool deleteNode(int idGroup, int idNode);

    void insert(int value);

    int findNodePos(int idGroup, int value);
    int findNode(int idGroup, int value);
    int findEdge(int idGroup, int value);
    int findEdgePos(int idGroup, int value);

    void update();
    void render(sf::RenderTarget& target);
};

