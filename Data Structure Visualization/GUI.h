#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED};


namespace gui 
{
	// BUTTON
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

	public: // Constructor
		Button(float x, float y, float width, float height,
			std::string t, sf::Font* font, sf::Color textColor, int textsize,
			sf::Color idleColor, sf::Color borderColor, int borderThickness, sf::Color hoverColor, sf::Color pressedColor);
		~Button();
	public:
		// Getter
		const sf::Text getText() const;
		const sf::Vector2f getPosition() const;
		const sf::FloatRect getBounds() const;
		// Setter 
		void setText(sf::Text text);
	public:
		void update(const sf::Vector2f mousePos);
		void render(sf::RenderTarget& target);
	public:
		bool isMouseOver(sf::RenderWindow& window);
		const bool isPressed() const;
	};

	// IMAGEBUTTON
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
		void render(sf::RenderTarget& target);
		bool isPressed();
	};

	// DROPDOWN LIST
	class DropdownList
	{
	private:
		float keyTime = 0.f;
		float keyTimeMax = 1.f;
		sf::Font* font;
		gui::Button* activeEle;
		std::vector<gui::Button*> list;
		sf::ConvexShape OC_Arrow; // Open/Close Arrow
		bool isShowed;
	public:
		DropdownList(float x, float y, float width, float height, 
			sf::Font* font, std::vector<std::string> list, sf::Color textColor, 
			int textsize, sf::Color idleColor, sf::Color borderColor, 
			int borderThickness, sf::Color hoverColor, sf::Color pressedColor);
		~DropdownList();

		const bool getKeyTime();
		const std::string getActiveEle();
		// Update
		void updateKeyTime(const float dt);
		void update(const sf::Vector2f& mousePos, const float dt);

		// Render
		void render(sf::RenderTarget& target);
	};

	// Text Box
	class TextBox {
	private:
		sf::RectangleShape Box;
		sf::RectangleShape Cursor;
		sf::Text Textbox;
		std::ostringstream text;

		bool isSelected = false;

	private:
		void deleteLastchar();
		void input(int charTyped);

	public:	
		TextBox(float x, float y, float width, float height, sf::Font* font, int outlineThickness, 
			sf::Color outlineColor, sf::Color boxColor, sf::Color textColor, sf::Color cursorColor);
		void update(const sf::Vector2f& mousePos, sf::Event& evnt);
		void render(sf::RenderTarget &target);
	};
}

