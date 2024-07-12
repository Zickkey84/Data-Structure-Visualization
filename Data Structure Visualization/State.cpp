#include "State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
	this->window = window;
	this->states = states;
	this->end = false;
}

State::~State()
{
}

const bool& State::getEnd() const
{
	return this->end;
}

void State::checkForEnd()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->end = true;
	}
}

void State::updateMousePos()
{
	this->MousePos = sf::Mouse::getPosition(*this->window);
	system("cls");
}
