#include "HeapState.h"

HeapState::HeapState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	initBackButton();
}

HeapState::~HeapState()
{
	delete this->BackButton;
}

void HeapState::checkForEnd()
{
	if (this->BackButton->isPressed()) this->end = true;
}

void HeapState::initBackground()
{
}

void HeapState::initBackButton()
{
	this->BackButton = new ImageButton(10.f, 10.f, 
		"../Resources/Images/BackArrow.png", 
		"../Resources/Images/Hover_BackArrow.png");

}

void HeapState::updateKeybinds(const float& dt)
{
	this->checkForEnd();

}

void HeapState::update(const float& dt)
{
	this->updateMousePos();
	this->updateKeybinds(dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) std::cout << "A\n";
	this->BackButton->update({(float)this->MousePos.x, (float)this->MousePos.y});
}

void HeapState::render(sf::RenderTarget* target)
{
	if (!target) target = this->window;
	this->BackButton->render(target);
}
