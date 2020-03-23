#include "stdafx.h"
#include "GUI.h"

//Base calss
gui::Entity::Entity(Data * data, sf::Vector2f position, sf::Vector2f sizePercent)
	: data(data),  position(position), sizePercent(sizePercent) {}


//Base class for buttons
gui::ButtonBaseClass::ButtonBaseClass(Data* data, sf::Vector2f position, sf::Vector2f sizePercent, float outlineThickness)
	: Entity(data, position, sizePercent) 
{ 
	this->buttonState = 0;
	this->outlineThickness = outlineThickness;
	this->shapeBounds = this->shape.getGlobalBounds();
}

const bool gui::ButtonBaseClass::pressed() const
{
	if (this->buttonState == ButtonStates::Active) return true;
	else return false;
}

const sf::Vector2f & gui::ButtonBaseClass::getPosition() const
{
	return this->position;
}

const sf::Vector2f & gui::ButtonBaseClass::getSizePercent() const
{
	return this->sizePercent;
}

const sf::Vector2f& gui::ButtonBaseClass::getSize() const
{
	return this->sizePercent;
}

const sf::FloatRect& gui::ButtonBaseClass::getShapeBounds() const
{
	return this->shapeBounds;
}

void gui::ButtonBaseClass::setPosition(sf::Vector2f position)
{
	this->position = position;
	this->shape.setPosition(position);
}


	//Regular Button

//Inits 
void gui::Button::init()
{
	//Variables
	this->buttonState = ButtonStates::Default;

	//Shape stuff
	this->shape.setSize(
		sf::Vector2f(this->data->PercentSizeX(this->sizePercent.x),
			this->data->PercentSizeY(this->sizePercent.y)));

	this->shape.setFillColor(this->BTNcolor);

	this->shape.setPosition(
		sf::Vector2f(this->data->PercentSizeX(this->position.x),
			this->data->PercentSizeY(this->position.y)));
}

//Constructors && Destructors
gui::Button::Button(Data* data, sf::Font* font, std::string BTNText,
	float fontPercentSize, sf::Vector2f position, sf::Vector2f sizePercent,
	sf::Color BTNcolor, sf::Color BTNHoverColor, sf::Color BTNUsedColor,
	sf::Color BTNTextColor, sf::Color BTNTextHoverColor, sf::Color BTNTextUsedColor,
	sf::Color BTNOutlineColor, sf::Color BTNOutlineHoverColor, sf::Color BTNOutlineUsedColor, float outlineThickness)
	: ButtonBaseClass(data, position, sizePercent, outlineThickness),
	font(font),
	fontPercentSize(fontPercentSize),
	BTNcolor(BTNcolor),
	BTNHoverColor(BTNHoverColor),
	BTNUsedColor(BTNUsedColor),
	BTNTextColor(BTNTextColor),
	BTNTextHoverColor(BTNTextHoverColor),
	BTNTextUsedColor(BTNTextUsedColor),
	BTNOutlineColor(BTNOutlineColor),
	BTNOutlineHoverColor(BTNOutlineHoverColor),
	BTNOutlineUsedColor(BTNOutlineUsedColor)

{

	this->init();

	//Text stuff
	this->numChars = static_cast<short>(BTNText.length());
	this->text.setString(BTNText);
	this->text.setFont(*this->font);
	this->text.setCharacterSize(static_cast<unsigned>(this->data->PercentSizeX(this->fontPercentSize)));

	//default possition
	this->text.setPosition(
		sf::Vector2f(
			this->shape.getPosition().x + (this->shape.getGlobalBounds().width - this->text.getGlobalBounds().width) / 2.f,
			this->shape.getPosition().y + (this->shape.getGlobalBounds().height - this->text.getGlobalBounds().height) / 2.f
		));	

	this->shape.setOutlineThickness(this->outlineThickness);

}

//gui::Button::Button(Settings * settings, std::string imgPath, 
//	sf::Vector2f position, sf::Vector2f sizePercent, 
//	sf::Color BTNcolor, sf::Color BTNHoverColor, sf::Color BTNUsedColor, 
//	sf::Color BTNOutlineColor, sf::Color BTNOutlineHoverColor, sf::Color BTNOutlineUsedColor, float outlineThickness)
//	: ButtonBaseClass(settings, position, sizePercent, outlineThickness),
//	BTNcolor(BTNcolor),
//	BTNHoverColor(BTNHoverColor),
//	BTNOutlineColor(BTNOutlineColor),
//	BTNOutlineHoverColor(BTNOutlineHoverColor),
//	BTNOutlineUsedColor(BTNOutlineUsedColor)
//
//
//{
//	this->init();
//}


gui::Button::~Button()
{
}

const sf::FloatRect& gui::Button::getTextBlounds() const
{
	return this->textBounds;
}

const short unsigned & gui::Button::getID() const
{
	return this->id;
}

void gui::Button::setID(short unsigned id)
{
	this->id = id;
}

const std::string & gui::Button::getButtonText() const
{
	return this->text.getString();
}

void gui::Button::setButtonText(std::string buttonText)
{
	this->text.setString(buttonText);
}

void gui::Button::setTextPosition(sf::Vector2f position)
{
	this->text.setPosition(position);
}

