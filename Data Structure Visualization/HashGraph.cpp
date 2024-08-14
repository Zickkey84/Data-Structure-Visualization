#include "HashGraph.h"


HashGraph::HashGraph(sf::Vector2f startPosition, sf::Font* font, Hash* hash, colorTheme theme, float length, int thickness)
{
	this->length = length;
	this->thickness = thickness;
	this->startPosition = startPosition;
	this->font = font;
	this->hash = hash;
	this->fillColor = HASH::color[theme][HASH::Normal].fillColor;
	this->textColor = HASH::color[theme][HASH::Normal].outlineColor;
}

HashGraph::~HashGraph()
{
	auto it = this->Nodes.begin();
	for (it; it != Nodes.end(); it++) delete* it;
}

