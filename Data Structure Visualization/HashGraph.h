#pragma once

#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "Color.h"
#include "HashNode.h"

struct Hash
{
	int size = 0, capacity = 50;
	std::vector<int> hashArr;
	
	int hashCode(int x);
	bool Insert(int x);
	bool Delete(int x);
	int Search(int x);
};

class HashGraph
{
public:
	sf::Font* font;
	float length; int thickness;
	sf::Color fillColor, borderColor, textColor;
	Hash* hash;
	sf::Vector2f startPosition;
public:
	std::vector<HashNode*> Nodes;


public:
	HashGraph(sf::Vector2f startPosition, sf::Font* font, Hash* hash, colorTheme theme, float radius, int thickness);
	~HashGraph();
	void resetAnimation();
	void InsertAnimation(sf::RenderTarget& target, int value);
	void update();
	void render(sf::RenderTarget& target);
};


