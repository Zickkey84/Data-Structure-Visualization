#include "Program.h"


// Initializer functions
void Program::initWindow()
{
	std::ifstream fin("../Config/window.ini");
	std::string title = "";
	sf::VideoMode window_bounds(1440, 810);
	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;
	sf::Image iconIM;
	if (!iconIM.loadFromFile("../Resources/Images/IconIM.png")) {
		std::cerr << "Error when loading icon image\n";
	}
	if (fin.is_open()) {
		std::getline(fin, title);
		fin >> window_bounds.width >> window_bounds.height;
		fin >> framerate_limit;
		fin >> vertical_sync_enabled;
		fin.close();
	}

	this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Close | sf::Style::Titlebar);
	this->window->setIcon(iconIM.getSize().x, iconIM.getSize().y, iconIM.getPixelsPtr());
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Program::initState()
{
	this->states.push(new MainMenuState(this->window, &this->states));
}

// Constructor / Destructor
Program::Program()
{
	this->initWindow();
	this->initState();
}

Program::~Program()
{
	delete this->window;
	while (!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}
}

// Functions 
const bool Program::running() const
{
	return this->window->isOpen();
}


// Update
void Program::updateDT()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Program::pollEvents()
{
	while (this->window->pollEvent(this->evnt)) {
		if (this->evnt.type == sf::Event::Closed) this->window->close();
	}
}

void Program::update()
{
	this->pollEvents();

	if (!this->states.empty()) {
		this->states.top()->update(this->dt);
		if (this->states.top()->getEnd()) {
			//this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else this->window->close();

}

// Render
void Program::render()
{
	this->window->clear(sf::Color(224, 236, 254));

	if (!this->states.empty()) this->states.top()->render();

	this->window->display();
}

// Core
void Program::run()
{
	while (this->window->isOpen()) {
		this->updateDT();
		this->update();
		this->render();
	}
}
