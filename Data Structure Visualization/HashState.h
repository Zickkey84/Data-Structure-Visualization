#pragma once

#include "State.h"
#include "GUI.h"
#include "HashGraph.h"

class HashState : public State
{

enum OperationState{Create = 0, Insert, Delete, Search};
enum CreateState{Random = 0, File};
enum ArrowState{None = 0, Searching, Found, NotFound, ZeroIndex};
private:
	sf::Texture BackGroundTexture;
	sf::Sprite BackGroundSprite;

	std::map<std::string, sf::Font> fonts;

	gui::ImageButton* BackButton;
	gui::Button* DoButton;

	gui::Button* InputFileButton;
	std::string FileName = "";

	gui::DropdownList* OperationButton;
	gui::DropdownList* CreateType;
	gui::DropdownList* Speed;

	gui::TextBox* InputRandomValue;
	gui::TextBox* EnterTheValue;

	sf::Text* NumberOfVal;
	sf::Text* EnterTheVal;

	sf::Text* code;
	sf::Text* noti;
	sf::ConvexShape arrow;

	unsigned operationState = 0;
	unsigned createState = 0;
	unsigned arrowState = 0;
	Hash* hash;
	HashGraph* hashGraph;

	bool inserting = false, deleting = false, searching = false; 
	int input, hashIndex; float speed = 1.f;
public:

	// Constructor & Destructor
	HashState(sf::RenderWindow* window, std::stack<State*>* states, bool DarkMode);
	virtual ~HashState();

	void checkForEnd();

	// Initialization
	void initFont();
	void initBackground();
	void initGUI();
	void initText();
	void initHashGraph();
	// Update Funtions
	void updateKeybinds(const float& dt);
	void updateOperationState();
	void updateNoti();
	void updateSpeed();
	void update(const float& dt);

	// Render Functions
	void render(sf::RenderTarget* target = nullptr);
};
