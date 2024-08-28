#include "HeapState.h"

HeapState::HeapState(sf::RenderWindow* window, std::stack<State*>* states, bool DarkMode) : State(window, states, DarkMode)
{
	this->initBackground();
	this->initFont();
	this->initGUI();
	this->initText();
	this->initHeapGraph();
}

HeapState::~HeapState()
{
	// Button
	delete this->BackButton;
	delete this->OperationButton;
	delete this->CreateType;
	delete this->DoButton;
	delete this->InputFileButton;
	// Text Box
	delete this->InputRandomValue;
	delete this->EnterTheValue;

	// Text
	delete this->EnterTheVal;
	delete this->NumberOfVal;

	delete this->heapGraph;
	delete this->heap;

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
	if (this->DarkMode) {
		if (!this->BackGroundTexture.loadFromFile("../Resources/Images/Heap Background - DM.png")) std::cerr << "Error loading Heap background!\n";
	}
	else {
		if (!this->BackGroundTexture.loadFromFile("../Resources/Images/Heap Background.png")) std::cerr << "Error loading Heap background!\n";
	}
	this->BackGroundSprite.setTexture(this->BackGroundTexture);
}

void HeapState::initGUI()
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
	list.push_back("Get Top");
	list.push_back("Size");

	this->OperationButton = new gui::DropdownList(1055, 100, 172, 50, &this->fonts["LexendDeca-Bold"], list,
		DarkBlue, 22, LightBlue, DarkBlue, 1, HoverBlue, PressBlue, LightBlue, DarkBlue, LightBlue);

	
	// Init Create Type Button
	std::vector<std::string> typelist;
	typelist.push_back("Random");
	typelist.push_back("File");

	this->CreateType = new gui::DropdownList(1055, 155, 350, 50, &this->fonts["LexendDeca-Bold"], typelist,
		DarkBlue, 22, LightBlue, DarkBlue, 1, HoverBlue, PressBlue, LightBlue, DarkBlue, LightBlue);

	// Init Do Button

	this->DoButton = new gui::Button(1232, 100, 172, 50, "DO", &this->fonts["LexendDeca-Bold"],
		DarkBlue, 22, LightBlue, DarkBlue, 1, HoverBlue, PressBlue, LightBlue, DarkBlue, LightBlue);
	
	// Init Input File Button
	
	this->InputFileButton = new gui::Button(1055, 210, 350, 50, "Input File", &this->fonts["LexendDeca-Bold"],
		DarkBlue, 22, LightBlue, DarkBlue, 1, HoverBlue, PressBlue, LightBlue, DarkBlue, LightBlue);

	// Init Random Number of Val Box

	this->InputRandomValue = new gui::TextBox(1327, 210, 75, 50, &this->fonts["LexendDeca-Regular"],
		3, DarkBlue, sf::Color::White, DarkBlue, DarkBlue);

	// Init Enter The Value Box
	this->EnterTheValue = new gui::TextBox(1322, 155, 75, 50, &this->fonts["LexendDeca-Regular"],
		3, DarkBlue, sf::Color::White, DarkBlue, DarkBlue);
}

