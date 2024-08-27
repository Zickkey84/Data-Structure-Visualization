#include "GUI.h"


// BUTTON ------------------------------

// Constructor 
gui::Button::Button(float x, float y, float width, float height,
	std::string t, sf::Font* font, sf::Color textColor, int textsize,
	sf::Color idleColor, sf::Color borderColor, int borderThickness, sf::Color hoverColor, sf::Color pressedColor,
	sf::Color DM_textColor, sf::Color DM_idleColor, sf::Color DM_borderColor)
{
	this->button.setPosition(sf::Vector2f(x, y));
	this->button.setSize(sf::Vector2f(width, height));
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(t);
	this->text.setFillColor(textColor);
	this->text.setCharacterSize(textsize);
	
	// Set position for text
	this->text.setOrigin({ round(this->text.getLocalBounds().width / 2.0f), round(this->text.getLocalBounds().height / 2.0f) });
	float xPos = (x + width / 2.0f);
	float yPos = (y + height / 2.0f);
	this->text.setPosition({ round(xPos), round(yPos) - 5.f});

	this->textColor = textColor;
	this->borderThickness = borderThickness;
	this->borderColor = borderColor;
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->pressedColor = pressedColor;

	this->DM_textColor = DM_textColor;
	this->DM_idleColor = DM_idleColor;
	this->DM_borderColor = DM_borderColor;
}

gui::Button::~Button()
{
}

const sf::Text gui::Button::getText() const
{
	return this->text;
}

const sf::Vector2f gui::Button::getPosition() const
{
	return this->button.getPosition();
}

const sf::FloatRect gui::Button::getBounds() const
{
	sf::FloatRect bound = this->button.getLocalBounds();
	bound.width -= 2.f * this->button.getOutlineThickness();
	bound.height -= 2.f * this->button.getOutlineThickness();

	return bound;
}


void gui::Button::setText(const sf::Text text)
{
	this->text = text;
	this->text.setOrigin({ round(this->text.getLocalBounds().width / 2.0f), round(this->text.getLocalBounds().height / 2.0f) });
	float xPos = (this->button.getPosition().x + this->button.getGlobalBounds().width / 2.0f);
	float yPos = (this->button.getPosition().y + this->button.getGlobalBounds().height / 2.0f);
	this->text.setPosition({ round(xPos), round(yPos) - 5.f });
}

void gui::Button::setTextColor(sf::Color textColor)
{
	this->text.setFillColor(textColor);
}

void gui::Button::setIdleColor(sf::Color idleColor)
{
	this->idleColor = idleColor;
}

void gui::Button::setborderColor(sf::Color borderColor)
{
	this->borderColor = borderColor;
}

const bool gui::Button::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax) {
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

void gui::Button::updateKeyTime(const float dt)
{
	if (this->keyTime < this->keyTimeMax) this->keyTime += 10.f * dt;

}

void gui::Button::update(const sf::Vector2f mousePos, const float dt, bool DarkMode)
{
	this->updateKeyTime(dt);
	this->buttonState = BTN_IDLE;
	if (this->button.getGlobalBounds().contains(mousePos)) 
	{
		this->buttonState = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime())
		{
			this->buttonState = BTN_PRESSED;
		}
	}

	switch (buttonState)
	{
	case BTN_IDLE:
		if (DarkMode) {
			this->text.setFillColor(this->DM_textColor);
			this->button.setFillColor(this->DM_idleColor);
			this->button.setOutlineColor(this->DM_borderColor);
		}
		else {
			this->text.setFillColor(this->textColor);
			this->button.setFillColor(this->idleColor);
			this->button.setOutlineColor(this->borderColor);
		}
		this->button.setOutlineThickness(this->borderThickness);
		break;
	case BTN_HOVER:
		this->button.setOutlineColor(this->hoverColor);
		this->button.setOutlineThickness(this->borderThickness + 2);
		break;
	case BTN_PRESSED:
		this->button.setOutlineColor(this->pressedColor);
		break;
	default:
		break;
	}
}

void gui::Button::render(sf::RenderTarget& target)

{
	target.draw(this->button);
	target.draw(this->text);
}

bool gui::Button::isMouseOver(sf::RenderWindow& window)
{
	float mouseX = sf::Mouse::getPosition().x;
	float mouseY = sf::Mouse::getPosition().y;

	float buttonX = this->button.getPosition().x;
	float buttonY = this->button.getPosition().y;

	float buttonWidth = this->button.getGlobalBounds().width;
	float buttonHeigh = this->button.getGlobalBounds().height;

	if (mouseX >= buttonX && mouseX <= buttonX + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeigh) {
		return true;
	}
	return false;
}

const bool gui::Button::isPressed() const
{
	if (this->buttonState == BTN_PRESSED) return true;
	return false;
}

