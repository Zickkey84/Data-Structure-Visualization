#include "HashState.h"

HashState::HashState(sf::RenderWindow* window, std::stack<State*>* states, bool DarkMode) : State(window, states, DarkMode)
{
	this->initBackground();
	this->initFont();
	this->initGUI();
	this->initText();
	this->initHashGraph();
}

HashState::~HashState()
{
	// Button
	delete this->BackButton;
	delete this->OperationButton;
	delete this->CreateType;
	delete this->Speed;
	delete this->DoButton;

	// Text Box
	delete this->InputRandomValue;
	delete this->EnterTheValue;

	// Text
	delete this->EnterTheVal;
	delete this->NumberOfVal;
	delete this->noti;
	delete this->code;

	delete this->hash;
	delete this->hashGraph;
}

void HashState::checkForEnd()
{
	if (this->BackButton->isPressed()) this->end = true;
}

void HashState::initFont()
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

void HashState::initBackground()
{
	if (this->DarkMode) {
		if (!this->BackGroundTexture.loadFromFile("../Resources/Images/HashTable Background - DM.png"))
			std::cerr << "Error loading HashTable background!\n";
	}
	else {
		if (!this->BackGroundTexture.loadFromFile("../Resources/Images/HashTable Background.png"))
			std::cerr << "Error loading HashTable background!\n";
	}
	this->BackGroundSprite.setTexture(this->BackGroundTexture);
}

void HashState::initGUI()
{
	// Init Back Button
	this->BackButton = new gui::ImageButton(10.f, 10.f,
		"../Resources/Images/BackArrow.png",
		"../Resources/Images/Hover_BackArrow.png",
		"../Resources/Images/BackArrow - DM.png",
		"../Resources/Images/Hover_BackArrow - DM.png");

	// Init Operation Button
	std::vector<std::string> list;
	list.push_back("Create");
	list.push_back("Insert");
	list.push_back("Delete");
	list.push_back("Search");
 
	this->OperationButton = new gui::DropdownList(1055, 100, 172, 50, &this->fonts["LexendDeca-Bold"], list,
		sf::Color(49, 53, 110), 22, LightBlue, sf::Color(49, 53, 110), 1, HoverBlue, PressBlue,
		LightBlue, sf::Color(49, 53, 110), LightBlue);

	// Init Create Type Button
	std::vector<std::string> typelist;
	typelist.push_back("Random");
	typelist.push_back("File");

	this->CreateType = new gui::DropdownList(1055, 155, 350, 50, &this->fonts["LexendDeca-Bold"], typelist,
		sf::Color(49, 53, 110), 22, LightBlue, sf::Color(49, 53, 110), 1, HoverBlue, PressBlue,
		LightBlue, sf::Color(49, 53, 110), LightBlue);

	// Init Speed Button
	std::vector<std::string> speedlist;
	speedlist.push_back("1x");
	speedlist.push_back("0.5x");
	speedlist.push_back("0.75x");
	speedlist.push_back("1.5x");
	speedlist.push_back("2x");

	this->Speed = new gui::DropdownList(1055, 215, 350, 50, &this->fonts["LexendDeca-Bold"], speedlist,
		sf::Color(49, 53, 110), 22, LightBlue, sf::Color(49, 53, 110), 1, HoverBlue, PressBlue,
		LightBlue, sf::Color(49, 53, 110), LightBlue);

	// Init Do Button

	this->DoButton = new gui::Button(1232, 100, 172, 50, "DO", &this->fonts["LexendDeca-Bold"],
		sf::Color(49, 53, 110), 22, LightBlue, sf::Color(49, 53, 110), 1, HoverBlue, PressBlue,
		LightBlue, sf::Color(49, 53, 110), LightBlue);

	// Init Input File Button

	this->InputFileButton = new gui::Button(1055, 210, 350, 50, "Input File", &this->fonts["LexendDeca-Bold"],
		sf::Color(49, 53, 110), 22, LightBlue, sf::Color(49, 53, 110), 1, HoverBlue, PressBlue,
		LightBlue, sf::Color(49, 53, 110), LightBlue);

	// Init Random Number of Val Box

	this->InputRandomValue = new gui::TextBox(1327, 210, 75, 50, &this->fonts["LexendDeca-Regular"],
		3, sf::Color(49, 53, 110), sf::Color::White, sf::Color(49, 53, 110), sf::Color(49, 53, 110));

	// Init Enter The Value Box
	this->EnterTheValue = new gui::TextBox(1322, 155, 75, 50, &this->fonts["LexendDeca-Regular"],
		3, sf::Color(49, 53, 110), sf::Color::White, sf::Color(49, 53, 110), sf::Color(49, 53, 110));

	// Init Arrow
	this->arrow.setPointCount(3);
	this->arrow.setPoint(0, sf::Vector2f(0, 0));
	this->arrow.setPoint(1, sf::Vector2f(0, 20));
	this->arrow.setPoint(2, sf::Vector2f(-20, 10));
	if (DarkMode) this->arrow.setFillColor(LightBlue);
	else this->arrow.setFillColor(DarkBlue);
	this->arrow.setOrigin(sf::Vector2f(-20, 10));

}