void HeapState::initText()
{
	this->NumberOfVal = new sf::Text("Number Of Value (Max 31): ", this->fonts["LexendDeca-Regular"], 20);
	this->NumberOfVal->setPosition(sf::Vector2f(1055, 220));

	this->EnterTheVal = new sf::Text("Enter The Value: ", this->fonts["LexendDeca-Regular"], 30);
	this->EnterTheVal->setPosition(sf::Vector2f(1060, 160));

	this->noti = new sf::Text("", this->fonts["LexendDeca-Regular"], 20);
	this->noti->setPosition(sf::Vector2f(1130, 490));

	this->code = new sf::Text("", this->fonts["LexendDeca-Regular"], 20);
	this->code->setPosition(sf::Vector2f(1070, 565));
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

void HeapState::initHeapGraph()
{
	this->heap = new Heap();
	this->heapGraph = new HeapGraph(sf::Vector2f(600, 200), &this->fonts["LexendDeca-Regular"], this->heap, colorTheme(this->DarkMode), 22.f, 2.f);
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
		this->code->setString("");
		std::string CrState = this->CreateType->getActiveEle();
		if (CrState == "Random") this->createState = Random;
		else if (CrState == "File") this->createState = File;
	}
	else if (OpeState == "Insert") {
		this->operationState = Insert;
		this->code->setString(INSERT_HEAP);
	}
	else if (OpeState == "Delete") {
		this->operationState = Delete;
		this->code->setString(DELETE_HEAP);
	}
	else if (OpeState == "Get Top") {
		this->operationState = GetTop;
		this->code->setString(GETTOP_HEAP);
	}
	else if (OpeState == "Size") {
		this->operationState = Size;
		this->code->setString(SIZE_HEAP);
	}
}

void HeapState::updateNoti()
{
	OperationState x;
	std::string OpeState = this->OperationButton->getActiveEle();
	if (OpeState == "Create") x = Create;
	else if (OpeState == "Insert") x = Insert;
	else if (OpeState == "Delete") x = Delete;
	else if (OpeState == "Get Top") x = GetTop;
	else if (OpeState == "Size") x = Size;

	if (x != this->operationState) this->noti->setString("");
}

void HeapState::update(const float& dt) {
	this->updateMousePos();
	this->updateKeybinds(dt);
	this->BackButton->update({ (float)this->MousePos.x, (float)this->MousePos.y }, dt, this->DarkMode);
	this->OperationButton->update({ (float)this->MousePos.x, (float)this->MousePos.y }, dt, this->DarkMode);
	this->updateNoti();
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
				fileName.setFillColor(DarkBlue);
				this->InputFileButton->setText(fileName);
				setCurrentWorkingDirectory(currentDir);
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
				if (x <= 31)	a = generateRandomArray(x);
			}
			this->heap->arr = a;
			this->heap->n = a.size();
			this->heap->makeHeap();
			break;
		}
		case Insert:
		{
			if (this->EnterTheValue->getString() != "") {
				int x = this->EnterTheValue->getInput();
				this->heap->insert(x);
				this->noti->setString(std::to_string(x) + std::string(" has been inserted"));
				this->noti->setPosition(sf::Vector2f(1130, 490));
			}
			break;
		}
		case Delete:
		{
			if (this->EnterTheValue->getString() != "") {
				int x = this->EnterTheValue->getInput();
				if (this->heap->del(x)) {
					this->noti->setString(std::to_string(x) + std::string(" has been deleted"));
					this->noti->setPosition(sf::Vector2f(1130, 490));
				}
				else {
					this->noti->setString(std::to_string(x) + std::string(" is not in the heap"));
					this->noti->setPosition(sf::Vector2f(1130, 490));
				}
			}
			break;
		}
		case GetTop:
		{
			int x = this->heap->getRoot();
			this->noti->setString(std::string("The top is: ") + std::to_string(x));
			this->noti->setPosition(sf::Vector2f(1160, 490));
			break;
		}
		case Size:
		{
			this->noti->setString(std::string("The size is: " + std::to_string(this->heap->n)));
			this->noti->setPosition(sf::Vector2f(1160, 490));
			break;
		}
		default:
			break;
		}
		this->heapGraph->update();
	}
}

void HeapState::render(sf::RenderTarget* target)
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
	if (this->operationState == Insert || this->operationState == Delete) {
		target->draw(*this->EnterTheVal);
		this->EnterTheValue->render(*target);
	}
	this->OperationButton->render(*target);
	this->DoButton->render(*target);
	if(this->heap->n != 0) 
		this->heapGraph->render(*target);
	target->draw(*this->noti); target->draw(*this->code);
}