// IMAGEBUTTON FUNCTION ----------------------

gui::ImageButton::ImageButton(float x, float y, std::string idelTextureFile, std::string hoverTextureFile, std::string DM_idelTextureFile, std::string DM_hoverTextureFile)
{
	if (!this->idelTexture.loadFromFile(idelTextureFile)) {
		std::cerr << "Error loading Button Texture!\n";
	}
	if (!this->hoverTexture.loadFromFile(hoverTextureFile)) {
		std::cerr << "Error loading hoverButton Texture!\n";
	}
	if (!this->DM_idelTexture.loadFromFile(DM_idelTextureFile)) {
		std::cerr << "Error loading Button Texture!\n";
	}
	if (!this->DM_hoverTexture.loadFromFile(DM_hoverTextureFile)) {
		std::cerr << "Error loading hoverButton Texture!\n";
	}
	this->IMG_Button.setPosition(sf::Vector2f(x, y));
}

const bool gui::ImageButton::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax) {
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

void gui::ImageButton::updateKeyTime(const float dt)
{
	if (this->keyTime < this->keyTimeMax) this->keyTime += 10.f * dt;
}

void gui::ImageButton::update(const sf::Vector2f mousePos, const float dt, bool DarkMode)
{
	this->updateKeyTime(dt);
	this->buttonState = BTN_IDLE;
	if (this->IMG_Button.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime())
		{
			this->buttonState = BTN_PRESSED;
		}
	}

	switch (buttonState)
	{
	case BTN_IDLE:
		if (DarkMode) this->IMG_Button.setTexture(this->DM_idelTexture);
		else this->IMG_Button.setTexture(this->idelTexture);
		break;
	case BTN_HOVER:
		if (DarkMode) this->IMG_Button.setTexture(this->DM_hoverTexture);
		else this->IMG_Button.setTexture(this->hoverTexture);		
		break;
	default:
		break;
	}
}

void gui::ImageButton::render(sf::RenderTarget& target)
{
	target.draw(this->IMG_Button);
}

bool gui::ImageButton::isPressed()
{
	if (this->buttonState == BTN_PRESSED) return true;
	return false;
}

// DROPDOWNLIST ----------------------------------- 
gui::DropdownList::DropdownList(float x, float y, float width, float height,
	sf::Font* font, std::vector<std::string> list, sf::Color textColor, 
	int textsize, sf::Color idleColor, sf::Color borderColor, 
	int borderThickness, sf::Color hoverColor, sf::Color pressedColor,
	sf::Color DM_textColor, sf::Color DM_idleColor, sf::Color DM_borderColor)
	: font(font), isShowed(false)
{
	this->activeEle = new gui::Button(x, y, width, height, list[0], this->font, textColor, 
		textsize, idleColor, borderColor, borderThickness, hoverColor, pressedColor, 
		DM_textColor, DM_idleColor, DM_borderColor);

	for (size_t i = 1; i < list.size(); i++) {
		this->list.push_back(
			new gui::Button(x, y + (i * (height + 5)), width, height, list[i], this->font,
				textColor, textsize, idleColor, borderColor, borderThickness, hoverColor, pressedColor,
				DM_textColor, DM_idleColor, DM_borderColor)
		);
	}

	this->OC_Arrow.setPointCount(3);
	this->OC_Arrow.setFillColor(textColor);
}

gui::DropdownList::~DropdownList()
{
	delete this->activeEle;
	auto it = this->list.begin();
	for (it; it != list.end();it++) delete *it;
}