void HashState::initText()
{
	this->NumberOfVal = new sf::Text("Number Of Value (Max 50): ", this->fonts["LexendDeca-Regular"], 20);
	this->NumberOfVal->setPosition(sf::Vector2f(1055, 220));

	this->EnterTheVal = new sf::Text("Enter The Value: ", this->fonts["LexendDeca-Regular"], 30);
	this->EnterTheVal->setPosition(sf::Vector2f(1060, 160));

	this->noti = new sf::Text("", this->fonts["LexendDeca-Regular"], 20);
	this->noti->setPosition(sf::Vector2f(1150, 490));

	this->code = new sf::Text("", this->fonts["LexendDeca-Regular"], 18);
	this->code->setPosition(sf::Vector2f(1070, 555));
	if (DarkMode) {
		this->NumberOfVal->setFillColor(LightBlue);
		this->EnterTheVal->setFillColor(LightBlue);
		this->noti->setFillColor(LightBlue);
		this->code->setFillColor(LightBlue);
	}
	else {
		this->NumberOfVal->setFillColor(DarkBlue);
		this->EnterTheVal->setFillColor(DarkBlue);
		this->noti->setFillColor(DarkBlue);
		this->code->setFillColor(DarkBlue);
	}
}

void HashState::initHashGraph()
{
	this->hash = new Hash();
	for (int i = 0; i < hash->capacity; i++) hash->hashArr.push_back(-1);
	this->hashGraph = new HashGraph(sf::Vector2f(150, 270), &this->fonts["LexendDeca-Regular"], this->hash, colorTheme(this->DarkMode), 45.f, 2.f);
}


void HashState::updateKeybinds(const float& dt)
{
	this->checkForEnd();

}

void HashState::updateOperationState()
{
	std::string OpeState = this->OperationButton->getActiveEle();
	if (OpeState == "Create") {
		this->operationState = Create;
		this->code->setString("");
		std::string CrState = this->CreateType->getActiveEle();
		if (CrState == "Random") this->createState = Random;
		else if (CrState == "File") this->createState = File;
	}
	else if (OpeState == "Insert") {
		this->operationState = Insert;
		this->code->setString(INSERT_HASH);
	}
	else if (OpeState == "Delete") {
		this->operationState = Delete;
		this->code->setString(DELETE_HASH);
	}
	else if (OpeState == "Search") {
		this->operationState = Search;
		this->code->setString(SEARCH_HASH);
	}

}

void HashState::updateNoti()
{
	OperationState x;
	std::string OpeState = this->OperationButton->getActiveEle();
	if (OpeState == "Create") x = Create;
	else if (OpeState == "Insert") x = Insert;
	else if (OpeState == "Delete") x = Delete;
	else if (OpeState == "Search") x = Search;

	if (x != this->operationState) {
		this->noti->setString("");
		this->arrowState = None;
	}
}

void HashState::updateSpeed()
{
	std::string speed = this->Speed->getActiveEle();
	if (speed == "0.5x") this->speed = 0.5f;
	else if (speed == "0.75x") this->speed = 0.75f;
	else if (speed == "1x") this->speed = 1.f;
	else if (speed == "1.5x") this->speed = 1.5f;
	else this->speed = 2.f;
}

