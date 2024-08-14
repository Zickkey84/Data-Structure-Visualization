#include "HeapGraph.h"



HeapGraph::HeapGraph(sf::Vector2f startPosition, sf::Font* font, Heap* heap, colorTheme theme, float radius, int thickness)
{
	this->radius = radius;
	this->thickness = thickness;
	this->startPosition = startPosition;
	this->font = font;
	this->arrHeap = heap;
	this->fillColor = HEAP::color[theme][HEAP::Normal].fillColor;
	this->textColor = HEAP::color[theme][HEAP::Normal].outlineColor;
}

HeapGraph::~HeapGraph()
{
	auto it = this->vertices.begin();
	for (it; it != vertices.end(); it++) delete* it;

	auto it2 = this->edges.begin();
	for (it2; it2 != edges.end(); it2++) delete* it2;
}

sf::RectangleShape HeapGraph::getEdgeLine(sf::Vector2f startPosition, sf::Vector2f endPosition) {
	sf::Vector2f diff = endPosition - startPosition;
	float lengthDiff = sqrt(diff.x * diff.x + diff.y * diff.y);
	if (lengthDiff < 2.f * (this->radius + this->thickness)) {
		return sf::RectangleShape();
	}
	sf::RectangleShape line(sf::Vector2f((lengthDiff - 2.f * (this->radius + (float)this->thickness)), this->thickness));
	line.setOrigin(0, (float) this->thickness / 2.f);
	line.setRotation(atan2(diff.y, diff.x) * 180.f / 3.14159265);
	line.setPosition(startPosition + sf::Vector2f(diff.x / lengthDiff, diff.y / lengthDiff) * (this->radius + (float)this->thickness));
	line.setFillColor(this->textColor);
	return line;
}

void HeapGraph::update()
{
	int x = this->vertices.size();
	while (x--) this->vertices.pop_back();
	for (int i = 0; i < (*this->arrHeap).n; i++) {
		if (i == 0) {
			this->vertices.push_back(new TreeNode(this->startPosition, this->radius, this->thickness,
				this->fillColor, this->textColor, (*this->arrHeap).arr[i], this->font));
		}
		else if (i % 2 == 1)
		{
			this->vertices.push_back(new TreeNode(this->vertices[(i - 1) / 2]->getVertexPosition() + sf::Vector2f(-200.f / pow(2, (int)log2(i + 1) - 1), 100.f), this->radius, this->thickness,
				this->fillColor, this->textColor, (*this->arrHeap).arr[i], this->font));
		}
		else {
			this->vertices.push_back(new TreeNode(this->vertices[(i - 1) / 2]->getVertexPosition() + sf::Vector2f(200.f / pow(2, (int)log2(i + 1) - 1), 100.f), this->radius, this->thickness,
				this->fillColor, this->textColor, (*this->arrHeap).arr[i], this->font));
		}
	}
	x = this->edges.size();
	while (x--) this->edges.pop_back();
	for (int i = 0; i < (*this->arrHeap).n; i++) {
		if (2 * i + 1 < (*this->arrHeap).n) {
			sf::RectangleShape* x = new sf::RectangleShape();
			*x = this->getEdgeLine(this->vertices[i]->getVertexPosition(), this->vertices[2 * i + 1]->getVertexPosition());
			this->edges.push_back(x);
		}
		if (2 * i + 2 < (*this->arrHeap).n) {
		sf::RectangleShape* x = new sf::RectangleShape();
		*x = this->getEdgeLine(this->vertices[i]->getVertexPosition(), this->vertices[2 * i + 2]->getVertexPosition());
		this->edges.push_back(x);
		}
	}
}

void HeapGraph::render(sf::RenderTarget& target)
{
	for (int i = 0; i < (*this->arrHeap).n; i++) {
		this->vertices[i]->render(target);
		if (i < (*this->arrHeap).n - 1) {
			target.draw(*this->edges[i]);
		}
	}
}


