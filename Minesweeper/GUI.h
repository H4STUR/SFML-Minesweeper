#ifndef _GUI
#define _GUI

#include "stdafx.h"
#include "Settings.h"

//Forward declarations
class Data;

enum ButtonStates
{
	Default = 0,
	Hover,
	Active
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

	//Base class
	class Entity
	{
	public:
		Entity(Data* data,
			   sf::Vector2f position, sf::Vector2f sizePercent);
		virtual ~Entity() {}

		//Functions
		virtual void render(sf::RenderTarget* target) = 0;

	protected:
		//variables
		Data* data;
		sf::RectangleShape shape;
		sf::Vector2f position;
		sf::Vector2f sizePercent;
		sf::FloatRect shapeBounds;
		sf::FloatRect textBounds;
	};

	class ButtonBaseClass : public Entity
	{
	public:
		ButtonBaseClass(Data* data,
			sf::Vector2f position, sf::Vector2f sizePercent, float outlineThickness);
		virtual ~ButtonBaseClass() {}

		//Accessors
		const bool pressed() const;
		const sf::Vector2f & getPosition() const;
		const sf::Vector2f & getSizePercent() const;
		const sf::Vector2f & getSize() const;
		const sf::FloatRect & getShapeBounds() const;
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
		Button(Data* data,
			std::string BTNText = "BUTTON",
			float fontPercentSize = 2.5f,
			sf::Vector2f position = sf::Vector2f(0.f, 0.f),
			sf::Vector2f sizePercent = sf::Vector2f(15.f, 5.f),
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
		//Button(Settings* settings,
		//	std::string imgPath,
		//	sf::Vector2f position = sf::Vector2f(0.f, 0.f),
		//	sf::Vector2f sizePercent = sf::Vector2f(15.f, 5.f),
		//	sf::Color BTNcolor = sf::Color(0, 0, 0, 255),
		//	sf::Color BTNHoverColor = sf::Color(0, 0, 0, 255),
		//	sf::Color BTNUsedColor = sf::Color(0, 0, 0, 255),
		//	sf::Color BTNOutlineColor = sf::Color(0, 0, 0, 255),
		//	sf::Color BTNOutlineHoverColor = sf::Color(0, 0, 0, 255),
		//	sf::Color BTNOutlineUsedColor = sf::Color(0, 0, 0, 255),
		//	float outlineThickness = 0);

		virtual ~Button();

		//Setters
		void setID(short unsigned id);
		const std::string & getButtonText() const;
		void setButtonText(std::string buttonText);
		void setTextPosition(sf::Vector2f position);

		//Accessors
		const sf::FloatRect & getTextBlounds() const;
		const short unsigned & getID() const;

		//Functions
		virtual void update(const sf::Vector2i mousePosWindow);
		virtual void render(sf::RenderTarget* target);

	private:
		//Variables
		sf::Text text;

		sf::Color BTNcolor;
		sf::Color BTNHoverColor;
		sf::Color BTNUsedColor;

		sf::Color BTNTextColor;
		sf::Color BTNTextHoverColor;
		sf::Color BTNTextUsedColor;

		sf::Color BTNOutlineColor;
		sf::Color BTNOutlineHoverColor;
		sf::Color BTNOutlineUsedColor;

		float fontPercentSize;
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
		MultiDimensionalButton(Data* data, Button* baseButton,
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
		Counter(Data* data, sf::Vector2f position, sf::Vector2f sizePercent, float fontPercentSize, int defaultValue = 0, bool filedWithZeros = true,
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

	private:

		//variables
		sf::Text text;

		sf::RectangleShape background;
		sf::Color backGroundColor;
		sf::Color textColor;
		sf::Color outlineColor;

		int value;
		bool fieldWithZeros;
		float fontPercentSize;

		//inits
		void init();
	};

}
#endif //!_GUI