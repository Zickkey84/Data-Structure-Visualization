#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED};
class Button
{
private:
	short unsigned buttonState;

	sf::RectangleShape button;
	sf::Font* font;
	sf::Text text;

	int borderThickness;
	sf::Color borderColor;
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color pressedColor;

public:
	Button();
	Button(float x, float y, float width, float height,
		std::string t, sf::Font* font, sf::Color textColor, int textsize, 
		sf::Color idleColor, sf::Color borderColor, int borderThickness, sf::Color hoverColor, sf::Color pressedColor);

public:
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
public:
	bool isMouseOver(sf::RenderWindow& window);
	const bool isPressed() const;
};

