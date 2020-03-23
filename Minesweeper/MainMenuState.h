#ifndef _MAINMENUSTATE
#define _MAINMENUSTATE

#include "State.h"
#include "GameState.h"

class MainMenuState : public State
{
public:
	MainMenuState(Data* data);
	virtual ~MainMenuState();
	
	//Functions

		//Update
		virtual void update(const float& deltatime);
		virtual void updateInput(const float& deltaTime);
		void updateButtons(const float& deltaTime);

		//Render
		void renderButtons(sf::RenderTarget* target = nullptr);
		void renderGui(sf::RenderTarget* target = nullptr);
		virtual void render(sf::RenderTarget* target = nullptr);

private:
	//variables
	sf::RectangleShape backGround;

	sf::Texture symbolTex;
	sf::RectangleShape symbol;

	std::map<std::string, gui::ButtonBaseClass*> buttons;
	std::pair<std::string, gui::ButtonBaseClass*> button;
	sf::RectangleShape ButtonsBG;



	//Inits
	void initVariables();
	void initkeys();
	void initGui();
	void initButtons();

};

#endif //!_MAINMENUSTATE