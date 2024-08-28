#include "234TreeState.h"

Tree234State::Tree234State(sf::RenderWindow* window, std::stack<State*>* states, bool DarkMode) : State(window, states, DarkMode)
{
	this->initBackground();
	this->initFont();
	this->initGUI();
	this->initText();
	this->initGraph();
}

Tree234State::~Tree234State()
{
	// Button
	delete this->BackButton;
	delete this->OperationButton;
	delete this->DoButton;

	// Text Box
	delete this->InputRandomValue;
	delete this->EnterTheValue;

	// Text
	delete this->EnterTheVal;
	delete this->NumberOfVal;
	delete this->noti;
	delete this->code;

	delete this->graph;
}

void Tree234State::checkForEnd()
{
	if (this->BackButton->isPressed()) this->end = true;
}

void Tree234State::initFont()
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

void Tree234State::initBackground()
{
	if (this->DarkMode) {
		if (!this->BackGroundTexture.loadFromFile("../Resources/Images/234Tree Background - DM.png")) {
			std::cerr << "Error loading 234Tree background!\n";
		}
	}
	else {
		if (!this->BackGroundTexture.loadFromFile("../Resources/Images/234Tree Background.png")) {
			std::cerr << "Error loading 234Tree background!\n";
		}
	}
	this->BackGroundSprite.setTexture(this->BackGroundTexture);
}

void Tree234State::initGUI()
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
	this->arrow.setPoint(1, sf::Vector2f(0, 15));
	this->arrow.setPoint(2, sf::Vector2f(-15, 8));
	if (DarkMode) this->arrow.setFillColor(LightBlue);
	else this->arrow.setFillColor(DarkBlue);
	this->arrow.setOrigin(sf::Vector2f(-15, 8));
}


void Tree234State::initText()
{
	this->NumberOfVal = new sf::Text("Number Of Value (Max 35): ", this->fonts["LexendDeca-Regular"], 20);
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
		this->NumberOfVal->setFillColor(sf::Color(49, 53, 110));
		this->EnterTheVal->setFillColor(sf::Color(49, 53, 110));
		this->noti->setFillColor(DarkBlue);
		this->code->setFillColor(DarkBlue);
	}
}

void Tree234State::initGraph()
{
	this->graph = new Tree234Graph(sf::Vector2f(535, 200), &this->fonts["LexendDeca-Regular"], (colorTheme)this->DarkMode, 32.f, 2.f);
}


void Tree234State::updateKeybinds(const float& dt)
{
	this->checkForEnd();

}

void Tree234State::updateOperationState()
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
		this->code->setString(INSERT_234TREE);
		this->code->setCharacterSize(15);
		this->code->setPosition(sf::Vector2f(1070, 546));
	}
	else if (OpeState == "Delete") {
		this->operationState = Delete;
		this->code->setString(DELETE_234TREE);
		this->code->setCharacterSize(13);
		this->code->setPosition(sf::Vector2f(1070, 546));
	}
	else if (OpeState == "Search") {
		this->operationState = Search;
		this->code->setString(SEARCH_234TREE);
		this->code->setCharacterSize(15);
		this->code->setPosition(sf::Vector2f(1063, 575));
	}
}


void Tree234State::updateNoti()
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

void Tree234State::updateSpeed()
{
	std::string speed = this->Speed->getActiveEle();
	if (speed == "0.5x") this->speed = 0.5f;
	else if (speed == "0.75x") this->speed = 0.75f;
	else if (speed == "1x") this->speed = 1.f;
	else if (speed == "1.5x") this->speed = 1.5f;
	else this->speed = 2.f;
}

