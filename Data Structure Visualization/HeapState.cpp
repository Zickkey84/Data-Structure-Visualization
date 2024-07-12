#include "HeapState.h"

HeapState::HeapState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	this->initBackground();
	this->initFont();
	this->initGUI();
	this->initText();
}

HeapState::~HeapState()
{
	// Button
	delete this->BackButton;
	delete this->OperationButton;
	delete this->DoButton;

	// Text Box
	delete this->InputManuallyValue;
	delete this->InputRandomValue;
	delete this->EnterTheValue;

	// Text
	delete this->EnterTheVal;
	delete this->NumberOfVal;

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

void HeapState::initGUI()
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

	this->OperationButton = new gui::DropdownList(1055, 100, 172, 50, &this->fonts["LexendDeca-Bold"], list,
		sf::Color(49, 53, 110), 22, sf::Color(205, 214, 255), sf::Color(49, 53, 110), 1, sf::Color(0, 71, 255), sf::Color(0, 10, 246));

	
	// Init Create Type Button
	std::vector<std::string> typelist;
	typelist.push_back("Manually");
	typelist.push_back("Random");
	typelist.push_back("File");

	this->CreateType = new gui::DropdownList(1055, 155, 350, 50, &this->fonts["LexendDeca-Bold"], typelist,
		sf::Color(49, 53, 110), 22, sf::Color(205, 214, 255), sf::Color(49, 53, 110), 1, sf::Color(0, 71, 255), sf::Color(0, 10, 246));

	// Init Do Button

	this->DoButton = new gui::Button(1232, 100, 172, 50, "DO", &this->fonts["LexendDeca-Bold"],
		sf::Color(49, 53, 110), 22, sf::Color(205, 214, 255), sf::Color(49, 53, 110), 1, sf::Color(0, 71, 255), sf::Color(0, 10, 246));

	// Init Manually Input Value Box

	this->InputManuallyValue = new gui::TextBox(1055, 210, 350, 50, &this->fonts["LexendDeca-Regular"],
		3, sf::Color(49, 53, 110), sf::Color::White, sf::Color(49, 53, 110), sf::Color(49, 53, 110));

	// Init Random Number of Val Box

	this->InputRandomValue = new gui::TextBox(1327, 210, 75, 50, &this->fonts["LexendDeca-Regular"],
		3, sf::Color(49, 53, 110), sf::Color::White, sf::Color(49, 53, 110), sf::Color(49, 53, 110));

	// Init Enter The Value Box
	this->EnterTheValue = new gui::TextBox(1322, 155, 75, 50, &this->fonts["LexendDeca-Regular"],
		3, sf::Color(49, 53, 110), sf::Color::White, sf::Color(49, 53, 110), sf::Color(49, 53, 110));
}

void HeapState::initText()
{
	this->NumberOfVal = new sf::Text("Number Of Value (Max 40): ", this->fonts["LexendDeca-Regular"], 20);
	this->NumberOfVal->setPosition(sf::Vector2f(1055, 220));
	this->NumberOfVal->setFillColor(sf::Color(49, 53, 110));

	this->EnterTheVal = new sf::Text("Enter The Value: ", this->fonts["LexendDeca-Regular"], 30);
	this->EnterTheVal->setPosition(sf::Vector2f(1060, 160));
	this->EnterTheVal->setFillColor(sf::Color(49, 53, 110));
}


void HeapState::updateKeybinds(const float& dt)
{
	this->checkForEnd();

}

void HeapState::updateOperationState()
{
	std::string OpeState = this->OperationButton->getActiveEle();
	if (OpeState == "Create") {
		this->operationState = Create;

		std::string CrState = this->CreateType->getActiveEle();
		if (CrState == "Manually") this->createState = Manually;
		else if (CrState == "Random") this->createState = Random;
		else if (CrState == "File") this->createState = File;
	}
	else if (OpeState == "Insert") this->operationState = Insert;
	else if (OpeState == "Delete") this->operationState = Delete;
	else if (OpeState == "Get Top") this->operationState = GetTop;
	else if (OpeState == "Size") this->operationState = Size;

}

void HeapState::update(const float& dt) {
	this->updateMousePos();
	this->updateKeybinds(dt);
	this->BackButton->update({ (float)this->MousePos.x, (float)this->MousePos.y });
	this->OperationButton->update({ (float)this->MousePos.x, (float)this->MousePos.y }, dt);
	this->updateOperationState();
	if (this->operationState == Create) {
		this->CreateType->update({ (float)this->MousePos.x, (float)this->MousePos.y }, dt);
		if (this->createState == Manually) {
			sf::Event evnt;
			while (this->window->pollEvent(evnt)) {
				if (evnt.type == sf::Event::TextEntered || evnt.type == sf::Event::MouseButtonPressed)
					this->InputManuallyValue->update({ (float)this->MousePos.x, (float)this->MousePos.y }, evnt);
				if (evnt.type == sf::Event::Closed) this->window->close();
			}
		}
		if (this->createState == Random) {
			sf::Event evnt;
			while (this->window->pollEvent(evnt)) {
				if (evnt.type == sf::Event::TextEntered || evnt.type == sf::Event::MouseButtonPressed)
					this->InputRandomValue->update({ (float)this->MousePos.x, (float)this->MousePos.y }, evnt);
				if (evnt.type == sf::Event::Closed) this->window->close();
			}
		}
	}
	if (this->operationState == Insert || this->operationState == Delete) {
		sf::Event evnt;
		while (this->window->pollEvent(evnt)) {
			if (evnt.type == sf::Event::TextEntered || evnt.type == sf::Event::MouseButtonPressed)
				this->EnterTheValue->update({ (float)this->MousePos.x, (float)this->MousePos.y }, evnt);
			if (evnt.type == sf::Event::Closed) this->window->close();
		}
	}
	this->DoButton->update({ (float)this->MousePos.x, (float)this->MousePos.y });
}

void HeapState::render(sf::RenderTarget* target)
{
	if (!target) target = this->window;
	target->draw(this->BackGroundSprite);
	this->BackButton->render(*target);
	if (this->operationState == Create && this->createState == Manually) {
		this->InputManuallyValue->render(*target);
	}
	if (this->operationState == Create && this->createState == Random) {
		target->draw(*this->NumberOfVal);
		this->InputRandomValue->render(*target);
	}
	if (this->operationState == Create) {
		this->CreateType->render(*target);
	}
	if (this->operationState == Insert || this->operationState == Delete) {
		target->draw(*this->EnterTheVal);
		this->EnterTheValue->render(*target);
	}
	this->OperationButton->render(*target);
	this->DoButton->render(*target);
}
