#include "TrieState.h"

TrieState::TrieState(sf::RenderWindow* window, std::stack<State*>* states, bool DarkMode) : State(window, states, DarkMode)
{
	this->initBackground();
	this->initFont();
	this->initGUI();
	this->initText();
	this->initTrieGraph();
}

TrieState::~TrieState()
{
	// Button
	delete this->BackButton;
	delete this->OperationButton;
	delete this->DoButton;
	delete this->Speed;

	// Text Box
	delete this->InputRandomValue;
	delete this->EnterTheValue;

	// Text
	delete this->EnterTheVal;
	delete this->NumberOfVal;
	delete this->noti;
	delete this->code;

	delete this->trieGraph;
}

void TrieState::checkForEnd()
{
	if (this->BackButton->isPressed()) this->end = true;
}

void TrieState::initFont()
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

void TrieState::initBackground()
{
	if (this->DarkMode) {
		if (!this->BackGroundTexture.loadFromFile("../Resources/Images/Trie Background - DM.png")) {
			std::cerr << "Error loading Graph background!\n";
		}
	}
	else {
		if (!this->BackGroundTexture.loadFromFile("../Resources/Images/Trie Background.png")) {
			std::cerr << "Error loading Graph background!\n";
		}
	}
	this->BackGroundSprite.setTexture(this->BackGroundTexture);
}

void TrieState::initGUI()
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
	this->EnterTheValue = new gui::TextBox2(1280, 155, 120, 50, &this->fonts["LexendDeca-Regular"],
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


void TrieState::initText()
{
	this->NumberOfVal = new sf::Text("Number of String (Max 20): ", this->fonts["LexendDeca-Regular"], 20);
	this->NumberOfVal->setPosition(sf::Vector2f(1055, 220));

	this->EnterTheVal = new sf::Text("Enter The String:\nMax length is 6", this->fonts["LexendDeca-Regular"], 20);
	this->EnterTheVal->setPosition(sf::Vector2f(1060, 160));

	this->noti = new sf::Text("", this->fonts["LexendDeca-Regular"], 20);
	this->noti->setPosition(sf::Vector2f(1130, 490));

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

void TrieState::initTrieGraph()
{
	this->trieGraph = new TrieGraph(sf::Vector2f(600, 160), 22.f, 2.f, &this->fonts["LexendDeca-Regular"], colorTheme(this->DarkMode), 20);
}


void TrieState::updateKeybinds(const float& dt)
{
	this->checkForEnd();

}

void TrieState::updateOperationState()
{
	std::string OpeState = this->OperationButton->getActiveEle();
	if (OpeState == "Create") {
		this->operationState = Create;

		std::string CrState = this->CreateType->getActiveEle();
		if (CrState == "Random") this->createState = Random;
		else if (CrState == "File") this->createState = File;
	}
	else if (OpeState == "Insert") {
		this->operationState = Insert;
		this->code->setString(INSERT_TRIE);
		this->code->setCharacterSize(16);
	}
	else if (OpeState == "Delete") {
		this->operationState = Delete;
		this->code->setString(DELETE_TRIE);
		this->code->setCharacterSize(15);
	}
	else if (OpeState == "Search") {
		this->operationState = Search;
		this->code->setString(SEARCH_TRIE);
		this->code->setCharacterSize(16);
	}
}

void TrieState::updateNoti()
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

void TrieState::updateSpeed()
{
	std::string speed = this->Speed->getActiveEle();
	if (speed == "0.5x") this->speed = 0.5f;
	else if (speed == "0.75x") this->speed = 0.75f;
	else if (speed == "1x") this->speed = 1.f;
	else if (speed == "1.5x") this->speed = 1.5f;
	else this->speed = 2.f;
}

void TrieState::update(const float& dt) {
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
			this->trieGraph->clear();
			if (this->createState == File) {
				std::ifstream fin;
				fin.open(this->FileName);
				if (fin.is_open()) {
					std::string word;
					while (fin >> word) {
						this->trieGraph->insertString(word);
					}
					fin.close();
				}
				else std::cout << "Error open input file!";
			}
			if (this->createState == Random) {
				int x = this->InputRandomValue->getInput();
				if (x <= 20 && x > 0) {
					std::vector<std::string> v;
					std::srand(std::time(0));
					generateRandomString(x, v);
					for (auto it : v) this->trieGraph->insertString(it);
				}
			}
			break;
		}
		case Insert:
		{
			if (this->EnterTheValue->getString() != "") {
				this->trieGraph->insertString(this->EnterTheValue->getString());
				this->noti->setString(this->EnterTheValue->getString() + " was inserted");
				this->noti->setPosition({ 1150,490 });
			}
			break;
		}
		case Delete:
		{
			if (this->EnterTheValue->getString() != "") {
				if (this->trieGraph->deleteString(this->EnterTheValue->getString())) {
					this->noti->setString(this->EnterTheValue->getString() + " was deleted");
					this->noti->setPosition({ 1150,490 });
				}
				else {
					this->noti->setString(this->EnterTheValue->getString() + " isn't in Trie");
					this->noti->setPosition({ 1140,490 });
				}
			}
			break;
		}
		case Search:
		{
			if (this->EnterTheValue->getString() != "") {
				this->str = this->EnterTheValue->getString();
			}
			this->searching = true;
			this->index = 0;
			this->id = -1; this->cur = -1;
			break;
		}
		default:
			break;
		}
		this->trieGraph->update();
	}
}

