#pragma once
#include "State.h"
#include "GUI.h"
#include "HeapState.h"
#include "234TreeState.h"
#include "HashState.h"
#include "GraphState.h"
#include "TrieState.h"
#include "AVLState.h"

class MainMenuState :
    public State
{
private: //Variables
	sf::Texture backgroundTexture;
	sf::Texture DM_backgroundTexture;

	sf::Sprite backgroundSprite;

	sf::Font font;

	gui::ImageButton* darkmodeButton;
	std::map<std::string, gui::Button*> buttons;

private: // Functions
	void initBackground();
	void initFont();
	void initButton();
public: // Constructor & Destructor
	MainMenuState(sf::RenderWindow* window, std::stack<State*>* states, bool DarkMode);
	virtual ~MainMenuState();

public:
	void updateDarkMode(const float& dt);
	void updateButton(const float& dt);
	void renderButton(sf::RenderTarget* target = nullptr);
	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);

};

