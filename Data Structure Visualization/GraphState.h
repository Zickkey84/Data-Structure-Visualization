#pragma once

#include "State.h"
#include "GUI.h"
class GraphState : public State
{

enum OperationState{Create = 0, Insert, Delete, GetTop, Size};
enum CreateState{Manually = 0, Random, File};
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

	gui::TextBox* InputManuallyValue;
	gui::TextBox* InputRandomValue;
	gui::TextBox* EnterTheValue;

	sf::Text* NumberOfVal;
	sf::Text* EnterTheVal;

	unsigned operationState = 0;
	unsigned createState = 0;
public:

	// Constructor & Destructor
	GraphState(sf::RenderWindow* window, std::stack<State*>* states, bool DarkMode);
	virtual ~GraphState();

	void checkForEnd();

	// Initialization
	void initFont();
	void initBackground();
	void initGUI();
	void initText();
	// Update Funtions
	void updateKeybinds(const float& dt);
	void updateOperationState();
	void update(const float& dt);

	// Render Functions
	void render(sf::RenderTarget* target = nullptr);

public: //Struct
	struct Node {
		int val, depth, index, order;
		Node* left, * right;
		bool isHighlighted;
	};
	
};