//Functions
void gui::Button::update(const sf::Vector2i mousePosWindow)
{
	this->buttonState = ButtonStates::Default;

	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->buttonState = ButtonStates::Hover; //Mouse is above button

		//Mouse is pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->buttonState = ButtonStates::Active;
	}

	switch (this->buttonState)
	{
		case ButtonStates::Default:
		{
			this->shape.setFillColor(this->BTNcolor);
			this->text.setFillColor(this->BTNTextColor);
		}break;

		case ButtonStates::Hover:
		{
			this->shape.setFillColor(this->BTNHoverColor);
			this->text.setFillColor(this->BTNTextHoverColor);
		}break;

		case ButtonStates::Active:
		{
			this->shape.setFillColor(this->BTNUsedColor);
			this->text.setFillColor(this->BTNTextUsedColor);
		}break;
	}
}

void gui::Button::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
	target->draw(this->text);
}

	
	//Multidimensional Button

//Inits
void gui::MultiDimensionalButton::init()
{
	this->active = false;
	if (this->downButton)
		this->buttons.push_back(this->downButton);	
	if (this->upButton)
		this->buttons.push_back(this->upButton);	
	if (this->rightButton)
		this->buttons.push_back(this->rightButton);	
	if (this->leftButton)
		this->buttons.push_back(this->leftButton);
}

//Constructors && Destructors

gui::MultiDimensionalButton::MultiDimensionalButton(Data * data, Button * baseButton,
	ButtonBaseClass * downButton, 
	ButtonBaseClass * upButton, 
	ButtonBaseClass * rightButton, 
	ButtonBaseClass * leftButton)
	: ButtonBaseClass(data, baseButton->getPosition(), baseButton->getSizePercent(), 0),
	baseButton(baseButton), downButton(downButton), rightButton(rightButton), leftButton(leftButton)
{
	this->init();
}

gui::MultiDimensionalButton::~MultiDimensionalButton()
{
}

//Accessors
void gui::MultiDimensionalButton::switchButtons(const float & deltatime)
{
	if(!this->active) this->active = true;
	else this->active = false;

}

const bool & gui::MultiDimensionalButton::isActive() const { return this->active; }

inline const bool gui::MultiDimensionalButton::pressed() const { return this->baseButton->pressed(); }

inline const bool gui::MultiDimensionalButton::isDownButtonPressed() const { if(this->active) return this->downButton->pressed(); else return false; }

inline const bool gui::MultiDimensionalButton::isUpButtonPressed() const { if(this->active) return this->upButton->pressed(); else return false; }

inline const bool gui::MultiDimensionalButton::isRightButtonPressed() const { if(this->active) return this->rightButton->pressed(); else return false;}

inline const bool gui::MultiDimensionalButton::isLeftButtonPressed() const { if(this->active) return this->leftButton->pressed(); else return false; }


//Functions
void gui::MultiDimensionalButton::update(const sf::Vector2i mousePosWindow)
{
	this->baseButton->update(mousePosWindow);

		for (auto &i : buttons)
			i->update(mousePosWindow);
}

void gui::MultiDimensionalButton::render(sf::RenderTarget * target)
{
	this->baseButton->render(target);

	if (active)
	{
		for (auto &i : buttons)
			i->render(target);
	}
}


		// COUNTER

void gui::Counter::init()
{
	//text stuff
	this->text.setFont(*this->font);
	this->text.setString(std::to_string(this->value));

	this->text.setCharacterSize(static_cast<unsigned>(this->data->PercentSizeX(this->fontPercentSize)));

	//default possition
	this->text.setPosition(
		sf::Vector2f(
			this->shape.getPosition().x + (this->shape.getGlobalBounds().width - this->text.getGlobalBounds().width),
			this->shape.getPosition().y + (this->shape.getGlobalBounds().height - this->text.getGlobalBounds().height) / 2.f
		));

	//frame && background
	this->background.setPosition(this->position);
	this->background.setSize(this->sizePercent);
	this->background.setFillColor(this->backGroundColor);
	this->background.setOutlineThickness(-1);
	this->background.setOutlineColor(this->outlineColor);
}


//Constructors && Destructors

gui::Counter::Counter()
	:Entity(nullptr, sf::Vector2f(0.f, 0.f), sf::Vector2f(10.f, 10.f))
{
	//Counter Default Contructor
}

gui::Counter::Counter(Data* data, sf::Vector2f position, sf::Vector2f sizePercent, sf::Font* font, float fontPercentSize, int defaultValue, bool filedWithZeros,
						sf::Color backGroundColor, sf::Color textColor, sf::Color outlineColor)
	:Entity(data, position, sizePercent)
{
	//init variables
	this->font = font;
	this->value = defaultValue;
	this->backGroundColor = backGroundColor;
	this->textColor = textColor;
	this->outlineColor = outlineColor;


	this->init();
}

gui::Counter::~Counter()
{
}

inline void gui::Counter::increase(unsigned amout) 
{	
	this->value += amout; 
	this->text.setString(std::to_string(this->value)); 
}

inline void gui::Counter::decrease(unsigned amout) 
{	
	this->value -= amout; 
	this->text.setString(std::to_string(this->value)); 
}

const int& gui::Counter::getValue() const
{
	return this->value;
}

void gui::Counter::render(sf::RenderTarget* target)
{
	target->draw(this->background);
	target->draw(this->text);
}

