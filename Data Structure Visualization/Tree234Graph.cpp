#include "Tree234Graph.h"

Node234::Node234(sf::Vector2f position, int value, sf::Font* font, sf::Color fillColor, sf::Color textColor, float size, float thickness)
{
	this->position = position;
	this->value = value;
	this->font = font;
	this->fillColor = fillColor;
	this->textColor = textColor;
	this->size = size;
	this->thickness = thickness;

	this->rect.setSize(sf::Vector2f(size, size));
	this->rect.setFillColor(fillColor);
	this->rect.setOutlineThickness(thickness);
	this->rect.setOutlineColor(textColor);
	this->rect.setOrigin(rect.getLocalBounds().left + rect.getLocalBounds().width / 2, rect.getLocalBounds().top + rect.getLocalBounds().height / 2);
	this->rect.setPosition(position);

	valueText.setFont(*font);
	valueText.setStyle(sf::Text::Bold);
	valueText.setString(std::to_string(value));
	valueText.setCharacterSize(size / 3);
	valueText.setOrigin(valueText.getLocalBounds().left + valueText.getLocalBounds().width / 2, valueText.getLocalBounds().top + valueText.getLocalBounds().height / 2);
	valueText.setPosition(position);
}

void Node234::setPosition(float newX, float newY)
{
	this->rect.setPosition(newX, newY);
	this->valueText.setPosition(newX, newY);
}

void Node234::setPosition(sf::Vector2f newPosition)
{
	this->rect.setPosition(newPosition);
	valueText.setPosition(newPosition);
}

void Node234::setSize(float percent)
{
	rect.setSize(sf::Vector2f(this->size * percent, this->size * percent));
	rect.setOutlineThickness(thickness * percent);
	rect.setOrigin(rect.getLocalBounds().left + rect.getLocalBounds().width / 2, rect.getLocalBounds().top + rect.getLocalBounds().height / 2);
	rect.setPosition(rect.getPosition());
	valueText.setCharacterSize(size / 3 * percent);
	valueText.setOrigin(valueText.getLocalBounds().left + valueText.getLocalBounds().width / 2, valueText.getLocalBounds().top + valueText.getLocalBounds().height / 2);
	valueText.setPosition(rect.getPosition());
}

void Node234::setValue(int value)
{
	this->value = value;
	valueText.setString(std::to_string(value));
	valueText.setOrigin(valueText.getLocalBounds().left + valueText.getLocalBounds().width / 2, valueText.getLocalBounds().top + valueText.getLocalBounds().height / 2);
	valueText.setPosition(rect.getPosition().x, rect.getPosition().y);
}

sf::Vector2f Node234::getPosition()
{
	return rect.getPosition();
}

int Node234::getValue()
{
	return this->value;
}

void Node234::render(sf::RenderTarget& target)
{
	target.draw(rect);
	target.draw(valueText);
}

Group234::Group234(std::vector<int> nodes, float size, float thickness)
{
	this->nodes = nodes;
	this->size = size;
	this->thickness = thickness;
	listEdge.resize(nodes.size() + 1, -1);
}

void Group234::setEdge(int pos, int id)
{
	if (pos > nodes.size()) {
		while (listEdge.size() <= pos) {
			listEdge.push_back(-1);
		}
	}
	listEdge[pos] = id;
}

bool Group234::isLeaf()
{
	for (int i = 0; i < listEdge.size(); ++i) {
		if (listEdge[i] != -1) {
			return false;
		}
	}
	return true;
}

sf::Vector2f Group234::getSize()
{
	if (nodes.empty()) {
		return sf::Vector2f(0, 0);
	}
	return sf::Vector2f(nodes.size() * size + thickness, size + thickness);
}

Tree234Graph::Tree234Graph(sf::Vector2f startPosition, sf::Font* font, colorTheme theme, float size, float thickness) 
{
	this->startPosition = startPosition;
	this->font = font;
	this->fillColor = HASH::color[theme][HASH::Normal].fillColor;
	this->textColor = HASH::color[theme][HASH::Normal].outlineColor;
	this->size = size;
	this->thickness = thickness;
	this->root = -1;
}

