#ifndef _GUI
#define _GUI

#include "stdafx.h"

enum ButtonStates
{
	Default = 0,
	Hover,
	Active
};

enum class Align
{
	Center = 0,
	Right,
	Left,
	Top,
	Bottom
};

namespace gui
{
	//Forward declaration
	class Entity;
	class ButtonBaseClass;
	class Button;
	class MultiDimensionalButton;
	class DropDownList;
	class Counter;
	class Timer;


	//Base class
	class Entity
	{
	public:
		Entity(sf::Vector2f position, sf::Vector2f size);
		virtual ~Entity() {}

	protected:
		//Functions
		sf::Vector2f align(sf::FloatRect objectBounds, Align&& state);
		sf::Vector2f align(sf::Vector2f& position, sf::FloatRect&& bounds, sf::FloatRect&& objectBounds, Align&& state);

		sf::Text createText(std::string textString = "Text", sf::Font* font = nullptr, float fontSize = 5.f, Align&& state = Align::Center);
		virtual void render(sf::RenderTarget* target) = 0;

		//variables
		sf::RectangleShape shape;
		sf::Vector2f position;
		sf::Vector2f size;
	};

	class ButtonBaseClass : public Entity
	{
	public:
		ButtonBaseClass(sf::Vector2f position, sf::Vector2f size, float outlineThickness);
		virtual ~ButtonBaseClass() {}

		//Accessors
		const bool pressed() const;
		const sf::Vector2f & getPosition() const;
		const sf::Vector2f & getSize() const;
		void setPosition(sf::Vector2f position);

		//Functions
		virtual void update(const sf::Vector2i mousePosWindow) = 0;
		virtual void render(sf::RenderTarget* target) = 0;

	protected:
		//Variables
		short unsigned buttonState;
		float outlineThickness;
	};
	//Regular Button
	class Button : public ButtonBaseClass
	{
	public:
		//Button with text
		Button(std::string BTNText = "BUTTON",
			float fontSize = 2.5f,
			sf::Font* font = nullptr,
			sf::Vector2f position = sf::Vector2f(0.f, 0.f),
			sf::Vector2f size = sf::Vector2f(15.f, 5.f),
			sf::Color BTNcolor = sf::Color(0, 0, 0, 255), 
			sf::Color BTNHoverColor = sf::Color(0, 0, 0, 255), 
			sf::Color BTNUsedColor = sf::Color(0, 0, 0, 255), 
			sf::Color BTNTextColor = sf::Color(0,0,0,255), 
			sf::Color BTNTextHoverColor = sf::Color(0, 0, 0, 255), 
			sf::Color BTNTextUsedColor = sf::Color(0, 0, 0, 255),
			sf::Color BTNOutlineColor = sf::Color(0, 0, 0, 255),
			sf::Color BTNOutlineHoverColor = sf::Color(0, 0, 0, 255),
			sf::Color BTNOutlineUsedColor = sf::Color(0, 0, 0, 255),
			float outlineThickness = 0);

		//Button with img
		Button(sf::Texture* texture,
			sf::Vector2f position = sf::Vector2f(0.f, 0.f),
			sf::Vector2f size = sf::Vector2f(15.f, 5.f),
			sf::Color BTNcolor = sf::Color(0, 0, 0, 255),
			sf::Color BTNHoverColor = sf::Color(0, 0, 0, 200),
			sf::Color BTNUsedColor = sf::Color(0, 0, 0, 255),
			sf::Color BTNOutlineColor = sf::Color(0, 0, 0, 255),
			sf::Color BTNOutlineHoverColor = sf::Color(0, 0, 0, 255),
			sf::Color BTNOutlineUsedColor = sf::Color(0, 0, 0, 255),
			float outlineThickness = 0);

		virtual ~Button();

		//Setters
		void setID(short unsigned id);
		void setButtonText(std::string buttonText);
		void setTextPosition(sf::Vector2f position);

		//Accessors
		const short unsigned & getID() const;
		const sf::Text& getButtonText() const;

		//Functions
		virtual void update(const sf::Vector2i mousePosWindow);
		virtual void render(sf::RenderTarget* target);

	private:
		//Variables
		sf::Text text;
		sf::Texture* texture;
		sf::Font* font;
		sf::Color BTNcolor;
		sf::Color BTNHoverColor;
		sf::Color BTNUsedColor;

		sf::Color BTNTextColor;
		sf::Color BTNTextHoverColor;
		sf::Color BTNTextUsedColor;

		sf::Color BTNOutlineColor;
		sf::Color BTNOutlineHoverColor;
		sf::Color BTNOutlineUsedColor;

		float fontSize;
		short unsigned id;
		short numChars;

		//Init
		void init();
	};

	//Multidimensional Button
	class MultiDimensionalButton : public ButtonBaseClass
	{
	public:
		//Constructors
		MultiDimensionalButton(Button* baseButton,
			ButtonBaseClass* downButton = nullptr,
			ButtonBaseClass* upButton = nullptr,
			ButtonBaseClass* rightButton = nullptr,
			ButtonBaseClass* leftButton = nullptr);

		~MultiDimensionalButton();

		//Accessors
		void switchButtons(const float & deltatime);

		const bool & isActive() const;
		virtual inline const bool pressed() const;
		virtual inline const bool isDownButtonPressed() const;
		virtual inline const bool isUpButtonPressed() const;
		virtual inline const bool isRightButtonPressed() const;
		virtual inline const bool isLeftButtonPressed() const;

		//Functions
		virtual void update(const sf::Vector2i mousePosWindow);
		virtual void render(sf::RenderTarget* target);

	private:
		//Variables
		std::vector<ButtonBaseClass*> buttons;
		Button* baseButton;
		ButtonBaseClass* downButton;
		ButtonBaseClass* upButton;
		ButtonBaseClass* rightButton;
		ButtonBaseClass* leftButton;

		bool active;

		//Functions
		void init();
	};


	//COUNTER CLASS

	class Counter	:public Entity
	{
	public:
		Counter();
		Counter(sf::Vector2f position, sf::Vector2f size, float fontSize, sf::Font* font, int defaultValue = 0, bool filedWithZeros = true,
			sf::Color backGroundColor = sf::Color(60, 60, 60, 255),
			sf::Color textColor = sf::Color(0, 0, 0, 255),
			sf::Color outlineColor = sf::Color(0, 0, 0, 255));
		~Counter();

		//Accessors && Modifiers
		void increase(unsigned amout = 1);
		void decrease(unsigned amout = 1);

		const int& getValue() const;

		//functions

		virtual void render(sf::RenderTarget* target);

	protected:

		//variables
		sf::Text text;

		sf::Color backGroundColor;
		sf::Color textColor;
		sf::Color outlineColor;
		sf::Font* font;

		int value;
		bool fieldWithZeros;
		float fontSize;

	private:

		//inits
		void init();
	};

	class Timer : public Counter
	{
	public:
		Timer(sf::Vector2f position, sf::Vector2f size, float fontSize, sf::Font* font = nullptr);
		~Timer();

		//Accessors
		const bool& getActive() const;
		const sf::Time& getTime() const;

		//Modifiers
		void resetTimer();
		void switchActive();

		//functions
		void update();

	private:
		//variables
		sf::Clock clock;
		sf::Time time;
		sf::Time lastTime;

		bool active;

		//Inits
		void init();
	};
}
#endif //!_GUI