void Tree234State::update(const float& dt) {
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
		sf::Event evnt;
		while (this->window->pollEvent(evnt)) {
			if (evnt.type == sf::Event::TextEntered || evnt.type == sf::Event::MouseButtonPressed)
				this->EnterTheValue->update({ (float)this->MousePos.x, (float)this->MousePos.y }, evnt);
			if (evnt.type == sf::Event::Closed) this->window->close();
		}
	}
	if (this->operationState == Search) this->Speed->update({ (float)this->MousePos.x, (float)this->MousePos.y }, dt, this->DarkMode);
	this->DoButton->update({ (float)this->MousePos.x, (float)this->MousePos.y }, dt, this->DarkMode);
	if (this->DoButton->isPressed()) {
		switch (this->operationState) {
		case Create:
		{
			std::vector<int> a; int x = 0;
			if (this->createState == File) {
				std::ifstream fin;
				fin.open(this->FileName);
				if (fin.is_open()) {
					while (fin >> x) a.push_back(x);
					fin.close();
				}
				else std::cout << "Error open input file!";
			}
			if (this->createState == Random) {
				x = this->InputRandomValue->getInput();
				if (x <= 35) {
					a = generateRandomArray(x);
				}
			}
			if (!a.empty()) {
				size = a.size();
				this->graph->clear();
				for (auto it : a) this->graph->insert(it);
				this->graph->update();
			}
			break;
		}
		case Insert:
		{
			if (this->EnterTheValue->getString() != "") {
				if (size < 35) {
					int x = this->EnterTheValue->getInput();
					this->graph->insert(x);
					size++;
					this->noti->setString(std::to_string(x) + " was inserted!");
					this->noti->setPosition(sf::Vector2f(1150, 490));
					this->graph->update();
				}
				else {
					this->noti->setString("The 234Tree is full");
					this->noti->setPosition(sf::Vector2f(1135, 490));
				}
			}
			break;
		}
		case Delete:
		{
			if (this->EnterTheValue->getString() != "") {
				if (size > 0) {
					int x = this->EnterTheValue->getInput();
					if (this->graph->Delete(x)) {
						this->noti->setString(std::to_string(x) + " was deleted!");
						this->noti->setPosition(sf::Vector2f(1155, 490));
						size--;
						this->graph->update();
					}
					else {
						this->noti->setString(std::to_string(x) + " is not in 234Tree!");
						this->noti->setPosition(sf::Vector2f(1129, 490));
					}
				}
				else {
					this->noti->setString("The 234Tree is empty");
					this->noti->setPosition(sf::Vector2f(1125, 490));
				}
			}
			break;
		}
		case Search:
		{
			this->graph->update();
			if (this->EnterTheValue->getString() != "") {
				if (size > 0) {
					this->input = this->EnterTheValue->getInput();
					this->searching = true;
					this->idGroup = this->graph->root;
					this->noti->setString("Searching for " + std::to_string(input));
					this->noti->setPosition(sf::Vector2f(1160, 490));
					this->arrowState = Active;
				}
				else {
					this->noti->setString("The 234Tree is empty");
					this->noti->setPosition(sf::Vector2f(1125, 490));
				}
			}
			break;
		}
		default:
			break;
		}
	}
}

void Tree234State::render(sf::RenderTarget* target)
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
	}
	this->OperationButton->render(*target);
	this->DoButton->render(*target);
	if (this->operationState == Search) this->Speed->render(*target);
	this->graph->render(*target);
	if (this->searching) {
		if (idGroup == -1) {
			this->searching = false;
			this->noti->setString(std::to_string(input) + " is not found!");
			this->noti->setPosition(sf::Vector2f(1155, 490));
			this->arrow.setPosition(sf::Vector2f(1360, 697));
		}
		else {
			for (auto it : this->graph->groups[idGroup]->nodes) {
				this->graph->nodes[it]->setHighlight(sf::Color::Red, this->graph->nodes[it]->thickness);
				this->graph->nodes[it]->render(*target);
				this->graph->nodes[it]->setHighlight(this->graph->textColor, this->graph->nodes[it]->thickness);
				if (this->graph->nodes[it]->getValue() == input) {
					this->graph->nodes[it]->setHighlight(sf::Color::Yellow, this->graph->nodes[it]->thickness * 1.5f);
					this->graph->nodes[it]->render(*target);
					this->searching = false;
					this->noti->setString(std::to_string(input) + " is found!");
					this->noti->setPosition(sf::Vector2f(1170, 490));
					this->arrow.setPosition(sf::Vector2f(1360, 664));
				}
			}
			sf::sleep(sf::seconds(0.75 / speed));
			if (this->searching) {
				int nextIDgroup = this->graph->findEdge(idGroup, input);
				this->arrow.setPosition(sf::Vector2f(1360, 738));
				idGroup = nextIDgroup;
			}
		}
	}
	target->draw(*this->noti); target->draw(*this->code);
	if (this->arrowState != None) target->draw(this->arrow);
}
