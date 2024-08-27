#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <set>
#include <vector>

class TreeNode
{
private:
	sf::CircleShape vertex;
	sf::Color vertexColor, textColor;
	sf::Text text, textVariable;
	sf::Font *font;
    std::set <std::string> variableList;
	int value;
public:
	TreeNode(sf::Vector2f position, float radius, int borderThickness,
        sf::Color vertexColor, sf::Color textColor, int value, sf::Font *font);
   
public:
    // Getters
    sf::Vector2f getVertexPosition();
    std::vector <std::string> getVariables();
    int getValue();
    std::string getVariableString();

    // Setters
    void setPosition(sf::Vector2f newPosition);
    void setSize(float newPercent);
    void setColor(sf::Color newVertexColor, sf::Color newTextColor);
    void setFillColor(sf::Color newVertexColor, sf::Color newTextColor);
    void setValue(int newValue);
    void setLeftChild(int newLeftChild);
    void setRightChild(int newRightChild);

public:
    void insertVariable(std::string variable);
    void deleteVariable(std::string variable);
    void insertVariable(std::vector <std::string> variables);
    void deleteVariable(std::vector <std::string> variables);

public:
   // void render(sf::RenderTarget& targer, const float dt, std::vector<Animation> animations);
   void render(sf::RenderTarget& target);
};
