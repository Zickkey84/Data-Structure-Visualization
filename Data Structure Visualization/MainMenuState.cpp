#include "MainMenuState.h"

void MainMenuState::initBackground()
{
	if (!this->backgroundTexture.loadFromFile("../Resources/Images/Main Screen Background.png")) {
		std::cerr << "Error loading main-screen background!\n";
	}
	this->backgroundSprite.setTexture(backgroundTexture);
}

void MainMenuState::initFont()
{
	if (!this->font.loadFromFile("../Resources/Font/Lexend Deca/LexendDeca-Regular.ttf")) {
		std::cerr << "Error loading button font!\n";
	}
}

void MainMenuState::initButton()
{
	this->buttons["Heap_Button"] = new Button(168, 365, 288, 162, "Heap", &this->font,
		sf::Color(49, 53, 110), 32, sf::Color(185, 219, 244), sf::Color(49, 53, 110), 3, sf::Color(0, 71, 255), sf::Color(0, 16, 246));
	this->buttons["Hash_Table_Button"] = new Button(168, 595, 288, 162, "Hash Table", &this->font,
		sf::Color(49, 53, 110), 30, sf::Color(185, 219, 244), sf::Color(49, 53, 110), 3, sf::Color(0, 71, 255), sf::Color(0, 16, 246));
	this->buttons["AVL_Button"] = new Button(576, 365, 288, 162, "AVL Tree", &this->font,
		sf::Color(49, 53, 110), 30, sf::Color(185, 219, 244), sf::Color(49, 53, 110), 3, sf::Color(0, 71, 255), sf::Color(0, 16, 246));
	this->buttons["Tree234_Button"] = new Button(576, 595, 288, 162, "234 Tree", &this->font,
		sf::Color(49, 53, 110), 30, sf::Color(185, 219, 244), sf::Color(49, 53, 110), 3, sf::Color(0, 71, 255), sf::Color(0, 16, 246));
	this->buttons["Trie_Button"] = new Button(984, 365, 288, 162, "Trie", &this->font,
		sf::Color(49, 53, 110), 32, sf::Color(185, 219, 244), sf::Color(49, 53, 110), 3, sf::Color(0, 71, 255), sf::Color(0, 16, 246));
	this->buttons["Graph_Button"] = new Button(984, 595, 288, 162, "Graph", &this->font,
		sf::Color(49, 53, 110), 32, sf::Color(185, 219, 244), sf::Color(49, 53, 110), 3, sf::Color(0, 71, 255), sf::Color(0, 16, 246));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{

	this->initBackground();
	this->initFont();
	this->initButton();
	
}


MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it; it != this->buttons.end(); it++) {
		delete it->second;
	}
}

void MainMenuState::updateButton()
{
	for (auto& it : this->buttons) {
		it.second->update({ (float)this->MousePos.x, (float)this->MousePos.y });
	}

	if (this->buttons["Heap_Button"]->isPressed()) {
		this->states->push(new HeapState(this->window, this->states));
	}
}

void MainMenuState::renderButton(sf::RenderTarget* target)
{
	for (auto &it : this->buttons) {
		it.second->render(target);
	}
}


void MainMenuState::updateKeybinds(const float& dt)
{
	//this->checkForEnd();
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePos();
	this->updateKeybinds(dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) std::cout << "A\n";
	this->updateButton();
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target) target = this->window;
	target->draw(this->backgroundSprite);
	this->renderButton(target);
}
