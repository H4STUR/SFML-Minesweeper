#include "stdafx.h"
#include <windows.h>
#include "Game.h"

inline void CloseConsole()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//CloseConsole();

	Game game;

	game.run();

	return 0;
}