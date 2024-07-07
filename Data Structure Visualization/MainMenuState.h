#pragma once
#include "State.h"
#include "GUI.h"
#include "HeapState.h"
class MainMenuState :
    public State
{
private: //Variables
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

private: // Functions
	void initBackground();
	void initFont();
	void initButton();
public: // Constructor & Destructor
	MainMenuState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~MainMenuState();

public:
	void updateButton();
	void renderButton(sf::RenderTarget* target = nullptr);
	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);

};

