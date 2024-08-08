#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "OpenFileDialog.h"
#include "Miscellaneous.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <math.h>
#include <vector>
#include <stack>
#include <map>

class State
{
protected:
	std::stack<State*>* states;

	sf::RenderWindow* window;
	std::vector<sf::Texture> textures;
	bool end;
	bool DarkMode = false;

public: // Constructor & Destructor
	sf::Vector2i MousePos;
	State(sf::RenderWindow* window, std::stack<State*>* states, bool DarkMode);
	virtual ~State();

public: //Functions
	const bool& getEnd() const;

	virtual void checkForEnd();
	//virtual void endState() = 0;
	virtual void updateKeybinds(const float& dt) = 0;
	virtual void updateMousePos();
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

