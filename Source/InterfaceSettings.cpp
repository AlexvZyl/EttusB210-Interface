// ================================================================================================================================================================================ //
//  Includes.                                                                                                                                                                       //
// ================================================================================================================================================================================ //

#include "Interface.h"

// ================================================================================================================================================================================ //
//  Settings Main.                                                                                                                                                                  //
// ================================================================================================================================================================================ //

void Interface::settingsMenu() 
{
	int answer;
	clear();
	systemInfo();
	std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
	std::cout << green << "\t   |-> " << yellow << "Settings.\n";
	std::cout << green << "\t  [1]: " << white << "Sampling frequency.\n";
	std::cout << green << "\t  [2]: " << white << "Wave frequency.\n";
	std::cout << green << "\t  [3]: " << white << "TX Gain.\n";
	std::cout << green << "\t  [4]: " << white << "RX Gain.\n";
	std::cout << green << "\t  [5]: " << white << "Filter bandwidth.\n";
	std::cout << green << "\t  [0]: " << white << "Return.\n";
	std::cout << green << "\t[INPUT]: " << white;
	std::cin >> answer;

	while (answer < 0 || answer > 5) 
	{
		clear();
		systemInfo();
		std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
		std::cout << green << "\t   |-> " << yellow << "Settings.\n";
		std::cout << green << "\t  [1]: " << white << "Sampling frequency.\n";
		std::cout << green << "\t  [2]: " << white << "Wave frequency.\n";
		std::cout << green << "\t  [3]: " << white << "TX Gain.\n";
		std::cout << green << "\t  [4]: " << white << "RX Gain.\n";
		std::cout << green << "\t  [5]: " << white << "Filter bandwidth.\n";
		std::cout << green << "\t  [0]: " << white << "Return.\n";
		std::cout << red << "\t[ERROR]: " << white << "'" << answer << "' is not a valid option.\n";
		std::cout << green << "\t[INPUT]: " << white;
		std::cin >> answer;
	}

	switch (answer) 
	{
	case 1:
		setSamplingFrequency();
		break;
	case 2:
		setWaveFrequency();
		break;
	case 3:
		setTXGain();
		break;
	case 4:
		setRXGain();
		break;
	case 5:
		setFilterBandwidth();
		break;
	case 0:
		break;
	}
}

// ================================================================================================================================================================================ //
//  Set settings.                                                                                                                                                                  //
// ================================================================================================================================================================================ //

void Interface::setSamplingFrequency() 
{
	int answer;
	clear();
	systemInfo();
	std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
	std::cout << green << "\t   |-> " << yellow << "Settings.\n";
	std::cout << green << "\t   |-> " << yellow << "Sampling frequency.\n";
	std::cout << green << "\t  [i]: " << white << "Enter the new value:\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t[INPUT]: " << white;
	std::cin >> answer;
	m_settingsStatus = "Changed settings not uploaded.";
	settingsMenu();
}

void Interface::setWaveFrequency() 
{
	int answer;
	clear();
	systemInfo();
	std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
	std::cout << green << "\t   |-> " << yellow << "Settings.\n";
	std::cout << green << "\t   |-> " << yellow << "Wave frequency.\n";
	std::cout << green << "\t  [i]: " << white << "Enter the new value:\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t[INPUT]: " << white;
	std::cin >> answer;
	m_settingsStatus = "Changed settings not uploaded.";
	settingsMenu();

}

void Interface::setTXGain() 
{
	int answer;
	clear();
	systemInfo();
	std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
	std::cout << green << "\t   |-> " << yellow << "Settings.\n";
	std::cout << green << "\t   |-> " << yellow << "TX gain.\n";
	std::cout << green << "\t  [i]: " << white << "Enter the new value:\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t[INPUT]: " << white;
	std::cin >> answer;
	m_settingsStatus = "Changed settings not uploaded.";

	settingsMenu();

}

void Interface::setRXGain() 
{
	int answer;
	clear();
	systemInfo();
	std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
	std::cout << green << "\t   |-> " << yellow << "Settings.\n";
	std::cout << green << "\t   |-> " << yellow << "RX gain.\n";
	std::cout << green << "\t  [i]: " << white << "Enter the new value:\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t[INPUT]: " << white;
	std::cin >> answer;
	m_settingsStatus = "Changed settings not uploaded.";

	settingsMenu();

}

void Interface::setFilterBandwidth() 
{
	int answer;
	clear();
	systemInfo();
	std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
	std::cout << green << "\t   |-> " << yellow << "Settings.\n";
	std::cout << green << "\t   |-> " << yellow << "Filter bandwidth.\n";
	std::cout << green << "\t  [i]: " << white << "Enter the new value:\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t[INPUT]: " << white;
	std::cin >> answer;
	m_settingsStatus = "Changed settings not uploaded.";
	settingsMenu();

}

// ================================================================================================================================================================================ //
//  EOF.	                                                                                                                                                                        //
// ================================================================================================================================================================================ //