Tree234Graph::~Tree234Graph()
{
	clear();
}

int Tree234Graph::getGroupID(int id)
{
	for (auto& group : groups) {
		for (auto& node : group.second->nodes) {
			if (node == id) return group.first;
		}
	}
	return -1;
}

int Tree234Graph::getParentGroup(int id)
{
	int groupID = getGroupID(id);
	if (groupID == -1) return -1;
	for (auto& group : groups) {
		for (auto& edge : group.second->listEdge) {
			if (edge == groupID) return group.first;
		}
	}
	return -1;
}

int Tree234Graph::getMexNodeID()
{
	std::set <int> idList;
	for (auto& node : nodes) {
		idList.insert(node.first);
	}
	int mex = 0;
	while (true) {
		if (idList.find(mex) == idList.end()) return mex;
		mex++;
	}
}

int Tree234Graph::getMexGroupID()
{
	std::set <int> idList;
	for (auto& group : groups) {
		idList.insert(group.first);
	}
	int mex = 0;
	while (true) {
		if (idList.find(mex) == idList.end()) return mex;
		mex++;
	}
}

std::vector<int> Tree234Graph::getMexNodeIDs(int size)
{
	std::set <int> idList;
	for (auto& node : nodes) {
		idList.insert(node.first);
	}
	std::vector <int> mexList;
	int mex = 0;
	while (mexList.size() < size) {
		if (idList.find(mex) == idList.end()) mexList.push_back(mex);
		mex++;
	}
	return mexList;
}

std::vector<int> Tree234Graph::getMexGroupIDs(int size)
{
	std::set <int> idList;
	for (auto& group : groups) {
		idList.insert(group.first);
	}
	std::vector <int> mexList;
	int mex = 0;
	while (mexList.size() < size) {
		if (idList.find(mex) == idList.end()) mexList.push_back(mex);
		mex++;
	}
	return mexList;
}

sf::RectangleShape Tree234Graph::getEdgeLine(sf::Vector2f startPosition, sf::Vector2f endPosition)
{
	sf::Vector2f diff = endPosition - startPosition;
	sf::RectangleShape line(sf::Vector2f(length(diff) , 2));
	line.setOrigin(0, thickness / 2);
	line.setFillColor(textColor);
	line.setPosition(startPosition);
	line.setRotation(atan2(diff.y, diff.x) * 180 / 3.14159265f);
	return line;
}

sf::Vector2f Tree234Graph::getPosition(int idGroup)
{

	auto& group = groups[idGroup];
	if (group->nodes.empty()) {
		std::cout << "Error in getPosition";
		return { 0, 0 };
	}
	int mid = group->nodes.size() / 2;
	if (group->nodes.size() % 2 == 0) {
		return (nodes[group->nodes[mid - 1]]->getPosition() + nodes[group->nodes[mid]]->getPosition()) / 2.f;
	}
	else {
		return nodes[group->nodes[mid]]->getPosition();
	}
}

std::vector<int> Tree234Graph::getEdges(int idGroup)
{
	if (groups.find(idGroup) == groups.end()) {
		std::cout << "Error in getEdges";
		return std::vector<int>(0);
	}
	return groups[idGroup]->listEdge;
}

sf::Vector2f Tree234Graph::getStartEdgePosition(int idGroup, int pos, sf::Vector2f curPosition)
{
	if (groups.find(idGroup) == groups.end()) {
		std::cout << "Error in getStartEdgesPos";
		return { 0,0 };
	}
	auto& group = groups[idGroup];
	if (pos < 0 || pos > group->nodes.size()) {
		std::cout << "Error in getStartEdgesPos";
		return { 0,0 };
	}
	sf::Vector2f diff = curPosition - getPosition(idGroup);
	if (pos == 0) {
		return nodes[group->nodes[0]]->getPosition() + sf::Vector2f(-size / 2, size / 2) + diff;
	}
	else if (pos == group->nodes.size()) {
		return nodes[group->nodes.back()]->getPosition() + sf::Vector2f(size / 2, size / 2) + diff;
	}
	else {
		return (nodes[group->nodes[pos - 1]]->getPosition() + nodes[group->nodes[pos]]->getPosition()) / 2.f + sf::Vector2f(0, size / 2) + diff;
	}
}

