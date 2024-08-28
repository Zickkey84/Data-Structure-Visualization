#include "TreeNode.h"

TreeNode::TreeNode(sf::Vector2f position, float radius, int borderThickness, sf::Color vertexColor, sf::Color textColor, int value, sf::Font *font)
{
	this->vertex.setRadius(radius);
	this->vertex.setOrigin(radius, radius);
	this->vertex.setPosition(position);
	this->vertex.setOutlineThickness(borderThickness);

	this->value = value;

	this->vertexColor = vertexColor;
	this->textColor = textColor;

	this->vertex.setFillColor(vertexColor);
	this->vertex.setOutlineColor(textColor);
	
	this->font = font;

	this->text.setFont(*this->font);
	this->text.setFillColor(textColor);
	this->text.setCharacterSize((int)round(radius / 3 * 2));
	this->text.setString(std::to_string(value));
	this->text.setOrigin({ round(this->text.getLocalBounds().width / 2.0f), round(this->text.getLocalBounds().height / 2.0f) });
	this->text.setPosition(position + sf::Vector2f(0, - round(radius * 0.15)));

	this->textVariable.setFillColor(textColor);
	this->textVariable.setCharacterSize((int)round(radius / 3 * 2));
	this->textVariable.setString("");
	this->textVariable.setOrigin({ round(this->text.getLocalBounds().width / 2.0f), round(this->text.getLocalBounds().height / 2.0f) });
	this->textVariable.setPosition({position.x, position.y + radius * 2});
}

TreeNode::TreeNode(sf::Vector2f position, float radius, int borderThickness, sf::Color vertexColor, sf::Color textColor, std::string val, sf::Font* font)
{
	this->vertex.setRadius(radius);
	this->vertex.setOrigin(radius, radius);
	this->vertex.setPosition(position);
	this->vertex.setOutlineThickness(borderThickness);

	this->vertexColor = vertexColor;
	this->textColor = textColor;

	this->vertex.setFillColor(vertexColor);
	this->vertex.setOutlineColor(textColor);

	this->font = font;

	this->text.setFont(*this->font);
	this->text.setFillColor(textColor);
	this->text.setCharacterSize((int)radius / 3 * 2);
	this->text.setString(val);
	this->text.setOrigin({ round(this->text.getLocalBounds().width / 2.0f), round(this->text.getLocalBounds().height / 2.0f) });
	this->text.setPosition(position + sf::Vector2f(0, -round(radius * 0.15)));

	this->textVariable.setFillColor(textColor);
	this->textVariable.setCharacterSize((int)radius / 3 * 2);
	this->textVariable.setString("");
	this->textVariable.setOrigin({ round(this->text.getLocalBounds().width / 2.0f), round(this->text.getLocalBounds().height / 2.0f) });
	this->textVariable.setPosition({ position.x, position.y + radius * 2 });
}

sf::Vector2f TreeNode::getVertexPosition()
{
	return this->vertex.getPosition();
}

std::vector<std::string> TreeNode::getVariables()
{
	std::vector<std::string> v;
	for (auto it = this->variableList.begin(); it != this->variableList.end(); it++) {
		v.push_back(*it);
	}
	return v;
}

int TreeNode::getValue()
{
	return this->value;
}

std::string TreeNode::getVariableString()
{
	std::string s = "";
	for (auto it = this->variableList.begin(); it != this->variableList.end(); it++) {
		s += *it;	s += ", ";
	}
	if (s.size() > 0) {
		s.pop_back();	s.pop_back();
	}
	return s;
}

bool TreeNode::getIsWord()
{
	return this->isWord;
}

sf::Vector2f TreeNode::getPosition()
{
	return vertex.getPosition();
}

float TreeNode::getRadius()
{
	return this->vertex.getRadius();
}

void TreeNode::setPosition(sf::Vector2f newPosition)
{
	this->vertex.setPosition(newPosition);
	this->text.setPosition(newPosition);
	this->textVariable.setPosition({ newPosition.x, newPosition.y + this->vertex.getRadius() * 2 });
}

