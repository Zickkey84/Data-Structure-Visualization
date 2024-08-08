#include "MainMenuState.h"


void MainMenuState::initBackground()
{
	if (!this->backgroundTexture.loadFromFile("../Resources/Images/Main Screen Background.png")) {
		std::cerr << "Error loading main-screen background!\n";
	}
	if (!this->DM_backgroundTexture.loadFromFile("../Resources/Images/Main Screen Background - DM.png")) {
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
	if (!DarkMode) {
		// Init Dark Mode Button
		this->darkmodeButton = new gui::ImageButton(1376.f, 10.f,
			"../Resources/Images/MS_DarkModeButton.png",
			"../Resources/Images/Hover_MS_DarkModeButton.png",
			"../Resources/Images/MS_DarkModeButton - DM.png",
			"../Resources/Images/Hover_MS_DarkModeButton - DM.png");

		// Init State Button
		this->buttons["Heap_Button"] = new gui::Button(168, 365, 288, 162, "Heap", &this->font,
			sf::Color(49, 53, 110), 32, sf::Color(185, 219, 244), sf::Color(49, 53, 110), 3, sf::Color(0, 71, 255), sf::Color(0, 16, 246),
			sf::Color(185, 219, 244), sf::Color(49, 53, 110), sf::Color(185, 219, 244));
		this->buttons["Hash_Table_Button"] = new gui::Button(168, 595, 288, 162, "Hash Table", &this->font,
			sf::Color(49, 53, 110), 30, sf::Color(185, 219, 244), sf::Color(49, 53, 110), 3, sf::Color(0, 71, 255), sf::Color(0, 16, 246),
			sf::Color(185, 219, 244), sf::Color(49, 53, 110), sf::Color(185, 219, 244));
		this->buttons["AVL_Button"] = new gui::Button(576, 365, 288, 162, "AVL Tree", &this->font,
			sf::Color(49, 53, 110), 30, sf::Color(185, 219, 244), sf::Color(49, 53, 110), 3, sf::Color(0, 71, 255), sf::Color(0, 16, 246),
			sf::Color(185, 219, 244), sf::Color(49, 53, 110), sf::Color(185, 219, 244));
		this->buttons["Tree234_Button"] = new gui::Button(576, 595, 288, 162, "234 Tree", &this->font,
			sf::Color(49, 53, 110), 30, sf::Color(185, 219, 244), sf::Color(49, 53, 110), 3, sf::Color(0, 71, 255), sf::Color(0, 16, 246),
			sf::Color(185, 219, 244), sf::Color(49, 53, 110), sf::Color(185, 219, 244));
		this->buttons["Trie_Button"] = new gui::Button(984, 365, 288, 162, "Trie", &this->font,
			sf::Color(49, 53, 110), 32, sf::Color(185, 219, 244), sf::Color(49, 53, 110), 3, sf::Color(0, 71, 255), sf::Color(0, 16, 246),
			sf::Color(185, 219, 244), sf::Color(49, 53, 110), sf::Color(185, 219, 244));
		this->buttons["Graph_Button"] = new gui::Button(984, 595, 288, 162, "Graph", &this->font,
			sf::Color(49, 53, 110), 32, sf::Color(185, 219, 244), sf::Color(49, 53, 110), 3, sf::Color(0, 71, 255), sf::Color(0, 16, 246),
			sf::Color(185, 219, 244), sf::Color(49, 53, 110), sf::Color(185, 219, 244));
	}
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states, bool DarkMode) : State(window, states, DarkMode)
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
	delete this->darkmodeButton;
}

void MainMenuState::updateDarkMode(const float& dt)
{
	if (this->darkmodeButton->isPressed()) this->DarkMode = !this->DarkMode;
	this->darkmodeButton->update({ (float)this->MousePos.x, (float)this->MousePos.y }, dt, this->DarkMode);
	if (DarkMode) this->backgroundSprite.setTexture(DM_backgroundTexture);
	else this->backgroundSprite.setTexture(backgroundTexture);
}

void MainMenuState::updateButton(const float& dt)
{
	for (auto& it : this->buttons) {
		it.second->update({ (float)this->MousePos.x, (float)this->MousePos.y }, this->DarkMode);
	}

	if (this->buttons["Heap_Button"]->isPressed()) {
		this->states->push(new HeapState(this->window, this->states, this->DarkMode));
	}
	else if (this->buttons["Trie_Button"]->isPressed()) {
		this->states->push(new TrieState(this->window, this->states, this->DarkMode));
	}
	else if (this->buttons["Hash_Table_Button"]->isPressed()) {
		this->states->push(new HashState(this->window, this->states, this->DarkMode));
	}
	else if (this->buttons["AVL_Button"]->isPressed()) {
		this->states->push(new AVLState(this->window, this->states, this->DarkMode));
	}
	else if (this->buttons["Tree234_Button"]->isPressed()) {
		this->states->push(new Tree234State(this->window, this->states, this->DarkMode));
	}
	else if (this->buttons["Graph_Button"]->isPressed()) {
		this->states->push(new GraphState(this->window, this->states, this->DarkMode));
	}
}

void MainMenuState::renderButton(sf::RenderTarget* target)
{
	for (auto &it : this->buttons) {
		it.second->render(*target);
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
	this->updateDarkMode(dt);
	this->updateButton(dt);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target) target = this->window;
	target->draw(this->backgroundSprite);
	this->renderButton(target);
	this->darkmodeButton->render(*target);
}
