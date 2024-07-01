#include "ImageButton.h"



ImageButton::ImageButton(float x, float y, std::string idelTextureFile, std::string hoverTextureFile)
{
	if (!this->idelTexture.loadFromFile(idelTextureFile)) {
		std::cerr << "Error loading Button Texture!\n";
	}
	if (!this->hoverTexture.loadFromFile(hoverTextureFile)) {
		std::cerr << "Error loading hoverButton Texture!\n";
	}
	this->IMG_Button.setPosition(sf::Vector2f(x, y));
}


void ImageButton::update(const sf::Vector2f mousePos)
{
	this->buttonState = BTN_IDLE;
	if (this->IMG_Button.getGlobalBounds().contains(mousePos))
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
		this->IMG_Button.setTexture(this->idelTexture);
		break;
	case BTN_HOVER:
		this->IMG_Button.setTexture(this->hoverTexture);
		break;
	default:
		break;
	}
}

void ImageButton::render(sf::RenderTarget* target)
{
	target->draw(this->IMG_Button);
}

bool ImageButton::isPressed()
{
	if (this->buttonState == BTN_PRESSED) return true;
	return false;
}