void TreeNode::setSize(float newPercent)
{
	this->vertex.setRadius(round(this->vertex.getRadius() * newPercent));
	this->vertex.setOutlineThickness(round(this->vertex.getOutlineThickness() * newPercent));
	this->vertex.setOrigin(round(this->vertex.getLocalBounds().left + this->vertex.getLocalBounds().width / 2), 
		round(this->vertex.getLocalBounds().top + this->vertex.getLocalBounds().height / 2));
	this->vertex.setPosition(this->vertex.getPosition());
	
	this->text.setCharacterSize(round(this->text.getCharacterSize() * newPercent));
	this->text.setOrigin(round(this->text.getLocalBounds().left + this->text.getLocalBounds().width / 2), 
		round(this->text.getLocalBounds().top + this->text.getLocalBounds().height / 2));
	this->text.setPosition(this->vertex.getPosition());
	
	this->textVariable.setCharacterSize(round(this->textVariable.getCharacterSize() * newPercent));
	this->textVariable.setOrigin(round(this->textVariable.getLocalBounds().left + this->textVariable.getLocalBounds().width / 2), 
		round(this->textVariable.getLocalBounds().top + this->textVariable.getLocalBounds().height / 2));
	this->textVariable.setPosition(this->vertex.getPosition() + sf::Vector2f(0, round(this->vertex.getRadius() * 2 * newPercent)));
}

void TreeNode::setColor(sf::Color newVertexColor, sf::Color newTextColor)
{
	this->vertexColor = newVertexColor;
	this->textColor = newTextColor;
}

void TreeNode::setFillColor(sf::Color newVertexColor, sf::Color newTextColor) {
	this->vertex.setFillColor(newVertexColor);
	this->vertex.setOutlineColor(newTextColor);
	this->text.setFillColor(newTextColor);
}

void TreeNode::setValue(int newValue)
{
	this->value = newValue;
	this->text.setString(std::to_string(this->value));
	this->text.setOrigin(round(this->text.getLocalBounds().left + this->text.getLocalBounds().width / 2),
		round(this->text.getLocalBounds().top + this->text.getLocalBounds().height / 2));
	this->text.setPosition(this->vertex.getPosition());
}

void TreeNode::setValue(std::string newValue)
{
	this->val = newValue;
	text.setString(val);
	text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2, text.getLocalBounds().top + text.getLocalBounds().height / 2);
	text.setPosition(vertex.getPosition().x, vertex.getPosition().y);
}

void TreeNode::insertEdge(int id, std::string weight)
{
	edges[id] = weight;
}

void TreeNode::deleteEdge(int id)
{
	if (edges.find(id) == edges.end()) {
		return;
	}
	edges.erase(id);
}

void TreeNode::setIsWord(bool isWord)
{
	this->isWord = isWord;
}

void TreeNode::setHighlight(sf::Color newColor, int thickness)
{
	this->vertex.setOutlineColor(newColor);
	this->vertex.setOutlineThickness(thickness);
}

void TreeNode::insertVariable(std::string variable)
{
	this->variableList.insert(variable);
	this->textVariable.setString(getVariableString());
	this->textVariable.setOrigin(round(this->textVariable.getLocalBounds().left + this->textVariable.getLocalBounds().width / 2), 
		round(this->textVariable.getLocalBounds().top + this->textVariable.getLocalBounds().height / 2));
	this->textVariable.setPosition(round(this->vertex.getPosition().x), round(this->vertex.getPosition().y + this->vertex.getRadius() * 2));
}

void TreeNode::deleteVariable(std::string variable)
{
	this->variableList.erase(this->variableList.find(variable));
	this->textVariable.setString(getVariableString());
	this->textVariable.setOrigin(round(this->textVariable.getLocalBounds().left + this->textVariable.getLocalBounds().width / 2), 
		round(this->textVariable.getLocalBounds().top + this->textVariable.getLocalBounds().height / 2));
	this->textVariable.setPosition(this->vertex.getPosition().x, this->vertex.getPosition().y + this->vertex.getRadius() * 2);
}

void TreeNode::insertVariable(std::vector<std::string> variables)
{
	for (auto variable : variables) {
		this->variableList.insert(variable);
	}
	this->textVariable.setString(getVariableString());
	this->textVariable.setOrigin(round(this->textVariable.getLocalBounds().left + this->textVariable.getLocalBounds().width / 2), 
		round(this->textVariable.getLocalBounds().top + this->textVariable.getLocalBounds().height / 2));
	this->textVariable.setPosition(this->vertex.getPosition().x, this->vertex.getPosition().y + this->vertex.getRadius() * 2);
}

void TreeNode::deleteVariable(std::vector<std::string> variables)
{
	for (auto variable : variables) {
		this->variableList.erase(variable);
	}
	this->textVariable.setString(getVariableString());
	this->textVariable.setOrigin(round(this->textVariable.getLocalBounds().left + this->textVariable.getLocalBounds().width / 2),
		round(this->textVariable.getLocalBounds().top + this->textVariable.getLocalBounds().height / 2));
	this->textVariable.setPosition(this->vertex.getPosition().x, this->vertex.getPosition().y + this->vertex.getRadius() * 2);
}

void TreeNode::render(sf::RenderTarget& target)
{
	target.draw(this->vertex);
	target.draw(this->text);
	target.draw(this->textVariable);
}

