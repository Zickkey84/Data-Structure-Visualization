#pragma once

#include "State.h"
#include "GUI.h"
#include "TrieGraph.h"

class TrieState : public State
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
	gui::TextBox2* EnterTheValue;

	sf::Text* NumberOfVal;
	sf::Text* EnterTheVal;
	sf::Text* noti;
	sf::Text* code;
	sf::ConvexShape arrow;

	unsigned operationState = 0;
	unsigned createState = 0;
	unsigned arrowState = 0;
	TrieGraph* trieGraph;
	bool searching = false; std::string str; int index = 0;
	int id; int cur; float speed = 1;
public:

	// Constructor & Destructor
	TrieState(sf::RenderWindow* window, std::stack<State*>* states, bool DarkMode);
	virtual ~TrieState();

	void checkForEnd();

	// Initialization
	void initFont();
	void initBackground();
	void initGUI();
	void initText();
	void initTrieGraph();
	// Update Funtions
	void updateKeybinds(const float& dt);
	void updateOperationState();
	void updateNoti();
	void updateSpeed();
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
