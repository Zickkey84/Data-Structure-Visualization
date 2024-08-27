#include "TrieGraph.h"

TrieGraph::TrieGraph(sf::Vector2f startPosition, float radius, int thickness, sf::Font* font, colorTheme theme, int maxSize)
{
	this->maxSize = maxSize;
	nodes.clear();
	EdgeList.clear();
	this->radius = radius;
	this->thickness = thickness;
	this->startPosition = startPosition;
	this->font = font;
	this->fillColor = HEAP::color[theme][HEAP::Normal].fillColor;
	this->textColor = HEAP::color[theme][HEAP::Normal].outlineColor;
	this->root = 0;
	nodes[0] = new TreeNode(startPosition, radius, thickness, fillColor, textColor, "", font);
}

TrieGraph::~TrieGraph()
{
	for (auto it : nodes) delete it.second;
	nodes.clear();
	EdgeList.clear();
}

int TrieGraph::getParent(int id)
{
	if (id == -1) {
		return -1;
	}
	for (auto x = nodes.begin(); x != nodes.end(); x++) {
		for (auto edge : x->second->edges)
			if (edge.first == id) return x->first;
	}
	return -1;
}

int TrieGraph::getMexID()
{
	std::set <int> idSet;
	for (auto x = nodes.begin(); x != nodes.end(); x++) {
		idSet.insert(x->first);
	}
	int i = 0;
	while (true) {
		if (idSet.find(i) == idSet.end()) {
			return i;
		}
		i++;
	}
}

int TrieGraph::findEdge(int id, std::string weight)
{
	if (nodes.find(id) == nodes.end()) return -1;
	for (auto x : nodes[id]->edges) {
		if (x.second == weight) {
			return x.first;
		}
	}
	return -1;
}

int TrieGraph::countString()
{
	int cnt = 0;
	for (auto x = nodes.begin(); x != nodes.end(); x++) {
		if (x->second->isWord) cnt++;
	}
	return cnt;
}

void TrieGraph::clear()
{
	this->EdgeList.clear();
	this->nodes.clear();
	nodes[0] = new TreeNode(startPosition, radius, thickness, fillColor, textColor, "", font);
}

std::pair<sf::RectangleShape, sf::Text> TrieGraph::getEdgeLine(sf::Vector2f startPosition, sf::Vector2f endPosition, std::string weight)
{
	sf::Vector2f diff = endPosition - startPosition;
	if (length(diff) < 2 * (radius + thickness)) {
		return { sf::RectangleShape(), sf::Text() };
	}
	sf::RectangleShape line(sf::Vector2f((length(diff) - 2.f * (this->radius + (float)this->thickness)), this->thickness));
	line.setOrigin(0, (float)this->thickness / 2.f);
	line.setRotation(atan2(diff.y, diff.x) * 180.f / 3.14159265);
	line.setPosition(startPosition + sf::Vector2f(diff.x / length(diff), diff.y / length(diff)) * (this->radius + (float)this->thickness));
	line.setFillColor(this->textColor);
	sf::Text text;
	text.setFillColor(this->textColor);
	text.setFont(*font);
	text.setString(weight);
	text.setCharacterSize((int)round(radius / 3 * 2));
	text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2, text.getLocalBounds().top + text.getLocalBounds().height / 2);
	if (diff.x <= 0) text.setPosition(startPosition + sf::Vector2f((diff.x / 2) - (float)(thickness * 3), diff.y / 2));
	else if (diff.x >= 0) text.setPosition(startPosition + sf::Vector2f((diff.x / 2) + (float)(thickness * 3), diff.y / 2));
	else text.setPosition(startPosition + normalize(diff) * round(length(diff) / 2.f) - sf::Vector2f(round(diff.y * thickness * 3 / length(diff)), 0));
	return { line, text };
}

void TrieGraph::DFS(int id, int height, std::vector<std::pair<int, int>>& tour)
{
	if (nodes.find(id) == nodes.end()) {
		return;
	}
	tour.push_back(std::make_pair(id, height));
	std::vector <std::pair<int, std::string>> children;
	for (auto& child : nodes[id]->edges) {
		if (child.first != -1) {
			children.push_back(child);
		}
	}
	std::function <bool(std::pair<int, std::string>, std::pair<int, std::string>)> cmp = [&](std::pair<int, std::string> a, std::pair<int, std::string> b) {
		return a.second > b.second;
		};
	sort(children.begin(), children.end(), cmp);
	for (auto& child : children) {
		DFS(child.first, height + 1, tour);
	}
}