void TrieState::render(sf::RenderTarget* target)
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
	if(this->operationState == Search) this->Speed->render(*target);
	if (this->searching) {
		if (index == 0) {
			this->cur = this->trieGraph->root;
			this->trieGraph->nodes[cur]->setHighlight(sf::Color::Red, this->trieGraph->thickness * 2);
			this->trieGraph->nodes[cur]->render(*target);
			sf::sleep(sf::seconds(0.75f / speed));
			this->trieGraph->nodes[cur]->setHighlight(this->trieGraph->textColor, this->trieGraph->thickness);
		}
		char x = str[index];
		index++;
		if (this->trieGraph->findEdge(cur, charToString(x)) == -1) {
			this->noti->setString(str + " is not found");
			this->noti->setPosition({ 1140,490 });
			this->arrow.setPosition({ 1350,650 });
			this->arrowState = Active;
			this->searching = false;
		}
		else {
			this->id = this->trieGraph->findEdge(cur, charToString(x));
			this->arrow.setPosition({ 1350,675 });
			this->arrowState = Active;
		}
		if (this->searching) {
			this->cur = this->id;
			this->trieGraph->nodes[cur]->setHighlight(sf::Color::Red, this->trieGraph->thickness * 2);
			this->trieGraph->nodes[cur]->render(*target);
			sf::sleep(sf::seconds(0.75f / speed));
			this->trieGraph->nodes[cur]->setHighlight(this->trieGraph->textColor, this->trieGraph->thickness);
			if (index == str.length() && this->trieGraph->nodes[cur]->getIsWord()) {
				this->noti->setString(str + " is found");
				this->noti->setPosition({ 1150,490 });
				this->arrow.setPosition({ 1350,725 });
				this->arrowState = Active;
				this->searching = false;
			}
			else if (index == str.length() && !this->trieGraph->nodes[cur]->getIsWord()) {
				this->noti->setString(str + " is not found");
				this->arrow.setPosition({ 1360,747 });
				this->arrowState = Active;
				this->searching = false;
			}
		}
	}
	this->OperationButton->render(*target);
	this->DoButton->render(*target);
	this->trieGraph->render(*target);
	target->draw(*this->noti); target->draw(*this->code);
	if (this->arrowState != None) target->draw(this->arrow);
}
