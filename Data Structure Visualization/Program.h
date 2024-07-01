#pragma once
#include "MainMenuState.h"

// This class acts as the program engine.

class Program
{
private: // Functions
	void initWindow();
	void initState();
private: // Variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event evnt;

	std::stack<State*> states;

	sf::Clock dtClock;
	float dt;
public: // Constructor / Destructor
	Program();
	virtual ~Program();

public: //getter
	const bool running() const;

public: // Functions
	void updateDT();
	void pollEvents();
	void update();
	void render();
	void run();
};

