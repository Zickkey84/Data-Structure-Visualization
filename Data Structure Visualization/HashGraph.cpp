#include "HashGraph.h"


HashGraph::HashGraph(sf::Vector2f startPosition, sf::Font* font, Hash* hash, colorTheme theme, float length, int thickness)
{
	this->length = length;
	this->thickness = thickness;
	this->startPosition = startPosition;
	this->font = font;
	this->hash = hash;
	this->fillColor = HASH::color[theme][HASH::Normal].fillColor;
	this->borderColor = HASH::color[theme][HASH::Normal].outlineColor;
	this->textColor = HASH::color[theme][HASH::Normal].outlineColor;
}

HashGraph::~HashGraph()
{
	auto it = this->Nodes.begin();
	for (it; it != Nodes.end(); it++) delete* it;
}

void HashGraph::update() {
	int x = this->Nodes.size(); 
	while (x--) this->Nodes.pop_back();
	for (int i = 0; i < (*this->hash).size; i++) {
		if (i == 0) {
			this->Nodes.push_back(new HashNode(this->startPosition, this->length, this->thickness,
				this->fillColor, this->textColor, (*this->hash).hashArr[i], this->font));
		}
		else if (i % 10 != 0)
		{
			this->Nodes.push_back(new HashNode(this->Nodes[i - 1]->getSquarePosition() + sf::Vector2f(length * 2, 0), this->length, this->thickness,
				this->fillColor, this->textColor, (*this->hash).hashArr[i], this->font));
		}
		else {
			this->Nodes.push_back(new HashNode(this->Nodes[i - 10]->getSquarePosition() + sf::Vector2f(0, length * 2), this->length, this->thickness,
				this->fillColor, this->textColor, (*this->hash).hashArr[i], this->font));
		}
		this->Nodes[i]->setVariableText(std::to_string(i));
	}
}

void HashGraph::resetAnimation()
{
	for (int i = 0; i < (*this->hash).size; i++) {
		this->Nodes[i]->setHighlight(this->borderColor, this->thickness);
	}
}

void HashGraph::InsertAnimation(sf::RenderTarget& target, int value)
{

}

void HashGraph::render(sf::RenderTarget& target) {
	for (int i = 0; i < (*this->hash).size; i++) {
		this->Nodes[i]->render(target);
	}
}