sf::Vector2f Tree234Graph::getEndEdgePosition(int idGroup, sf::Vector2f curPosition)
{
	if (groups.find(idGroup) == groups.end()) {
		std::cout << "Error in getEndEdgesPos";
		return { 0,0 };
	}
	if (groups[idGroup]->nodes.empty()) {
		return { 0, 0 };
	}
	return curPosition + sf::Vector2f(0, -size / 2);
}

void Tree234Graph::clear()
{
	nodes.clear();
	groups.clear();
	this->Edgeslist.clear();
}

void Tree234Graph::DFS(int id, int height, std::vector<std::vector<std::vector<int>>>& tour)
{
	bool flag = false;
	for (auto& child : groups[id]->listEdge) {
		if (child != -1) {
			if (!flag) {
				tour[height + 1].push_back(std::vector <int>());
				flag = true;
			}
			tour[height + 1].back().push_back(child);
			DFS(child, height + 1, tour);
		}
	}
}

void Tree234Graph::arrangeBTree()
{
	if (root == -1) return;
	std::vector <std::vector <std::vector <int> > > tour(groups.size() + 1);
	tour[0].push_back({ root });
	DFS(root, 0, tour);
	int leafHeight = -1;
	while (true) {
		if (tour.size() <= leafHeight + 1) {
			break;
		}
		if (tour[leafHeight + 1].empty()) {
			break;
		}
		leafHeight++;
	}
	float totalWidth = 0;
	for (int i = 0; i < tour[leafHeight].size(); i++) {
		for (int j = 0; j < tour[leafHeight][i].size(); j++) {
			totalWidth += groups[tour[leafHeight][i][j]]->getSize().x;
			if (j < tour[leafHeight][i].size() - 1) {
				totalWidth += 20;
			}
		}
		if (i < tour[leafHeight].size() - 1) {
			totalWidth += 20;
		}
	}
	float startX = startPosition.x - totalWidth / 2;
	float startY = startPosition.y + leafHeight * 140;
	for (int i = 0; i < tour[leafHeight].size(); i++) {
		for (int j = 0; j < tour[leafHeight][i].size(); j++) {
			sf::Vector2f here = groups[tour[leafHeight][i][j]]->getSize();
			setPosition(tour[leafHeight][i][j], sf::Vector2f(startX + here.x / 2, startY));
			startX += here.x;
			if (j < tour[leafHeight][i].size() - 1) {
				startX += 20;
			}
		}
		if (i < tour[leafHeight].size() - 1) {
			startX += 20;
		}
	}
	for (int h = leafHeight - 1; h >= 0; h--) {
		startY -= 140;
		for (int i = 0; i < tour[h].size(); i++) {
			for (int j = 0; j < tour[h][i].size(); j++) {
				int idGroup = tour[h][i][j];
				if (groups[idGroup]->listEdge.empty()) {
					continue;
				}
				float totalPositionX = 0;
				for (auto& edge : groups[idGroup]->listEdge) {
					if (edge == -1) continue;
					totalPositionX += getPosition(edge).x;
				}
				setPosition(idGroup, sf::Vector2f(totalPositionX / groups[idGroup]->listEdge.size(), startY));
			}
		}
	}
}

