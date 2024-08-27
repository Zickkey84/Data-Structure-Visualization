#pragma once

#include "State.h"
#include "GUI.h"
#include "GGraph.h"

class GraphState : public State
{

enum OperationState{Create = 0, MST, CC};
enum CreateState{Random = 0, File, Matrix};
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

	gui::TextBox* InputRandomValue;
	gui::TextBox* EnterTheValue;

	sf::Text* NumberOfVal;
	sf::Text* EnterTheVal;

	sf::Text* code;
	sf::Text* noti;

	unsigned operationState = 0;
	unsigned createState = 0;

	GGraph* graph;
	std::set<GEdge*> edges;
	gui::MatrixBox* matrixBox;
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
	void initGraph();
	// Update Funtions
	void updateKeybinds(const float& dt);
	void updateOperationState();
	void updateNoti();
	void update(const float& dt);
	// Render Functions
	void render(sf::RenderTarget* target = nullptr);
};
