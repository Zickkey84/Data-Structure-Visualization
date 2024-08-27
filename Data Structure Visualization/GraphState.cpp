#include "GraphState.h"

GraphState::GraphState(sf::RenderWindow* window, std::stack<State*>* states, bool DarkMode) : State(window, states, DarkMode)
{
	this->initBackground();
	this->initFont();
	this->initGUI();
	this->initText();
	this->initGraph();
}

GraphState::~GraphState()
{
	// Button
	delete this->BackButton;
	delete this->OperationButton;
	delete this->CreateType;
	delete this->DoButton;

	// Text Box
	delete this->InputRandomValue;
	delete this->EnterTheValue;

	// Text
	delete this->EnterTheVal;
	delete this->NumberOfVal;
	delete this->noti;
	delete this->code;

	//Graph
	delete this->graph;
	for (auto it : edges) delete it;
	delete this->matrixBox;


}

void GraphState::checkForEnd()
{
	if (this->BackButton->isPressed()) this->end = true;
}

void GraphState::initFont()
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

void GraphState::initBackground()
{
	if (DarkMode) {
		if (!this->BackGroundTexture.loadFromFile("../Resources/Images/Graph Background - DM.png")) {
			std::cerr << "Error loading Graph background!\n";
		}
	}
	else {
		if (!this->BackGroundTexture.loadFromFile("../Resources/Images/Graph Background.png")) {
			std::cerr << "Error loading Graph background!\n";
		}
	}
	this->BackGroundSprite.setTexture(this->BackGroundTexture);
}

void GraphState::initGUI()
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
	list.push_back("MST");
	list.push_back("CC");
	this->OperationButton = new gui::DropdownList(1055, 100, 172, 50, &this->fonts["LexendDeca-Bold"], list,
		sf::Color(49, 53, 110), 22, LightBlue, sf::Color(49, 53, 110), 1, HoverBlue, PressBlue,
		LightBlue, sf::Color(49, 53, 110), LightBlue);

	// Init Create Type Button
	std::vector<std::string> typelist;
	typelist.push_back("Random");
	typelist.push_back("File");
	typelist.push_back("Matrix");

	this->CreateType = new gui::DropdownList(1055, 155, 350, 50, &this->fonts["LexendDeca-Bold"], typelist,
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

	// Init matrixBox
	this->matrixBox = new gui::MatrixBox(1085, 475, 26, &this->fonts["LexendDeca-Regular"], (colorTheme) this->DarkMode);
}


void GraphState::initText()
{
	this->NumberOfVal = new sf::Text("Number Of Vertices (Max 10): ", this->fonts["LexendDeca-Regular"], 17);
	this->NumberOfVal->setPosition(sf::Vector2f(1055, 220));

	this->EnterTheVal = new sf::Text("Enter The Value: ", this->fonts["LexendDeca-Regular"], 30);
	this->EnterTheVal->setPosition(sf::Vector2f(1060, 160));

	this->noti = new sf::Text("", this->fonts["LexendDeca-Regular"], 18);
	this->noti->setPosition(sf::Vector2f(1150, 490));

	this->code = new sf::Text("", this->fonts["LexendDeca-Regular"], 18);
	this->code->setPosition(sf::Vector2f(1070, 545));
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

void GraphState::initGraph()
{
	this->graph = new GGraph(this->edges, sf::FloatRect({100,200},{800,550}), colorTheme(this->DarkMode), 22.f, 2, &this->fonts["LexendDeca-Regular"]);
}


void GraphState::updateKeybinds(const float& dt)
{
	this->checkForEnd();

}

void GraphState::updateOperationState()
{
	std::string OpeState = this->OperationButton->getActiveEle();
	if (OpeState == "Create") {
		this->code->setString("");
		this->operationState = Create;
		std::string CrState = this->CreateType->getActiveEle();
		if (CrState == "Random") this->createState = Random;
		else if (CrState == "File") this->createState = File;
		else if (CrState == "Matrix") this->createState = Matrix;
	}
	else if (OpeState == "MST") {
		this->code->setString(MST_GRAPH);
		this->code->setCharacterSize(17);
		this->operationState = MST;
	}
	else if (OpeState == "CC") {
		this->code->setCharacterSize(19);
		this->code->setPosition(1100, 555);
		this->code->setString(CC_GRAPH);
		this->operationState = CC;
	}
}

void GraphState::updateNoti()
{
	OperationState x;
	std::string OpeState = this->OperationButton->getActiveEle();
	if (OpeState == "Create") x = Create;
	else if (OpeState == "MST") x = MST;
	else if (OpeState == "CC") x = CC;

	if (x != this->operationState) {
		this->noti->setString("");
	}
}

void GraphState::update(const float& dt) {
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
				fileName.setFillColor(sf::Color(49, 53, 110));
				this->InputFileButton->setText(fileName);
				setCurrentWorkingDirectory(currentDir);
			}
		}
		if (this->createState == Matrix) {
			sf::Event evnt;
			while (this->window->pollEvent(evnt)) {
				if (evnt.type == sf::Event::TextEntered || evnt.type == sf::Event::MouseButtonPressed)
					this->matrixBox->update({ (float)this->MousePos.x, (float)this->MousePos.y }, evnt);
				if (evnt.type == sf::Event::Closed) this->window->close();
			}
		}
	}
	this->DoButton->update({ (float)this->MousePos.x, (float)this->MousePos.y }, dt, this->DarkMode);
	if (this->DoButton->isPressed()) {
		switch (this->operationState) {
		case Create:
		{
			if (this->createState == File) {
				std::ifstream fin;
				fin.open(this->FileName);
				int x;
				if (fin.is_open()) {
					fin >> x;
					while (x--) {
						int f, t, w;
						fin >> f >> t >> w;
						this->edges.insert(new GEdge(f, t, w));
					}
					this->graph->edges = this->edges;
					fin.close();
				}
				else std::cout << "Error open input file!";
			}
			if (this->createState == Random) {
				int x = this->InputRandomValue->getInput();
				generateRandomMatrix(x, this->edges);
				this->graph->edges = this->edges;
			}
			if (this->createState == Matrix) {
				this->edges.clear();
				this->matrixBox->readInput(edges);
				this->graph->edges = this->edges;
			}
			this->graph->update();
			break;
		}
		case MST:
		{
			this->graph->update();
			int d = 0;
			if (this->graph->MST(d)) {
				this->noti->setPosition(1083, 490);
				this->noti->setString("The minimum spanning tree is " + std::to_string(d));
			}
			else {
				this->noti->setPosition(1090, 490);
				this->noti->setString("Graph doesn't have spanning tree!");
			}
			break;
		}
		case CC:
		{
			this->graph->update();
			int d = this->graph->CC();
			this->noti->setPosition(1065, 490);
			this->noti->setString("Number of connected components is " + std::to_string(d));
			break;
		}
		default:
			break;
		}
	}
}

void GraphState::render(sf::RenderTarget* target)
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
	if (this->operationState == Create && this->createState == Matrix) {
		this->matrixBox->render(*target);
	}
	if (this->operationState == Create) {
		this->CreateType->render(*target);
	}

	this->OperationButton->render(*target);
	this->DoButton->render(*target);
	target->draw(*this->noti); target->draw(*this->code);
	this->graph->render(*target);
}
