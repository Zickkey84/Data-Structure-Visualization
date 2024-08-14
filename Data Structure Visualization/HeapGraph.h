#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "TreeNode.h"
#include "Color.h"
#include <math.h>
struct Heap {
	std::vector<int> arr;
	int n = 0, capacity = 31;

	void insert(int key);
	bool del(int key);
	int left(int i);
	int right(int i);
	int parent(int i);
	int getRoot();
	void heapify(int i);
	void makeHeap();
};

class HeapGraph
{
private:
	sf::Font *font; 
	float radius; int thickness;
	sf::Color fillColor, textColor;
	std::vector<TreeNode*> vertices;
	std::vector<sf::RectangleShape*> edges;
	Heap* arrHeap;
	sf::Vector2f startPosition;

public:		
	HeapGraph(sf::Vector2f startPosition, sf::Font* font, Heap* heap, colorTheme theme, float radius, int thickness);
	~HeapGraph();

	sf::RectangleShape getEdgeLine(sf::Vector2f startPosition, sf::Vector2f endPosition);
	void update();
	void render(sf::RenderTarget& target);
};

