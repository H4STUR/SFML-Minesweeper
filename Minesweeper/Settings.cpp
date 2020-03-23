#include "stdafx.h"
#include "Settings.h"

//Constructors && Destructors
Data::Data()
{
	this->window = nullptr;
	this->states = nullptr;

	this->title = "Minesweeper";
	this->defaultResolution = sf::VideoMode::getDesktopMode();
	this->resolution = this->defaultResolution;
	this->fullstreen = false;
	this->FPSLimit = 64;
	this->videoModes = sf::VideoMode::getFullscreenModes();
	this->DebugMode = true;
}


//Functions
void Data::saveSettings()
{
	std::ofstream ofs("config/settings.ini");
	{
		if (ofs.is_open())
		{
			ofs << this->title;
			ofs << this->defaultResolution.width << " " << this->defaultResolution.height;
			ofs << this->fullstreen;
			ofs << this->FPSLimit;
		}
		else
			printf("Cannot save settings! Settings.cpp :: saveSettings()\n");

		ofs.close();
	}
}

void Data::loadSettings()
{
	{
		std::ifstream ifs("config/settings.ini");

		if (ifs.is_open())
		{
			while (ifs
				>> this->title
				>> this->defaultResolution.width >> this->defaultResolution.height
				>> this->fullstreen
				>> this->FPSLimit
				);
		}
		else
			printf("Cannot load settings! Settings.cpp :: loadSettings() - settings.ini\n");

		ifs.close();
	}

	//Setting current resolution 
	this->resolution = this->defaultResolution;
}

void Data::SwitchDebugMode(bool && DebugMode)
{
	this->DebugMode = DebugMode;
}
