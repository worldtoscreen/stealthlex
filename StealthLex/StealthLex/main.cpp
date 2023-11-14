#define _CRT_SECURE_NO_WARNINGS //Sombody please tell microsoft to kill themselves :3

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <cstdlib>
#include <string>
#include <thread>
#include <nlohmann/json.hpp>
#include "fs.hpp"
#include "config.hpp"
#include "output.hpp"
#include "binding.hpp"


int main(int argc, char* argv[])
{
	//Setup

	outputDebug("Initalizing Stealthlex...");

	system("color 0b");
	system("cls");

	//Look for previous configs
	//Directory: %appdata%/StealthLex/config

	{
		//Check if %appdata% exists
		std::filesystem::path appData = std::getenv("APPDATA");

		if (directoryExists(appData))
		{
			outputDebug("AppData Path exists");
		}
		else {
			outputDebug("ERROR! App Data Path doesn\'t exist.");
			failed(); //kinda like abort but for us
		}
	}

	{
		//Check if %appdata%/StealthLex exists
		std::filesystem::path stealthLexFolderDir = std::getenv("APPDATA");
		stealthLexFolderDir /= "StealthLex";

		if (directoryExists(stealthLexFolderDir))
		{
			outputDebug("StealthLex folder exists");
		}
		else {

			//It doesn't exist, create it!
			outputDebug("StealthLex folder doesn\'t exist. Creating it now...");

			if (createDirectory(stealthLexFolderDir))
			{
				outputDebug("Successfully created StealthLex folder.");
			}
			else {
				outputDebug("Failed to create StealthLex folder.");
				failed();
			}

		}

	}

	{
		//Check if the config file exists
		std::filesystem::path configFilePath = std::getenv("APPDATA");
		configFilePath /= "StealthLex";
		configFilePath /= "stealthlex.json";


		if (fileExists(configFilePath))
		{
			outputDebug("Found config file! Parasing...");


			if (loadConfig(configFilePath))
			{
				/*
				std::cout << "injectionBind: " << injectionConfig::injectionBind << std::endl;
				std::cout << "beepOnInjection: " << injectionConfig::beepOnInjection << std::endl;
				std::cout << "beepFreq: " << injectionConfig::beepFreq << std::endl;
				std::cout << "beepDur: " << injectionConfig::beepDur << std::endl;

				// Output values in the 'uninjectConfig' namespace
				std::cout << "uninjectBind: " << uninjectConfig::uninjectBind << std::endl;
				std::cout << "beepOnUninjection: " << uninjectConfig::beepOnUninjection << std::endl;
				std::cout << "beepFreq: " << uninjectConfig::beepFreq << std::endl;
				std::cout << "beepDur: " << uninjectConfig::beepDur << std::endl;

				// Output values in the 'deleteTracesConfig' namespace
				std::cout << "deleteTracesBind: " << deleteTracesConfig::deleteTracesBind << std::endl;
				std::cout << "beepOnDeleteTraces: " << deleteTracesConfig::beepOnDeleteTraces << std::endl;
				std::cout << "beepFreq: " << deleteTracesConfig::beepFreq << std::endl;
				std::cout << "beepDur: " << deleteTracesConfig::beepDur << std::endl;
				*/
				
				//hide console
				//FreeConsole();
				
				//Do main loop
				bool done = false;
				bool has_injected = true;

				

				while (!done)
				{
					HWND robloxHandle = FindWindowA(NULL, "RobloxPlayerBeta.exe");

					

					Sleep(100); //delay

					//Check if the key is the injection key
					if (GetAsyncKeyState(injectionConfig::injectionBind) & 1)
					{
						//Start to inject
						if (injectionConfig::beepOnInjection) { Beep(injectionConfig::beepFreq, injectionConfig::beepDur); }
						//Run Client.exe

						std::filesystem::path client_exe_path = std::getenv("APPDATA");
						client_exe_path /= "celex-v2";
						client_exe_path /= "client.exe";

						runFile(client_exe_path);

						has_injected = true;

						SetForegroundWindow(robloxHandle);

					}
					
					//Check if the key is the uninject key					
					if (GetAsyncKeyState(int(uninjectConfig::uninjectBind)))
					{
						std::cout << "Uninjecting..." << std::endl;
						//Start to uninject - taskkill /IM client.exe
						if (uninjectConfig::beepOnUninjection) { Beep(uninjectConfig::beepFreq, uninjectConfig::beepDur); }
						

						system("taskkill /F /IM client.exe"); //I LOVE IOCTL
						SetForegroundWindow(robloxHandle);
						system("taskkill /F /IM cmd.exe"); //I LOVE IOCTL
						SetForegroundWindow(robloxHandle);


						has_injected = false;


					}

					//Check if the key is the delete traces key
					if (GetAsyncKeyState(deleteTracesConfig::deleteTracesBind) & 1)
					{
						//Start to delete traces - delete celex directory, delete executable, delete config & config folder
						if (deleteTracesConfig::beepOnDeleteTraces) { Beep(deleteTracesConfig::beepFreq, deleteTracesConfig::beepDur); }
						
						//Delete the following directories:
						//%appdata%/celex-v2
						//%appdata%/StealthLex
						//stealthlex executable (current executable path)

						//Then
						//Check registry for celex auth keys and delete them [NICK SAID THERE ARE NONE AND WE TRUST NICK)
						//Exit

						std::filesystem::path appdata = std::getenv("APPDATA"); //App Data Directory

						//Delete the traces :money_mouth:
						SetForegroundWindow(robloxHandle);
						std::filesystem::remove_all(appdata / "celex-v2"); //Celex - loader, client, user.json, configs
						SetForegroundWindow(robloxHandle);
						std::filesystem::remove_all(appdata / "StealthLex"); //StealthLex - config.json
						SetForegroundWindow(robloxHandle);

						//Get current EXE path
						//(LATER)

						
					}
				}

				exit(0);
			}
			else {
				outputDebug("Failed to parase config file.");
				failed();
			}
			
		}
		else {
			outputDebug("Config file not found - creating it now...");
			//Create the config file and name it stealthlex.json

			if (createFile(configFilePath))
			{
				outputDebug("Successfully created config file.");

				//Configuration
				{
					//Injection config
					getConfig(
						"----Injection----",
						"injection phase",
						injectionConfig::injectionBind,
						injectionConfig::beepOnInjection,
						injectionConfig::beepFreq,
						injectionConfig::beepDur,
						0
					);

					//Uninjection config
					getConfig(
						"----Uninjection----",
						"when StealthLex uninjects",
						uninjectConfig::uninjectBind,
						uninjectConfig::beepOnUninjection,
						uninjectConfig::beepFreq,
						uninjectConfig::beepDur,
						0
					);

					//Delete traces config
					getConfig(
						"----Delete Traces----",
						"when StealthLex deletes traces",
						deleteTracesConfig::deleteTracesBind,
						deleteTracesConfig::beepOnDeleteTraces,
						deleteTracesConfig::beepFreq,
						deleteTracesConfig::beepDur,
						0
					);

					std::cout << "Configured! Converting to JSON and logging...";
					
					//make a json object and log it
					json configData;
					configData["injectionConfig"] = {
						{"injectionBind", injectionConfig::injectionBind},
						{"beepOnInjection", injectionConfig::beepOnInjection},
						{"beepFreq", injectionConfig::beepFreq},
						{"beepDur", injectionConfig::beepDur}
					};

					configData["uninjectConfig"] = {
						{"uninjectBind", uninjectConfig::uninjectBind},
						{"beepOnUninjection", uninjectConfig::beepOnUninjection},
						{"beepFreq", uninjectConfig::beepFreq},
						{"beepDur", uninjectConfig::beepDur}
					};

					configData["deleteTracesConfig"] = {
						{"deleteTracesBind", deleteTracesConfig::deleteTracesBind},
						{"beepOnDeleteTraces", deleteTracesConfig::beepOnDeleteTraces},
						{"beepFreq", deleteTracesConfig::beepFreq},
						{"beepDur", deleteTracesConfig::beepDur}
					};

					// Serialize the JSON data to a string
					std::string jsonData = configData.dump(4); // Optional: Pretty-print with an indentation of 4 spaces

					std::cout << "View JSON? (y/n): ";
					char viewJson;
					std::cin >> viewJson;
					if (viewJson == 'y')
					{
						std::cout << jsonData << std::endl;

						Sleep(1000);
					}

					std::cout << "Logging json to " << configFilePath;
					if (writeToFile(configFilePath, configData))
					{
						std::cout << "Successfully logged json to " << configFilePath;
					}
					else {
						std::cout << "Failed to log json to " << configFilePath;
						failed();
					}

					system("cls");

					//last message you'll see before we minimize

					std::cout << "PLEASE READ THIS!" << std::endl;

					std::cout << "After you press ENTER, StealthLex will become forever hidden.\nYou will need to navigate to %appdata%/StealthLex/stealthlex.json to re-configure stealthlex! Press ENTER to continue...";

					do { } while (!GetAsyncKeyState(VK_RETURN)); //Wait for enter
					//FreeConsole(); //Bye Bye!

					std::string injectionBindStr = std::string(KeyNames[injectionConfig::injectionBind]);
					std::string uninjectBindStr = std::string(KeyNames[uninjectConfig::uninjectBind]);
					std::string deleteTracesBindStr = std::string(KeyNames[deleteTracesConfig::deleteTracesBind]);

					// Create a wide string with the values
					std::wstring message = L"Good luck with your closet cheating - stealth lex will always be with you.\nPress DELETE to make StealthLex close!"
						L" Remember your keybinds:\n\n"
						L"Inject: (" + std::wstring(injectionBindStr.begin(), injectionBindStr.end()) + L")\n"
						L"Uninject: (" + std::wstring(uninjectBindStr.begin(), uninjectBindStr.end()) + L")\n"
						L"Delete Traces: (" + std::wstring(deleteTracesBindStr.begin(), deleteTracesBindStr.end()) + L")\n";


					MessageBoxW(
						NULL,
						message.c_str(),
						L"StealthLex On Top! || discord.gg/bci",
						MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL
					);

					MessageBoxW(
						NULL,
						L"Please Re-Run StealthLex to use it!",
						L"StealthLex On Top! || discord.gg/bci",
						MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL
					);

					exit(0);

				}
				
				

			}
			else {
				outputDebug("Failed to create config file.");
				failed();
			}

		}
	}
}