const bool gui::DropdownList::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax) {
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

void gui::DropdownList::updateKeyTime(const float dt)
{
	if (this->keyTime < this->keyTimeMax) this->keyTime += 10.f * dt;
}

const std::string gui::DropdownList::getActiveEle()
{
	return this->activeEle->getText().getString();
}

void gui::DropdownList::update(const sf::Vector2f& mousePos, const float dt, bool DarkMode)
{
	this->updateKeyTime(dt);
	this->activeEle->update(mousePos, dt, DarkMode);
	if (DarkMode) this->OC_Arrow.setFillColor(sf::Color(205, 214, 255));
	else this->OC_Arrow.setFillColor(sf::Color(49, 53, 110));

	if (activeEle->isPressed() && this->getKeyTime()) {
		this->isShowed = !this->isShowed;
	}
	if (this->isShowed) {
		this->OC_Arrow.setPoint(0, sf::Vector2f(this->activeEle->getPosition().x + round(this->activeEle->getBounds().width * 0.9f),
			this->activeEle->getPosition().y + round(this->activeEle->getBounds().height * 0.6f)));
		this->OC_Arrow.setPoint(1, sf::Vector2f(this->activeEle->getPosition().x + round(this->activeEle->getBounds().width * 0.93333f),
			this->activeEle->getPosition().y + round(this->activeEle->getBounds().height * 0.4f)));
		this->OC_Arrow.setPoint(2, sf::Vector2f(this->activeEle->getPosition().x + round(this->activeEle->getBounds().width * 0.96666f),
			this->activeEle->getPosition().y + round(this->activeEle->getBounds().height * 0.6f)));
		for (auto& it : this->list) {
			it->update(mousePos, dt, DarkMode);
			if (it->isPressed() && this->getKeyTime()) {
				sf::Text temp = it->getText();
				it->setText(this->activeEle->getText());
				this->activeEle->setText(temp);
				this->isShowed = false;
			}
			if (it == *(this->list.end() - 1) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime()) this->isShowed = false;

		}
	}
	else {
		this->OC_Arrow.setPoint(0, sf::Vector2f(this->activeEle->getPosition().x + round(this->activeEle->getBounds().width * 0.9f),
			this->activeEle->getPosition().y + round(this->activeEle->getBounds().height * 0.45f)));
		this->OC_Arrow.setPoint(1, sf::Vector2f(this->activeEle->getPosition().x + round(this->activeEle->getBounds().width * 0.93333f),
			this->activeEle->getPosition().y + round(this->activeEle->getBounds().height * 0.65f)));
		this->OC_Arrow.setPoint(2, sf::Vector2f(this->activeEle->getPosition().x + round(this->activeEle->getBounds().width * 0.96666f),
			this->activeEle->getPosition().y + round(this->activeEle->getBounds().height * 0.45f)));
	}
}

void gui::DropdownList::render(sf::RenderTarget& target)
{
	this->activeEle->render(target);
	if (this->isShowed) {
		for (auto& it : this->list) {
			it->render(target);
		}
	}
	target.draw(this->OC_Arrow);
}

// TEXT BOX ------------------------------------

gui::TextBox::TextBox(float x, float y, float width, float height, sf::Font* font, int outlineThickness,
	sf::Color outlineColor, sf::Color boxColor, sf::Color textColor, sf::Color cursorColor)
{
	this->Textbox.setString("");
	this->Textbox.setFont(*font);
	this->Textbox.setCharacterSize(round(height * 0.6));
	this->Textbox.setPosition({ round(x + width * 0.05f),round(y + height * 0.055f)});
	this->Textbox.setFillColor(textColor);

	this->Box.setPosition(sf::Vector2f(x, y));
	this->Box.setSize(sf::Vector2f(width, height));
	this->Box.setOutlineThickness(outlineThickness);
	this->Box.setFillColor(boxColor);
	this->Box.setOutlineColor(outlineColor);

	this->Cursor.setSize(sf::Vector2f(width * 0.015, height * 0.8));
	this->Cursor.setPosition(sf::Vector2f(x + round(width * 0.07), y + round(height * 0.055)));
	this->Cursor.setFillColor(cursorColor);

}

void gui::TextBox::deleteLastchar() {
	std::string t = this->text.str();
	std::string newT = "";
	for (int i = 0; i < t.length() - 1; i++) newT += t[i];
	this->text.str("");
	this->text << newT;
	this->Textbox.setString(this->text.str());
}

void gui::TextBox::input(int charTyped) {
	if (charTyped != 8) {
		this->text << static_cast<char>(charTyped);
	}
	else {
		if (text.str().length() > 0) deleteLastchar();
	}
	this->Textbox.setString(this->text.str());
}

void gui::TextBox::update(const sf::Vector2f& mousePos, sf::Event& evnt) {

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (this->Box.getGlobalBounds().contains(mousePos)) {
			this->isSelected = true;
		}
		else this->isSelected = false;
	}

	if (isSelected) {
		int charTyped = evnt.text.unicode;
		if (charTyped == 8 || charTyped == 32 || charTyped > 47 && charTyped < 58) {
			input(charTyped);
			this->Cursor.setPosition(sf::Vector2f(this->Box.getPosition().x + round(this->Box.getSize().x * 0.07) + this->Textbox.getLocalBounds().width,
				this->Box.getPosition().y + round(this->Box.getSize().y * 0.055)));
		}
	}
}

void gui::TextBox::render(sf::RenderTarget& target) {
	target.draw(this->Box);
	if(this->isSelected) target.draw(this->Cursor);
	target.draw(this->Textbox);
}

int gui::TextBox::getInput()
{
	std::string str = this->text.str(); 
	if (str.length() > 0) {
		int inputNum = std::stoi(str);
		return inputNum;
	}
	else return 0;
}

std::string gui::TextBox::getString()
{
	return this->Textbox.getString();
}