void HashState::update(const float& dt) {
	this->updateMousePos();
	this->updateKeybinds(dt);
	this->BackButton->update({ (float)this->MousePos.x, (float)this->MousePos.y }, dt, this->DarkMode);
	this->OperationButton->update({ (float)this->MousePos.x, (float)this->MousePos.y }, dt, this->DarkMode);
	this->updateNoti();
	this->updateSpeed();
	this->updateOperationState();
	if (this->operationState == Create) {
		this->CreateType->update({ (float)this->MousePos.x, (float)this->MousePos.y }, dt, this->DarkMode);
		if (this->createState == Random) {
			sf::Event evnt;
			while (this->window->pollEvent(evnt)) {
				if (evnt.type == sf::Event::TextEntered || evnt.type == sf::Event::MouseButtonPressed)
					this->InputRandomValue->update({ (float)this->MousePos.x, (float)this->MousePos.y }, evnt);
				if (evnt.type == sf::Event::Closed) this->window->close();
			}
		}
		if (this->createState == File) {
			this->InputFileButton->update({ (float)this->MousePos.x, (float)this->MousePos.y }, dt, this->DarkMode);
			if (this->InputFileButton->isPressed()) {
				std::string currentDir = getCurrentWorkingDirectory();
				this->FileName = OpenFileDialog();
				sf::Text fileName;
				fileName.setFont(this->fonts["LexendDeca-Regular"]);
				fileName.setString(GetNameFileDialog(this->FileName));
				fileName.setCharacterSize(22);
				fileName.setFillColor(sf::Color(49, 53, 110));
				this->InputFileButton->setText(fileName);
				setCurrentWorkingDirectory(currentDir);
			}
		}
	}
	if (this->operationState == Insert || this->operationState == Delete || this->operationState == Search) {
		this->Speed->update({ (float)this->MousePos.x, (float)this->MousePos.y }, dt, this->DarkMode);
		sf::Event evnt;
		while (this->window->pollEvent(evnt)) {
			if (evnt.type == sf::Event::TextEntered || evnt.type == sf::Event::MouseButtonPressed)
				this->EnterTheValue->update({ (float)this->MousePos.x, (float)this->MousePos.y }, evnt);
			if (evnt.type == sf::Event::Closed) this->window->close();
		}
	}
	this->DoButton->update({ (float)this->MousePos.x, (float)this->MousePos.y }, dt, this->DarkMode);
	if (this->DoButton->isPressed()) {
		switch (this->operationState) {
		case Create:
		{
			Hash a; int x = 0;
			if (this->createState == File) {
				std::ifstream fin;
				fin.open(this->FileName);
				if (fin.is_open()) {
					fin >> a.size;
					for (int i = 0; i < a.capacity; i++) a.hashArr.push_back(-1);
					while (fin >> x) a.Insert(x);
					fin.close();
				}
				else std::cout << "Error open input file!";
			}
			if (this->createState == Random) {
				x = this->InputRandomValue->getInput();
				if (x <= 50 && x > 0) {
					a.size = x;
					for (int i = 0; i < a.capacity; i++) a.hashArr.push_back(-1);
					int n = rand() % x;
					for (int i = 0; i < n; i++) {
						a.Insert(rand() % 1000);
					}
				}
			}
			*this->hash = a;
			break;
		}
		case Insert:
		{
			if (this->EnterTheValue->getString() != "") {
				this->input = this->EnterTheValue->getInput();
				this->hashIndex = this->hash->hashCode(this->input);
				this->noti->setString(std::to_string(input) + " mod "
					+ std::to_string(this->hash->size) + " = " + std::to_string(this->hashIndex));
				this->inserting = true;
				this->noti->setPosition(sf::Vector2f(1150, 490));
			}
			break;
		}
		case Delete:
		{
			if (this->EnterTheValue->getString() != "") {
				this->input = this->EnterTheValue->getInput();
				this->hashIndex = this->hash->hashCode(this->input);
				this->noti->setString(std::to_string(input) + " mod "
					+ std::to_string(this->hash->size) + " = " + std::to_string(this->hashIndex));
				this->noti->setPosition(sf::Vector2f(1150, 490));
				this->deleting = true;
			}
			break;
		}
		case Search:
		{
			if (this->EnterTheValue->getString() != "") {
				this->input = this->EnterTheValue->getInput();
				this->hashIndex = this->hash->hashCode(this->input);
				this->noti->setString(std::to_string(input) + " mod "
					+ std::to_string(this->hash->size) + " = " + std::to_string(this->hashIndex));
				this->noti->setPosition(sf::Vector2f(1150, 490));
				this->searching = true;
			}
			break;
		}
		default:
			break;
		}
		this->hashGraph->update();
	}
}

