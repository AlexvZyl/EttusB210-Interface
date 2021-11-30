// ================================================================================================================================================================================ //
//  Includes.                                                                                                                                                                       //
// ================================================================================================================================================================================ //

#include "Interface.h"

// ================================================================================================================================================================================ //
//  Menu.                                                                                                                                                                           //
// ================================================================================================================================================================================ //

void Interface::waveFormMenu() 
{
	clear();
	systemInfo();
	std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
	std::cout << green << "\t   |-> " << yellow << "Waveform.\n";
	std::cout << green << "\t  [1]: " << white << "Radar max range.\n";
	std::cout << green << "\t  [2]: " << white << "Radar dead zone range.\n";
	std::cout << green << "\t  [3]: " << white << "Radar transmission time.\n";
	std::cout << green << "\t  [0]: " << white << "Return.\n";
	m_currentTerminalLine += 6;
	menuListBar(1);
	unsigned int answer;
	readInput(&answer);

	// Handle errors.
	while (answer < 0 || answer > 3)
	{
		clear();
		systemInfo();
		std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
		std::cout << green << "\t   |-> " << yellow << "Waveform.\n";
		std::cout << green << "\t  [1]: " << white << "Radar max range.\n";
		std::cout << green << "\t  [2]: " << white << "Radar dead zone range.\n";
		std::cout << green << "\t  [3]: " << white << "Radar transmission time.\n";
		std::cout << green << "\t  [0]: " << white << "Return.\n";
		m_currentTerminalLine += 7;
		menuListBar(1);
		printError(answer);
		readInput(&answer);
	}

	switch (answer)
	{
	case 1:
		setMaxRange();
		break;
	case 2:
		setDeadzoneRange();
		break;
	case 3:
		setTxTime();
		break;
	case 0:
		break;
	}
}

// ================================================================================================================================================================================ //
//  Settings.                                                                                                                                                                       //
// ================================================================================================================================================================================ //

void Interface::setMaxRange()
{
	clear();
	systemInfo();
	std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
	std::cout << green << "\t   |-> " << yellow << "Waveform.\n";
	std::cout << green << "\t   |-> " << yellow << "Radar max range.\n";
	std::cout << green << "\t  [i]: " << white << "The maximum range at which the radar can detect targets.\n";
	std::cout << green << "\t  [i]: " << white << "Enter the new value [m]:\n";
	m_currentTerminalLine += 5;
	menuListBar(1);
	double answer;
	readInput(&answer);
	while (answer == -1)
	{
		clear();
		systemInfo();
		std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
		std::cout << green << "\t   |-> " << yellow << "Waveform.\n";
		std::cout << green << "\t   |-> " << yellow << "Radar max range.\n";
		std::cout << green << "\t  [i]: " << white << "The maximum range at which the radar can detect targets.\n";
		std::cout << green << "\t  [i]: " << white << "Enter the new value [m]:\n";
		m_currentTerminalLine += 6;
		menuListBar(1);
		printError(answer);
		readInput(&answer);
	}
	m_settingsStatusSDR = "Changed settings not uploaded to SDR.";
	m_settingsStatusYAML = "Changed settings not saved to YAML file.";
	m_maxRange = answer;
	calculatePulsesPerTX();
	waveFormMenu();
}

void Interface::setDeadzoneRange()
{
	clear();
	systemInfo();
	std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
	std::cout << green << "\t   |-> " << yellow << "Waveform.\n";
	std::cout << green << "\t   |-> " << yellow << "Radar dead zone range.\n";
	std::cout << green << "\t  [i]: " << white << "The range where the radar is blind.  A longer dead zone leads to higher SNR.\n";
	std::cout << green << "\t  [i]: " << white << "Enter the new value [m]:\n";
	m_currentTerminalLine += 5;
	menuListBar(1);
	double answer;
	readInput(&answer);
	while (answer == -1)
	{
		clear();
		systemInfo();
		std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
		std::cout << green << "\t   |-> " << yellow << "Waveform.\n";
		std::cout << green << "\t   |-> " << yellow << "Radar max range.\n";
		std::cout << green << "\t  [i]: " << white << "The range where the radar is blind.  A longer dead zone leads to higher SNR.\n";
		std::cout << green << "\t  [i]: " << white << "Enter the new value [m]:\n";
		m_currentTerminalLine += 6;
		menuListBar(1);
		printError(answer);
		readInput(&answer);
	}
	m_settingsStatusSDR = "Changed settings not uploaded to SDR.";
	m_settingsStatusYAML = "Changed settings not saved to YAML file.";
	m_deadzone = answer;
	calculatePulsesPerTX();
	waveFormMenu();
}

void Interface::setTxTime()
{
	clear();
	systemInfo();
	std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
	std::cout << green << "\t   |-> " << yellow << "Waveform.\n";
	std::cout << green << "\t   |-> " << yellow << "Radar transmission time.\n";
	std::cout << green << "\t  [i]: " << white << "How long the radar transmits.  Longer times lead to higher SNR values.\n";
	std::cout << green << "\t  [i]: " << white << "Enter the new value [s]:\n";
	m_currentTerminalLine += 5;
	menuListBar(1);
	double answer;
	readInput(&answer);
	while (answer == -1)
	{
		clear();
		systemInfo();
		std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
		std::cout << green << "\t   |-> " << yellow << "Waveform.\n";
		std::cout << green << "\t   |-> " << yellow << "Radar transmission time.\n";
		std::cout << green << "\t  [i]: " << white << "How long the radar transmits.  Longer times lead to higher SNR values.\n";
		std::cout << green << "\t  [i]: " << white << "Enter the new value [s]:\n";
		m_currentTerminalLine += 6;
		menuListBar(1);
		printError(answer);
		readInput(&answer);
	}
	m_settingsStatusSDR = "Changed settings not uploaded to SDR.";
	m_settingsStatusYAML = "Changed settings not saved to YAML file.";
	m_txDuration = answer;
	calculatePulsesPerTX();
	waveFormMenu();
}

void Interface::calculatePulsesPerTX()
{
	// Now calculate the amount of pulses that are transmitted with each transmission cycle.
	m_pulsesPerTransmission = std::floor((m_txDuration * m_txSamplingFrequencyTarget) / m_waveLengthSamples);
}

// ================================================================================================================================================================================ //
//  EOF.	                                                                                                                                                                        //
// ================================================================================================================================================================================ //
