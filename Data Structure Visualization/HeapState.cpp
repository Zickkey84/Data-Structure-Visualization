#include "HeapState.h"

HeapState::HeapState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	this->initBackground();
	this->initFont();
	this->initButton();
}

HeapState::~HeapState()
{
	delete this->BackButton;
	delete this->OperationButton;
	delete this->DoButton;
}

void HeapState::checkForEnd()
{
	if (this->BackButton->isPressed()) this->end = true;
}

void HeapState::initFont()
{
	if (!this->fonts["LexendDeca-Bold"].loadFromFile("../Resources/Font/Lexend Deca/LexendDeca-Bold.ttf")) {
		std::cerr << "Error loading LexendDeca Bold font!\n";
	}
	this->fonts["LexendDeca-Bold"].setSmooth(true);
	if (!this->fonts["LexendDeca-Regular"].loadFromFile("../Resources/Font/Lexend Deca/LexendDeca-Regular.ttf")) {
		std::cerr << "Error loading LexendDeca Regular font!\n";
	}
	this->fonts["LexendDeca-Regular"].setSmooth(true);
}

void HeapState::initBackground()
{
	if (!this->BackGroundTexture.loadFromFile("../Resources/Images/Heap Background.png")) {
		std::cerr << "Error loading Heap background!\n";
	}
	this->BackGroundSprite.setTexture(this->BackGroundTexture);
}

void HeapState::initButton()
{
	// Init Back Button
	this->BackButton = new gui::ImageButton(10.f, 10.f,
		"../Resources/Images/BackArrow.png", 
		"../Resources/Images/Hover_BackArrow.png");

	// Init Operation Button
	std::vector<std::string> list;
	list.push_back("Create");
	list.push_back("Insert");
	list.push_back("Delete");
	list.push_back("Get Top");
	list.push_back("Size");

	this->OperationButton = new gui::DropdownList(1055, 100, 150, 50, &this->fonts["LexendDeca-Bold"], list,
		sf::Color(49, 53, 110), 22, sf::Color(205, 214, 255), sf::Color(49, 53, 110), 1, sf::Color(0, 71, 255), sf::Color(0, 10, 246));

		// Init Do Button
	
	this->DoButton = new gui::Button(1210, 100, 150, 50, "DO", &this->fonts["LexendDeca-Bold"],
		sf::Color(49, 53, 110), 22, sf::Color(205, 214, 255), sf::Color(49, 53, 110), 1, sf::Color(0, 71, 255), sf::Color(0, 10, 246));
}


void HeapState::updateKeybinds(const float& dt)
{
	this->checkForEnd();

}

void HeapState::updateOperationState()
{
	std::string state = this->OperationButton->getActiveEle();
	if (state == "Create") this->operationState = Create;
	else if (state == "Insert") this->operationState = Insert;
	else if (state == "Delete") this->operationState = Delete;
	else if (state == "Get Top") this->operationState = GetTop;
	else if (state == "Size") this->operationState = Size;
}

void HeapState::update(const float& dt)
{
	this->updateMousePos();
	this->updateKeybinds(dt);
	this->BackButton->update({ (float)this->MousePos.x, (float)this->MousePos.y });
	this->OperationButton->update({ (float)this->MousePos.x, (float)this->MousePos.y }, dt);
	this->DoButton->update({ (float)this->MousePos.x, (float)this->MousePos.y });
	this->updateOperationState();
}

void HeapState::render(sf::RenderTarget* target)
{
	if (!target) target = this->window;
	target->draw(this->BackGroundSprite);
	this->BackButton->render(*target);
	this->OperationButton->render(*target);
	this->DoButton->render(*target);
}
