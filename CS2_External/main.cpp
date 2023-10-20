#include "Cheats.h"
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <Windows.h>

int main()
{

	std::printf(
	"External Crosshair Tool\n"
	"Source Code: https://github.com/CowNowK/ExternalCrosshair\n"
	"\n"
	"- Support Game: CS2"
	"- Press [INS] to show or hide Menu.\n"
	"\n"
	);

	std::cout << std::endl;
	std::cout << "Window attach successfully!" << std::endl;

	// Gui.NewWindow("External Crosshair Tool", Vec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), Cheats::Run);

	try
	{
		Gui.AttachAnotherWindow("Counter-Strike 2", "SDL_app", Cheats::Run);
	}
	catch (OSImGui::OSException& e)
	{
		try
		{
			Gui.AttachAnotherWindow("反恐精英：全球攻势", "SDL_app", Cheats::Run);
		}
		catch (OSImGui::OSException& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

END:
	std::cout << std::endl;
	system("pause");
	return 0;
}