void Tree234Graph::setPosition(int idGroup, sf::Vector2f position)
{
	if (groups.find(idGroup) == groups.end()) return;
	auto& group = groups[idGroup];
	if (group->nodes.empty()) return;
	int mid = group->nodes.size() / 2;
	if (group->nodes.size() % 2 == 0) {
		nodes[group->nodes[mid - 1]]->setPosition(position - sf::Vector2f(size / 2, 0));
		nodes[group->nodes[mid]]->setPosition(position + sf::Vector2f(size / 2, 0));
		for (int i = mid - 2; i >= 0; i--) {
			nodes[group->nodes[i]]->setPosition(nodes[group->nodes[i + 1]]->getPosition() - sf::Vector2f(size, 0));
		}
		for (int i = mid + 1; i < group->nodes.size(); i++) {
			nodes[group->nodes[i]]->setPosition(nodes[group->nodes[i - 1]]->getPosition() + sf::Vector2f(size, 0));
		}
	}
	else {
		nodes[group->nodes[mid]]->setPosition(position);
		for (int i = mid - 1; i >= 0; i--) {
			nodes[group->nodes[i]]->setPosition(nodes[group->nodes[i + 1]]->getPosition() - sf::Vector2f(size, 0));
		}
		for (int i = mid + 1; i < group->nodes.size(); i++) {
			nodes[group->nodes[i]]->setPosition(nodes[group->nodes[i - 1]]->getPosition() + sf::Vector2f(size, 0));
		}
	}
}

void Tree234Graph::setEdge(int idGroup, int pos, int id)
{
	if (groups.find(idGroup) == groups.end()) return;
	auto& group = groups[idGroup];
	if (pos < 0 || pos > group->nodes.size()) return;
	group->setEdge(pos, id);
}

void Tree234Graph::insertNode(int idGroup, int idNode)
{
	if (groups.find(idGroup) == groups.end() || nodes.find(idNode) == nodes.end()) return;
	auto& group = groups[idGroup];
	int res = -1;
	for (int i = 0; i < group->nodes.size(); i++) {
		if (nodes[group->nodes[i]]->getValue() >= nodes[idNode]->getValue()) {
			res = i;
			break;
		}
	}
	if (res == -1) {
		group->nodes.push_back(idNode);
	}
	else {
		group->nodes.insert(group->nodes.begin() + res, idNode);
	}
	group->listEdge.assign(group->nodes.size() + 1, -1);
}

bool Tree234Graph::deleteNode(int idGroup, int idNode)
{
	if (groups.find(idGroup) == groups.end() || nodes.find(idNode) == nodes.end()) return false;
	auto& group = groups[idGroup];
	for (int i = 0; i < group->nodes.size(); i++) {
		if (group->nodes[i] == idNode) {
			group->nodes.erase(group->nodes.begin() + i);
			group->listEdge.assign(group->nodes.size() + 1, -1);
			return true;
		}
	}
	return false;
}