gui::MatrixBox::MatrixBox(float x, float y, float size, sf::Font* font, colorTheme theme)
{
	for (int i = 0; i <= 10; i++) {
		sf::RectangleShape* temp = new sf::RectangleShape();
		temp->setSize({ size,size });
		temp->setFillColor(HASH::color[theme][HASH::Normal].fillColor);
		temp->setOutlineThickness(1);
		temp->setOutlineColor(HASH::color[theme][HASH::Normal].outlineColor);
		temp->setPosition({ x + size * (float)i + (float)i, y });
		firstRow.push_back(temp);
		if (i != 0) {
			sf::Text* text1 = new sf::Text();
			text1->setFont(*font);
			text1->setCharacterSize(round(size / 2));
			text1->setString(std::to_string(i));
			text1->setFillColor(HASH::color[theme][HASH::Normal].outlineColor);
			text1->setOrigin({ round(text1->getGlobalBounds().width / 2), round(text1->getGlobalBounds().height / 2) });
			text1->setPosition({ temp->getPosition().x + size / 2.f, temp->getPosition().y + size / 2.f });
			firstRowText.push_back(text1);
		}
		sf::RectangleShape* temp2 = new sf::RectangleShape();
		temp2->setSize({ size,size });
		temp2->setFillColor(HASH::color[theme][HASH::Normal].fillColor);
		temp2->setOutlineThickness(1);
		temp2->setOutlineColor(HASH::color[theme][HASH::Normal].outlineColor);
		temp2->setPosition({ x , y + size * (float)i + (float)i });
		firstColumn.push_back(temp2);
		if (i != 0) {
			sf::Text* text2 = new sf::Text();
			text2->setFont(*font);
			text2->setCharacterSize(round(size / 2));
			text2->setString(std::to_string(i));
			text2->setFillColor(HASH::color[theme][HASH::Normal].outlineColor);
			text2->setOrigin({ round(text2->getGlobalBounds().width / 2), round(text2->getGlobalBounds().height / 2) });
			text2->setPosition({ temp2->getPosition().x + size / 2.f, temp2->getPosition().y + size / 2.f });
			firstColumnText.push_back(text2);
		}
	}
	for (int i = 1; i <= 9; i++) {
		for (int j = i + 1; j <= 10; j++) {
			ListBox.push_back(new TextBox(x + size * (float)j + (float)j, y + size * (float)i + (float)i, size, size, font, 1,
				HASH::color[theme][HASH::Normal].outlineColor, HASH::color[theme][HASH::Normal].fillColor,
				HASH::color[theme][HASH::Normal].outlineColor, HASH::color[theme][HASH::Normal].outlineColor));
		}
	}
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= i; j++) {
			sf::RectangleShape* temp = new sf::RectangleShape();
			temp->setSize({ size,size });
			temp->setFillColor(HASH::color[theme][HASH::Normal].fillColor);
			temp->setOutlineThickness(1);
			temp->setOutlineColor(HASH::color[theme][HASH::Normal].outlineColor);
			temp->setPosition({ x + size * j + j, y + size * i + i});
			XBox.push_back(temp);

			sf::Text* text = new sf::Text();
			text->setFont(*font);
			text->setCharacterSize(round(size / 2));
			text->setString("X");
			text->setFillColor(HASH::color[theme][HASH::Normal].outlineColor);
			text->setOrigin({ round(text->getGlobalBounds().width / 2), round(text->getGlobalBounds().height / 2) });
			text->setPosition({ temp->getPosition().x + size / 2.f, temp->getPosition().y + size / 2.f });
			XText.push_back(text);
		}
	}
}

gui::MatrixBox::~MatrixBox() {
	for (auto it : ListBox) delete it;
	for (auto it : XBox) delete it;
	for (auto it : firstColumn) delete it;
	for (auto it : firstRow) delete it;
	for (auto it : firstRowText) delete it;
	for (auto it : firstColumnText) delete it;
	for (auto it : XText) delete it;
}

void gui::MatrixBox::readInput(std::set<GEdge*>& edges) {
	int index = 0;
	for (int i = 1; i <= 9; i++) {
		for (int j = i + 1; j <= 10; j++) {
			edges.insert(new GEdge(i, j, ListBox[index]->getInput()));
			index++;
		}
	}
}
void gui::MatrixBox::update(const sf::Vector2f& mousePos, sf::Event& evnt)
{
	for (auto it : ListBox) it->update(mousePos, evnt);
}


void gui::MatrixBox::render(sf::RenderTarget& target)
{
	for (auto it : ListBox) it->render(target);
	for (auto it : XBox) target.draw(*it);
	for (auto it : firstColumn) target.draw(*it);
	for (auto it : firstRow) target.draw(*it);
	for (auto it : firstRowText) target.draw(*it);
	for (auto it : firstColumnText) target.draw(*it);
	for (auto it : XText) target.draw(*it);
}



