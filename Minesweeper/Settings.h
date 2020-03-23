#ifndef _DATA
#define _DATA

#include "stdafx.h"
#include "State.h"

class Settings;
class Data;
class State;

//DATA

class Data
{
public:
	Data();

	//Functions
	void saveSettings();
	void loadSettings();
	void SwitchDebugMode(bool&& DebugMode = true);

	inline float PercentSizeX(const float& x)
	{
		return static_cast<float>((x * this->resolution.width) / 100);
	}

	inline float PercentSizeY(const float& y)
	{
		return static_cast<float>((y * this->resolution.height) / 100);
	}

	inline void Resize(sf::VideoMode newResolution)
	{
		this->resolution = newResolution;
		this->window->setSize(sf::Vector2u(
			this->resolution.width,
			this->resolution.height
		));
	}

	//Variables
	std::string title;
	sf::VideoMode resolution;
	sf::VideoMode defaultResolution;
	std::vector<sf::VideoMode> videoModes;
	bool fullstreen;
	unsigned FPSLimit;
	std::vector<std::string> languages;
	bool DebugMode;

	//Variables
	sf::RenderWindow* window;
	std::stack<State*>* states;
};


#endif // !_DATA

/*	config/settings.ini
	
	- window title
	- width - height
	- fullsreen 0/1
	- Frame rate
	- language
*/

/*	config/settings_window.ini

	- easy mode resolution
	- medium mode resolution
	- hard mode resolution
*/