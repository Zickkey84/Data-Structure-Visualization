#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class ImageButton
{
enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED };
private:
	short unsigned buttonState;
	sf::Texture idelTexture;
	sf::Texture hoverTexture;
	sf::Sprite IMG_Button;
public:
	ImageButton(float x, float y, std::string idelTextureFile, std::string hoverTextureFile);
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
	bool isPressed();
};

