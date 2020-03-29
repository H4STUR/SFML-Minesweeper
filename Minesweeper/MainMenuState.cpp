#include "stdafx.h"
#include "MainMenuState.h"

//Inits
void MainMenuState::initVariables()
{
	std::string elements_list[3]
	{
		"FIST",
		"SECOND",
		"XDDD"
	};

	
}

void MainMenuState::initkeys()
{

}

void MainMenuState::initGui()
{

	//Background stuff
	{
		this->backGround.setSize(
			sf::Vector2f(
				static_cast<float>(this->data->resolution.width),
				static_cast<float>(this->data->resolution.height)
			)
		);

		//BackGround
		this->backGround.setPosition(sf::Vector2f(0,0));
		this->backGround.setFillColor(sf::Color(200, 200, 200, 220));

		//IMG in the middle of main menu
		if (this->symbolTex.loadFromFile("resources/symbolMainMenu.png"))
		{
			this->symbol.setTexture(&this->symbolTex);
			this->symbol.setSize(sf::Vector2f(this->data->PercentSizeX(50.f), this->data->PercentSizeX(50.f)));

			this->symbol.setPosition(
			sf::Vector2f((this->data->resolution.width / 2) - (symbol.getSize().x / 2),
						 (this->data->resolution.height / 2) - (symbol.getSize().y / 2) + this->data->PercentSizeY(3.5f)));
			
			

			if (this->data->DebugMode)
				printf("BackGround Texture Succesfuly Loaded!\n");
		}
		else
			printf("ERROR! symbol IMG Cannot be Loaded! :: MainMenuState -> initGui()\n");
	}


}

void MainMenuState::initButtons()
{
	//Easy button
	this->button =
		std::make_pair("EASY", new gui::Button("EASY", this->data->PercentSizeY(4.f), this->data->font,
			this->data->PercentSize(35.f, 10.f), this->data->PercentSize(30.f, 15.f),
			sf::Color(69, 69, 69, 255), sf::Color(169, 169, 169, 255), sf::Color(20, 20, 20, 255),
			sf::Color(20, 20, 20, 255), sf::Color(69, 69, 69, 255), sf::Color(0, 0, 0, 255)));

	this->buttons.insert(std::move(button));

	//Easy button
	this->button =
		std::make_pair("MEDIUM", new gui::Button("MEDIUM", this->data->PercentSizeY(4.f), this->data->font,
			this->data->PercentSize(35.f, 30.f), this->data->PercentSize(30.f, 15.f),
			sf::Color(69, 69, 69, 255), sf::Color(169, 169, 169, 255), sf::Color(20, 20, 20, 255),
			sf::Color(20, 20, 20, 255), sf::Color(69, 69, 69, 255), sf::Color(0, 0, 0, 255)));

	this->buttons.insert(std::move(button));

	//Easy button
	this->button =
		std::make_pair("HARD", new gui::Button("HARD", this->data->PercentSizeY(4.f), this->data->font,
			this->data->PercentSize(35.f, 50.f), this->data->PercentSize(30.f, 15.f),
			sf::Color(69, 69, 69, 255), sf::Color(169, 169, 169, 255), sf::Color(20, 20, 20, 255),
			sf::Color(20, 20, 20, 255), sf::Color(69, 69, 69, 255), sf::Color(0, 0, 0, 255)));

	this->buttons.insert(std::move(button));

	//EXIT button
	this->button =
		std::make_pair("EXIT", new gui::Button("EXIT", this->data->PercentSizeY(4.f), this->data->font,
			this->data->PercentSize(35.f, 70.f), this->data->PercentSize(30.f, 15.f),
			sf::Color(69, 69, 69, 255), sf::Color(169, 169, 169, 255), sf::Color(20, 20, 20, 255),
			sf::Color(20, 20, 20, 255), sf::Color(69, 69, 69, 255), sf::Color(0, 0, 0, 255)));

	this->buttons.insert(std::move(button));
	
}


//Constructor && Destructors
MainMenuState::MainMenuState(Data* data)
	: State(data)
{
	this->initVariables();
	this->initkeys();
	this->initGui();
	this->initButtons();
}


MainMenuState::~MainMenuState()
{
	for (auto &i : this->buttons)
		delete i.second;
}

//Functions
//Update
void MainMenuState::update(const float & deltatime)
{
	this->updateKeytime(deltatime);
	this->updateMousePos();
	this->updateInput(deltatime);
	this->updateButtons(deltatime);
}

void MainMenuState::updateInput(const float & deltaTime)
{
}

void MainMenuState::updateButtons(const float & deltaTime)
{
	//Updates buttons status
	for (auto &i : this->buttons)
		i.second->update(this->mousePosWindow);

	//Easy button
	if (this->buttons["EASY"]->pressed() && this->getKeytime())
	{
		std::cout << "\nEasy button\n";
		
		this->data->states->push(new GameState(this->data, sf::Vector2i(8, 8)));
	}	
	
	//Medium button
	if (this->buttons["MEDIUM"]->pressed() && this->getKeytime())
	{
		std::cout << "\nMedium button\n";
		this->data->states->push(new GameState(this->data, sf::Vector2i(16, 16)));
	}	
	
	//Hard button
	if (this->buttons["HARD"]->pressed() && this->getKeytime())
	{
		std::cout << "\nHard button\n";
		this->data->states->push(new GameState(this->data, sf::Vector2i(32, 16)));
	}

	//just exit button... nothing special, thanks for reading 
	if (this->buttons["EXIT"]->pressed() && this->getKeytime())
	{
		this->endState();
	}

}

//Render
void MainMenuState::renderButtons(sf::RenderTarget * target)
{
	for (auto &i : this->buttons)
		i.second->render(target);

}

void MainMenuState::renderGui(sf::RenderTarget * target)
{
	target->draw(this->backGround);
	target->draw(this->ButtonsBG);
	target->draw(this->symbol);
}


void MainMenuState::render(sf::RenderTarget * target)
{
	this->renderGui(target);
	this->renderButtons(target);
}