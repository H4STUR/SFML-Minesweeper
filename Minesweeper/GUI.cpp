#include "stdafx.h"
#include "GUI.h"

//Base calss
gui::Entity::Entity(sf::Vector2f position, sf::Vector2f size)
	:position(position), size(size) {}

sf::Vector2f gui::Entity::align(sf::FloatRect objectBounds, Align&& state)
{
	return this->align(this->position, this->shape.getGlobalBounds(), std::forward<sf::FloatRect>(objectBounds), std::forward<Align>(state));
}

sf::Vector2f gui::Entity::align(sf::Vector2f& position, sf::FloatRect&& groundBounds, sf::FloatRect&& objectBounds, Align&& state)
{
	switch (state)
	{
		case Align::Center:
		{
			return sf::Vector2f(
				position.x + groundBounds.width - (groundBounds.width / 2.f) - (objectBounds.width / 2),
				position.y + groundBounds.height - (groundBounds.height / 2.f) - (objectBounds.height)
				);
		}break;

		case Align::Right:
		{
			return sf::Vector2f(
				position.x + (groundBounds.width - objectBounds.width),
				position.y + groundBounds.height - (groundBounds.height / 2.f) - (objectBounds.height)
				);
		}break;

		case Align::Left:
		{
			return sf::Vector2f(
				position.x,
				position.y + groundBounds.height - (groundBounds.height / 2.f) - (objectBounds.height)
				);
		}break;

		case Align::Top:
		{
			return sf::Vector2f(
				position.x + groundBounds.width - (groundBounds.width / 2.f) - (objectBounds.width / 2),
				position.y
				);
		}break;

		case Align::Bottom:
		{
			return sf::Vector2f(
				position.x + groundBounds.width - (groundBounds.width / 2.f) - (objectBounds.width / 2),
				position.y + (groundBounds.height - objectBounds.height*2)
				);
		}break;

		default:
		{
			std::cout << "\n gui::Entity::align error\n";
			return sf::Vector2f();
		}break;
	}
}

sf::Text gui::Entity::createText(std::string textString, sf::Font* font, float fontSize, Align&& state)
{
	sf::Text text;
	text.setFont(*font);
	text.setString(textString);
	text.setCharacterSize(static_cast<unsigned int>(fontSize));
	text.setPosition(this->align(text.getGlobalBounds(), std::forward<Align>(state)));

	return text;
}


//Base class for buttons
gui::ButtonBaseClass::ButtonBaseClass(sf::Vector2f position, sf::Vector2f sizePercent, float outlineThickness)
	: Entity(position, sizePercent) 
{ 
	this->buttonState = 0;
	this->outlineThickness = outlineThickness;
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

const sf::Vector2f& gui::ButtonBaseClass::getSize() const
{
	return this->size;
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
	this->shape.setSize(this->size);

	this->shape.setFillColor(this->BTNcolor);

	this->shape.setPosition(this->position);
}

//Constructors && Destructors
gui::Button::Button(std::string BTNText,
	float fontSize, sf::Font* font, sf::Vector2f position, sf::Vector2f size,
	sf::Color BTNcolor, sf::Color BTNHoverColor, sf::Color BTNUsedColor,
	sf::Color BTNTextColor, sf::Color BTNTextHoverColor, sf::Color BTNTextUsedColor,
	sf::Color BTNOutlineColor, sf::Color BTNOutlineHoverColor, sf::Color BTNOutlineUsedColor, float outlineThickness)
	: ButtonBaseClass(position, size, outlineThickness),
	fontSize(fontSize),
	font(font),
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
	this->text = this->createText(BTNText, this->font, this->fontSize, Align::Center);

	this->shape.setOutlineThickness(this->outlineThickness);
	this->shape.setOutlineColor(this->BTNOutlineUsedColor);

}

gui::Button::Button(sf::Texture* texture,
	sf::Vector2f position, sf::Vector2f size, 
	sf::Color BTNcolor, sf::Color BTNHoverColor, sf::Color BTNUsedColor, 
	sf::Color BTNOutlineColor, sf::Color BTNOutlineHoverColor, sf::Color BTNOutlineUsedColor, float outlineThickness)
	: ButtonBaseClass(position, size, outlineThickness),
	texture(texture),
	BTNcolor(BTNcolor),
	BTNHoverColor(BTNHoverColor),
	BTNOutlineColor(BTNOutlineColor),
	BTNOutlineHoverColor(BTNOutlineHoverColor),
	BTNOutlineUsedColor(BTNOutlineUsedColor)


{
	this->init();
	this->shape.setTexture(this->texture);
}


gui::Button::~Button()
{
}

const short unsigned & gui::Button::getID() const
{
	return this->id;
}

void gui::Button::setID(short unsigned id)
{
	this->id = id;
}

const sf::Text & gui::Button::getButtonText() const
{
	return this->text;
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

gui::MultiDimensionalButton::MultiDimensionalButton(Button * baseButton,
	ButtonBaseClass * downButton, 
	ButtonBaseClass * upButton, 
	ButtonBaseClass * rightButton, 
	ButtonBaseClass * leftButton)
	: ButtonBaseClass(baseButton->getPosition(), baseButton->getSize(), 0),
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

inline const bool & gui::MultiDimensionalButton::isActive() const { return this->active; }

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
	//frame && background
	this->shape.setPosition(this->position);

	this->shape.setSize(this->size);

	this->shape.setFillColor(this->backGroundColor);
	this->shape.setOutlineThickness(-1);
	this->shape.setOutlineColor(this->outlineColor);


	//text stuff

	this->text = this->createText(std::to_string(this->value), this->font, this->fontSize, Align::Center);
}


//Constructors && Destructors

gui::Counter::Counter()
	:Entity(sf::Vector2f(0.f, 0.f), sf::Vector2f(10.f, 10.f)),
	fieldWithZeros(true), fontSize(5.f), value(0), font(nullptr)
{

	//Counter Default Contructor
	this->init();
}

gui::Counter::Counter(sf::Vector2f position, sf::Vector2f sizePercent, 
					float fontSize, sf::Font* font, int defaultValue, bool filedWithZeros,
					sf::Color backGroundColor, sf::Color textColor, sf::Color outlineColor)
	:Entity(position, sizePercent)
{
	//init variables
	this->fontSize = fontSize;
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

void gui::Counter::increase(unsigned amout) 
{	
	this->value += amout; 
	this->text.setString(std::to_string(this->value)); 
}

void gui::Counter::decrease(unsigned amout) 
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
	target->draw(this->shape);
	target->draw(this->text);
}



		// TIMER

//Inits
void gui::Timer::init()
{
	this->active = false;
	this->text.setString("0");
	this->clock.restart();
}


//Constructos && Destructors

gui::Timer::Timer(sf::Vector2f position, sf::Vector2f size, float fontSize, sf::Font* font)
	:Counter(position, size, fontSize, font)
{
	this->init();
}

gui::Timer::~Timer()
{
}

const bool& gui::Timer::getActive() const
{
	return this->active;
}

const sf::Time& gui::Timer::getTime() const
{
	return this->time;
}

void gui::Timer::resetTimer()
{
	this->clock.restart();
}

void gui::Timer::switchActive()
{
	this->active = !this->active;
}

//Functions
void gui::Timer::update()
{
	if (this->active)
	{
		this->time = clock.getElapsedTime();
		this->text.setString(std::to_string(this->time.asSeconds()));
	}
}