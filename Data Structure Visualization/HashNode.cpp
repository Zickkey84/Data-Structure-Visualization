#include "HashNode.h"

HashNode::HashNode(sf::Vector2f position, float length, int borderThickness, sf::Color fillColor, sf::Color textColor, int value, sf::Font* font)
{
	this->square.setSize({ length, length });
	this->square.setOrigin({ round(length / 2), round(length / 2) });
	this->square.setPosition(position);
	this->square.setOutlineThickness(borderThickness);
	this->square.setFillColor(fillColor);
	this->square.setOutlineColor(textColor);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setFillColor(textColor);
	this->text.setCharacterSize((int)length / 3 );
	if (value != -1) this->text.setString(std::to_string(value));
	else this->text.setString("");
	this->text.setOrigin({ round(this->text.getLocalBounds().width / 2.0f), round(this->text.getLocalBounds().height / 2.0f) });
	this->text.setPosition(position - sf::Vector2f(0, (float)round(length * 0.1)));

	this->textVariable.setFont(*this->font);
	this->textVariable.setFillColor(textColor);
	this->textVariable.setCharacterSize((int)length / 3 );
	this->textVariable.setString("");
	this->textVariable.setOrigin({ round(this->textVariable.getLocalBounds().width / 2.0f), round(this->textVariable.getLocalBounds().height / 2.0f) });
	this->textVariable.setPosition({ position.x - (float)round(length * 0.15), position.y + (float)round(length / 2)});
}

sf::Vector2f HashNode::getSquarePosition()
{
	return this->square.getPosition();
}

int HashNode::getValue()
{
	return this->value;
}

std::string HashNode::getText()
{
	return this->text.getString();
}

void HashNode::setPosition(sf::Vector2f newPosition)
{
	this->square.setPosition(newPosition);
	this->text.setPosition(newPosition);
	this->textVariable.setPosition({ newPosition.x, newPosition.y + this->square.getSize().y });
}

void HashNode::setColor(sf::Color newFillColor, sf::Color newTextColor)
{
	this->fillColor = newFillColor;
	this->textColor = newTextColor;
}

void HashNode::setBorderColor(sf::Color newColor)
{
	this->square.setOutlineColor(newColor);
}

void HashNode::setValue(int newValue)
{
	this->value = newValue;
	this->text.setString(std::to_string(this->value));
	this->text.setOrigin(round(this->text.getLocalBounds().left + this->text.getLocalBounds().width / 2),
		round(this->text.getLocalBounds().top + this->text.getLocalBounds().height / 2));
	this->text.setPosition(this->square.getPosition());
}

void HashNode::setText(std::string newText)
{
	this->text.setString(newText);
}

void HashNode::setVariableText(std::string text)
{
	this->textVariable.setString(text);
}

void HashNode::setHighlight(sf::Color highlightColor, float borderThickness)
{
	this->square.setOutlineThickness(borderThickness);
	this->square.setOutlineColor(highlightColor);
}

void HashNode::render(sf::RenderTarget& target)
{
	target.draw(this->square);
	target.draw(this->text);
	target.draw(this->textVariable);
}
