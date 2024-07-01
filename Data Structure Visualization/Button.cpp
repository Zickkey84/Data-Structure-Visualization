#include "Button.h"


Button::Button(float x, float y, float width, float height,
	std::string t, sf::Font* font, sf::Color textColor, int textsize,
	sf::Color idleColor, sf::Color borderColor, int borderThickness, sf::Color hoverColor, sf::Color pressedColor)
{
	this->button.setPosition(sf::Vector2f(x, y));
	this->button.setSize(sf::Vector2f(width, height));
	this->font = font;
	this->text.setString(t);
	this->text.setFont(*this->font);
	this->text.setFillColor(textColor);
	this->text.setCharacterSize(textsize);

	// Set position for text
	float xPos = (x + width / 2.0f) - (this->text.getGlobalBounds().width / 2.0f);
	float yPos = (y + height / 2.0f) - (this->text.getGlobalBounds().height / 2.0f);
	this->text.setPosition({ xPos, yPos - 5.0f});

	this->borderThickness = borderThickness;
	this->borderColor = borderColor;
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->pressedColor = pressedColor;

}


void Button::update(const sf::Vector2f mousePos)
{
	this->buttonState = BTN_IDLE;
	if (this->button.getGlobalBounds().contains(mousePos)) 
	{
		this->buttonState = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_PRESSED;
		}
	}

	switch (buttonState)
	{
	case BTN_IDLE:
		this->button.setFillColor(this->idleColor);
		this->button.setOutlineColor(this->borderColor);
		this->button.setOutlineThickness(this->borderThickness);
		break;
	case BTN_HOVER:
		this->button.setOutlineColor(this->hoverColor);
		this->button.setOutlineThickness(this->borderThickness + 2);
		break;
	case BTN_PRESSED:
		this->button.setOutlineColor(this->pressedColor);
		break;
	default:
		break;
	}
}

void Button::render(sf::RenderTarget* target)

{
	target->draw(this->button);
	target->draw(this->text);
}

bool Button::isMouseOver(sf::RenderWindow& window)
{
	float mouseX = sf::Mouse::getPosition().x;
	float mouseY = sf::Mouse::getPosition().y;

	float buttonX = this->button.getPosition().x;
	float buttonY = this->button.getPosition().y;

	float buttonWidth = this->button.getGlobalBounds().width;
	float buttonHeigh = this->button.getGlobalBounds().height;

	if (mouseX >= buttonX && mouseX <= buttonX + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeigh) {
		return true;
	}
	return false;
}

const bool Button::isPressed() const
{
	if (this->buttonState == BTN_PRESSED) return true;
	return false;
}
