#define _CRT_SECURE_NO_WARNINGS //Sombody please tell microsoft to kill themselves <3

#include <iostream>

#include "output.hpp"

void outputDebug(std::string info)
{
	std::cout << " [ " << config::dbgSym <<" ] " << info << std::endl;
}

void failed()
{
	outputDebug("StealthLex has detected a failure. Press [ENTER] to exit.");
	outputDebug("You can also delete the config directory by pressing [SPACE]");
	outputDebug("Pressing SPACE will most likley fix this issue.");

	while (true)
	{
		if (GetAsyncKeyState(VK_RETURN) & 1)
		{
			exit(0);
		}
		else if (GetAsyncKeyState(VK_SPACE) & 1)
		{
			std::cout << "Deleting..." << std::endl;

			std::filesystem::path configFilePath = std::getenv("APPDATA");
			configFilePath /= "StealthLex";

			std::filesystem::remove_all(configFilePath);

			std::cout << "Deleted!" << std::endl;

			Sleep(1000);

			exit(0);
		}
	}
}

void getConfig(std::string configType, std::string triggerEvent, int& keyCodeBuf, bool& beepBuf, int& beepFreqBuf, int& beepDurBuf, int delay) //delay in ms: 3 sec
{

	//now, we can can get settings
	Sleep(500);
	system("cls");

	std::cout << "Welcome to StealthLex!\n";
	std::cout << "Stay undetected without the issue of being caught via screen-share!\n";
	std::cout << "You can enter settings below.\n";

	std::cout << "\n\n" << configType << std::endl;

	std::cout << "Press a key to bind injection to..." << std::endl;

	keyCodeBuf = waitUntilKeyPressed();

	std::cout << "StealthLex will inject when you press " << KeyNames[keyCodeBuf] << " (" << keyCodeBuf << ")" << std::endl;
	std::cout << "\n\nWould you like to hear a beep when" << triggerEvent << " (y/n) ";

	char beepOnInjection;

	std::cin >> beepOnInjection;

	if (beepOnInjection == 'y')
	{
		beepBuf = true;
		std::cout << "\nBeep Duration (In MS): ";
		int injectionBeepDurration;
		std::cin >> injectionBeepDurration;
		beepDurBuf = injectionBeepDurration;
		std::cout << "Beep Frequency (In Hz): ";
		int injectionBeepFrequency;
		std::cin >> injectionBeepFrequency;
		beepFreqBuf = injectionBeepFrequency;
		std::cout << "Play test beep? (y/n)";

		char testBeep_injection;
		std::cin >> testBeep_injection;

		if (testBeep_injection == 'y') { Beep(beepFreqBuf, beepDurBuf); }

		testBeep_injection = NULL;
	}
	else {
		beepBuf = false;
	}
	std::cout << "\n" << triggerEvent << " configuration finished...";
	Sleep(delay);
	system("cls");

	beepOnInjection = NULL;
	
	
}