void Tree234Graph::insert(int value)
{
	if (this->nodes.empty()) {
		int idNode = getMexNodeID();
		int idGroup = getMexGroupID();
		this->nodes[idNode] = new Node234(startPosition, value, font, fillColor, textColor, size, thickness);
		this->groups[idGroup] = new Group234(std::vector<int>(), size, thickness);
		root = idGroup;
		insertNode(idGroup, idNode);
		return;
	}
	int idGroup = root, par = -1;
	while (true) {
		if (groups[idGroup]->nodes.size() < 3 && idGroup != par) {
			int nextIDGroup = findEdge(idGroup, value);
			if (nextIDGroup == -1) {
				int idNode = getMexNodeID();
				this->nodes[idNode] = new Node234(startPosition, value, font, fillColor, textColor, size, thickness);
				insertNode(idGroup, idNode);
				break;
			}
			else {
				par = idGroup;
				idGroup = nextIDGroup;
			}
		}
		else if (par == -1) {
			std::vector <int> newGroupID = getMexGroupIDs(2);
			int idLeftGroup = newGroupID[0], idRightGroup = newGroupID[1];
			std::vector <int> edges = getEdges(idGroup);
			this->groups[idLeftGroup] = new Group234(std::vector<int>(), size, thickness);
			this->groups[idRightGroup] = new Group234(std::vector<int>(), size, thickness);
			insertNode(idLeftGroup, groups[idGroup]->nodes[0]);
			insertNode(idRightGroup, groups[idGroup]->nodes[2]);
			deleteNode(idGroup, groups[idGroup]->nodes[0]);
			deleteNode(idGroup, groups[idGroup]->nodes[1]);
			setEdge(idGroup, 0, idLeftGroup);
			setEdge(idGroup, 1, idRightGroup);
			setEdge(idLeftGroup, 0, edges[0]);
			setEdge(idLeftGroup, 1, edges[1]);
			setEdge(idRightGroup, 0, edges[2]);
			setEdge(idRightGroup, 1, edges[3]);
		}
		else if (idGroup != par) {
			std::vector <int> newGroupID = getMexGroupIDs(2);
			int idLeftGroup = newGroupID[0], idRightGroup = newGroupID[1];
			std::vector <int> edges = getEdges(idGroup);
			std::vector <int> parEdges = getEdges(par);
			int idEdgePos = findEdgePos(par, value);
			this->groups[idLeftGroup] = new Group234(std::vector<int>(), size, thickness);
			this->groups[idRightGroup] = new Group234(std::vector<int>(), size, thickness);
			insertNode(par, groups[idGroup]->nodes[1]);
			insertNode(idRightGroup, groups[idGroup]->nodes[0]);
			insertNode(idLeftGroup, groups[idGroup]->nodes[2]); 
			delete this->groups[idGroup];
			parEdges[idEdgePos] = idLeftGroup;
			parEdges.insert(parEdges.begin() + idEdgePos + 1, idRightGroup);
			for (int i = 0; i < parEdges.size(); i++) {
				setEdge(par, i, parEdges[i]);
			}
			setEdge(idLeftGroup, 0, edges[0]);
			setEdge(idLeftGroup, 1, edges[1]);
			setEdge(idRightGroup, 0, edges[2]);
			setEdge(idRightGroup, 1, edges[3]);
			idGroup = par;
		}
		else {
			int nextIDGroup = findEdge(idGroup, value);
			par = idGroup;
			idGroup = nextIDGroup;
		}
	}
}

int Tree234Graph::findNodePos(int idGroup, int value)
{
	auto& group = groups[idGroup];
	for (int i = 0; i < group->nodes.size(); i++) {
		if (nodes[group->nodes[i]]->getValue() == value) {
			return i;
		}
	}
	return -1;
}

int Tree234Graph::findNode(int idGroup, int value)
{
	auto& group = groups[idGroup];
	for (int i = 0; i < group->nodes.size(); i++) {
		if (nodes[group->nodes[i]]->getValue() == value) {
			return group->nodes[i];
		}
	}
	return -1;
}

int Tree234Graph::findEdge(int idGroup, int value)
{
	auto& group = groups[idGroup];
	for (int i = 0; i < group->nodes.size(); i++) {
		if (nodes[group->nodes[i]]->getValue() >= value) {
			return group->listEdge[i];
		}
	}
	return group->listEdge.back();
}

int Tree234Graph::findEdgePos(int idGroup, int value)
{
	auto& group = groups[idGroup];
	for (int i = 0; i < group->nodes.size(); i++) {
		if (nodes[group->nodes[i]]->getValue() >= value) {
			return i;
		}
	}
	return group->nodes.size();
}

void Tree234Graph::update()
{
	arrangeBTree();
	this->Edgeslist.clear();
	for (auto x = groups.begin(); x != groups.end(); x++) {
		int idU = x->first;
		if (groups[idU]->nodes.empty()) continue;
		sf::Vector2f curPositionU = getPosition(idU);
		for (int i = 0; i < 4; i++) {
			if (x->second->listEdge.size() <= i || x->second->listEdge[i] == -1) continue;
			int idV = x->second->listEdge[i];
			sf::Vector2f curPositionV = getPosition(idV);
			sf::RectangleShape line = getEdgeLine(getStartEdgePosition(idU, i, curPositionU), getEndEdgePosition(idV, curPositionV));
			Edgeslist.push_back(line);
		}
	}
}

void Tree234Graph::render(sf::RenderTarget& target)
{
	for (auto it : this->Edgeslist) target.draw(it);
	for (auto it : this->nodes) it.second->render(target);
}





