#pragma once

#include "State.h"
#include "GUI.h"
#include "Tree234Graph.h"

class Tree234State : public State
{

enum OperationState{Create = 0, Insert, Delete, Search};
enum CreateState{Random = 0, File};
enum ArrowState { None = 0, Active };
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

	Tree234Graph* graph;
	int size = 0;
	bool searching = false; int input; int idGroup = 0;
	float speed = 1.f;

public:

	// Constructor & Destructor
	Tree234State(sf::RenderWindow* window, std::stack<State*>* states, bool DarkMode);
	virtual ~Tree234State();

	void checkForEnd();

	// Initialization
	void initFont();
	void initBackground();
	void initGUI();
	void initText();
	void initGraph();
	// Update Funtions
	void updateKeybinds(const float& dt);
	void updateOperationState();
	void updateNoti();
	void updateSpeed();
	void update(const float& dt);

	// Render Functions
	void render(sf::RenderTarget* target = nullptr);
};