void TrieGraph::arrangeTrieTree()
{
	if (root == -1) return;
	std::vector <std::pair <int, int> > tour;
	DFS(root, 0, tour);
	float totalWidth = 0;
	for (auto x : tour) {
		int u = x.first;
		if (nodes.find(u) == nodes.end()) return;
		if (nodes[u]->edges.empty()) totalWidth += 2 * (radius + thickness) + 20;
	}
	totalWidth -= 20;
	float startX = startPosition.x - totalWidth / 2;
	for (auto x = tour.rbegin(); x != tour.rend(); x++) {
		int u = x->first, h = x->second;
		if (nodes.find(u) == nodes.end()) return;
		if (nodes[u]->edges.empty()) {
			nodes[u]->setPosition(sf::Vector2f(startX + radius + thickness, startPosition.y + h * 100));
			startX += 2 * (radius + thickness) + 20;
		}
		else {
			float totalX = 0;
			for (auto y : nodes[u]->edges) {
				int v = y.first;
				if (nodes.find(v) == nodes.end()) return;
				totalX += nodes[v]->getPosition().x;
			}
			nodes[u]->setPosition(sf::Vector2f(totalX / nodes[u]->edges.size(), startPosition.y + h * 100));
		}
	}
}

bool TrieGraph::insertString(std::string str)
{
	if (countString() == this->maxSize) return false;
	int cur = root;
	for (int i = 0; i < str.length(); i++) {
		char x = str[i];
		int id;
		std::string y = charToString(x);
		if (findEdge(cur, y) == -1) {
			id = getMexID();
			this->nodes[cur]->insertEdge(id, y);
			this->nodes[id] = new TreeNode(startPosition, radius, thickness, fillColor, textColor, y, font);
		}
		else {
			id = findEdge(cur, y);
		}
		cur = id;
	}
	this->nodes[cur]->setIsWord(true);
	arrangeTrieTree();
	return true;
}

bool TrieGraph::deleteString(std::string str)
{
	int cur = root;
	std::vector<int> path;
	for (int i = 0; i < str.length(); i++) {
		path.push_back(cur);
		char x = str[i];
		std::string y = charToString(x);
		int id = findEdge(cur, y);
		if (id == -1) return false;
		cur = id;
	}
	int cur2 = path.back();
	if (!this->nodes[cur]->getIsWord()) return false;
	this->nodes[cur]->setIsWord(false);
	if (this->nodes[cur]->edges.empty()) {
		delete this->nodes[cur];
		nodes.erase(cur);
		nodes[cur2]->edges.erase(cur);
	}
	while (1) {
		if (path.empty()) return true;
		cur = path.back(); path.pop_back();
		if (!nodes[cur]->getIsWord() && nodes[cur]->edges.empty()) {
			if (cur == root) return true;
			if (!path.empty()) this->nodes[path.back()]->edges.erase(cur);
			delete this->nodes[cur];
			nodes.erase(cur);
		}
		else return true;
	}
}

bool TrieGraph::searchString(std::string str)
{
	return false;
}

void TrieGraph::update()
{
	arrangeTrieTree();
	for (auto it : nodes) {
		if (it.second->getIsWord()) it.second->setFillColor(NeonPink, DarkBlue);
		else it.second->setFillColor(this->fillColor, this->textColor);
	}

	EdgeList.clear();
	if (nodes.size() > 1) {
		for (auto it : nodes) {
			sf::Vector2f start = it.second->getPosition();
			for (auto it2 : it.second->edges) {
				int cur = it2.first;
				sf::Vector2f end = nodes[cur]->getPosition();
				EdgeList[cur] = getEdgeLine(start, end, it2.second);
			}
		}
	}
}

void TrieGraph::render(sf::RenderTarget& target)
{
	for (auto it : nodes) it.second->render(target);
	for (auto it : EdgeList) {
		target.draw(it.second.first);
		target.draw(it.second.second);
	}
}

