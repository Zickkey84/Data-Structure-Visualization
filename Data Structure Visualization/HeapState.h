#pragma once

#include "State.h"
#include "GUI.h"
class HeapState : public State
{

enum OperationState{Create = 0, Insert, Delete, GetTop, Size};
private:
	sf::Texture BackGroundTexture;
	sf::Sprite BackGroundSprite;
	gui::ImageButton* BackButton;
	std::map<std::string, sf::Font> fonts;

	gui::Button* DoButton;
	gui::DropdownList* OperationButton;

	unsigned operationState = 0;

public:

	// Constructor & Destructor
	HeapState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~HeapState();

	void checkForEnd();
	
	// Initialization
	void initFont();
	void initBackground();
	void initButton();

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
