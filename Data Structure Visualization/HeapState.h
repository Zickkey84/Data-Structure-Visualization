#pragma once

#include "State.h"
#include "ImageButton.h"
class HeapState : public State
{
private:
	ImageButton* BackButton;
public:
	HeapState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~HeapState();
	void checkForEnd();
	void initBackground();
	void initBackButton();
	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};