void HashState::render(sf::RenderTarget* target)
{
	if (!target) target = this->window;
	target->draw(this->BackGroundSprite);
	this->BackButton->render(*target);
	if (this->operationState == Create && this->createState == Random) {
		target->draw(*this->NumberOfVal);
		this->InputRandomValue->render(*target);
	}
	if (this->operationState == Create && this->createState == File) {
		this->InputFileButton->render(*target);
	}
	if (this->operationState == Create) {
		this->CreateType->render(*target);
	}
	if (this->operationState == Insert || this->operationState == Delete || this->operationState == Search) {
		target->draw(*this->EnterTheVal);
		this->EnterTheValue->render(*target);
		this->Speed->render(*target);
	}
	this->OperationButton->render(*target);
	this->DoButton->render(*target);
	if (this->inserting) {
		this->arrow.setPosition({ 1350,590 });
		this->arrowState = Searching;
		this->hashGraph->Nodes[hashIndex]->setHighlight(sf::Color::Red, this->hashGraph->thickness * 2);
		this->hashGraph->render(*target);
		sf::sleep(sf::seconds(0.75f / speed));
		if (this->hashGraph->Nodes[hashIndex]->getText() != "") {
			this->hashGraph->Nodes[hashIndex]->setHighlight(this->hashGraph->borderColor, this->hashGraph->thickness);
			hashIndex = (hashIndex + 1) % this->hash->size;
			if (hashIndex == 0) {
				this->arrowState = ZeroIndex;
				this->arrow.setPosition({ 1350,620 });
			}if (hashIndex == this->hash->hashCode(this->input)) {
				this->inserting = false;
				this->arrow.setPosition({ 1350,685 });
				this->arrowState = NotFound;
				this->noti->setString(" The Hash Tabel is full");
				this->noti->setPosition(sf::Vector2f(1110, 490));
			}
		}
		else {
			this->arrow.setPosition({ 1350,735 }); this->arrowState = Found;
			this->hash->Insert(this->input);
			this->inserting = false;
			this->hashGraph->update();
			this->hashGraph->Nodes[hashIndex]->setHighlight(sf::Color::Yellow, this->hashGraph->thickness * 2);
			this->noti->setString(std::to_string(input) + " was inserted at index " + std::to_string(this->hashIndex));
			this->noti->setPosition(sf::Vector2f(1110, 490));
		}
	}
	else if (this->deleting) {
		this->arrow.setPosition({ 1350,590 });
		this->arrowState = Searching;
		this->hashGraph->Nodes[hashIndex]->setHighlight(sf::Color::Red, this->hashGraph->thickness * 2);
		this->hashGraph->render(*target);
		sf::sleep(sf::seconds(0.75f / speed));
		if (this->hashGraph->Nodes[hashIndex]->getText() != std::to_string(input)) {
			this->hashGraph->Nodes[hashIndex]->setHighlight(this->hashGraph->borderColor, this->hashGraph->thickness);
			hashIndex = (hashIndex + 1) % this->hash->size;
			if (hashIndex == 0) {
				this->arrowState = ZeroIndex;
				this->arrow.setPosition({ 1350,620 });
			}if (hashIndex == this->hash->hashCode(this->input)) {
				this->deleting = false;
				this->arrow.setPosition({ 1350,685 });
				this->arrowState = NotFound;
				this->noti->setString(std::to_string(input) + " isn't in the Hash Table ");
				this->noti->setPosition(sf::Vector2f(1110, 490));
			}
		}
		else {
			this->arrow.setPosition({ 1350,735 }); this->arrowState = Found;
			this->hash->Delete(this->input);
			this->deleting = false;
			this->hashGraph->update();
			this->hashGraph->Nodes[hashIndex]->setHighlight(sf::Color::Yellow, this->hashGraph->thickness * 2);
			this->noti->setString(std::to_string(input) + " at index " + std::to_string(this->hashIndex) + " was deleted ");
			this->noti->setPosition(sf::Vector2f(1110, 490));
		}
	}
	else if (this->searching) {
		this->arrow.setPosition({ 1350,590 });
		this->arrowState = Searching;
		this->hashGraph->Nodes[hashIndex]->setHighlight(sf::Color::Red, this->hashGraph->thickness * 2);
		this->hashGraph->render(*target);
		sf::sleep(sf::seconds(0.75f / speed));
		if (this->hashGraph->Nodes[hashIndex]->getText() != std::to_string(input)) {
			this->hashGraph->Nodes[hashIndex]->setHighlight(this->hashGraph->borderColor, this->hashGraph->thickness);
			hashIndex = (hashIndex + 1) % this->hash->size;
			if (hashIndex == 0) {
				this->arrowState = ZeroIndex;
				this->arrow.setPosition({ 1350,620 });
			}
			if (hashIndex == this->hash->hashCode(this->input)) {
				this->searching = false;
				this->arrow.setPosition({ 1350,675 });
				this->arrowState = NotFound;
				this->noti->setString(std::to_string(input) + " isn't in the Hash Table ");
				this->noti->setPosition(sf::Vector2f(1110, 490));
			}
		}
		else {
			this->arrow.setPosition({ 1350,735 }); this->arrowState = Found;
			this->searching = false;
			this->hashGraph->Nodes[hashIndex]->setHighlight(sf::Color::Yellow, this->hashGraph->thickness * 2);
			this->noti->setString(std::to_string(input) + " was found at index " + std::to_string(this->hashIndex));
			this->noti->setPosition(sf::Vector2f(1110, 490));
		}
	}
	else {
		if (this->hash->size != 0)
			this->hashGraph->render(*target);
	}
	target->draw(*this->noti); target->draw(*this->code);
	if (this->arrowState != None) target->draw(this->arrow);
}
