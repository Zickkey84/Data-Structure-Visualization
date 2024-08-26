#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <set>
#include <vector>

class HashNode
{
private:
    sf::RectangleShape square;
    sf::Color fillColor, textColor;
    sf::Text text, textVariable;
    sf::Font* font;
    std::set <std::string> variableList;
    int value;
public:
    HashNode(sf::Vector2f position, float length, int borderThickness,
        sf::Color fillColor, sf::Color textColor, int value, sf::Font* font);

public:
    // Getters
    sf::Vector2f getSquarePosition();
    int getValue();
    std::string getText();
    // Setters
    void setPosition(sf::Vector2f newPosition);
    void setColor(sf::Color newVertexColor, sf::Color newTextColor);
    void setBorderColor(sf::Color newColor);
    void setValue(int newValue);
    void setText(std::string newText);
    void setVariableText(std::string text);
    void setHighlight(sf::Color highlightColor, float borderThickness);
public:
    // void render(sf::RenderTarget& targer, const float dt, std::vector<Animation> animations);
    void render(sf::RenderTarget& target);
};

