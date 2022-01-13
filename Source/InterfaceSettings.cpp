// ================================================================================================================================================================================ //
//  Includes.                                                                                                                                                                       //
// ================================================================================================================================================================================ //

#include "Interface.h"
#include <string>
#include <iostream>

// ================================================================================================================================================================================ //
//  Settings Main.                                                                                                                                                                  //
// ================================================================================================================================================================================ //

void Interface::settingsMenu() 
{
	clear();
	systemInfo();
	std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
	std::cout << green << "\t   |-> " << yellow << "Settings.\n";
	std::cout << green << "\t  [1]: " << white << "Sampling frequency.\n";
	std::cout << green << "\t  [2]: " << white << "Wave frequency.\n";
	std::cout << green << "\t  [3]: " << white << "TX gain.\n";
	std::cout << green << "\t  [4]: " << white << "RX gain.\n";
	std::cout << green << "\t  [5]: " << white << "Filter bandwidth.\n";
	std::cout << green << "\t  [0]: " << white << "Return.\n";
	m_currentTerminalLine += 8;
	menuListBar(1);
	unsigned int answer;
	readInput(&answer);

	// Handle errors.
	while (answer < 0 || answer > 5) 
	{
		clear();
		systemInfo();
		std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
		std::cout << green << "\t   |-> " << yellow << "Settings.\n";
		std::cout << green << "\t  [1]: " << white << "Sampling frequency.\n";
		std::cout << green << "\t  [2]: " << white << "Wave frequency.\n";
		std::cout << green << "\t  [3]: " << white << "TX gain.\n";
		std::cout << green << "\t  [4]: " << white << "RX gain.\n";
		std::cout << green << "\t  [5]: " << white << "Filter bandwidth.\n";
		std::cout << green << "\t  [0]: " << white << "Return.\n";
		m_currentTerminalLine += 9;
		menuListBar(1);
		printError(answer);
		readInput(&answer);
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
	clear();
	systemInfo();
	std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
	std::cout << green << "\t   |-> " << yellow << "Settings.\n";
	std::cout << green << "\t   |-> " << yellow << "Sampling frequency.\n";
	std::cout << green << "\t  [i]: " << white << "The Ettus B210 only supports up to 30.72 MHz (simplex).\n";
	std::cout << green << "\t  [i]: " << white << "Enter the new value [MHz]:\n";
	m_currentTerminalLine += 5;
	menuListBar(1);
	double answer;
	readInput(&answer);

	while (answer == -1 || answer > 30.72 || answer < 0)
	{
		if (answer == -1) 
		{
			clear();
			systemInfo();
			std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
			std::cout << green << "\t   |-> " << yellow << "Settings.\n";
			std::cout << green << "\t   |-> " << yellow << "Sampling frequency.\n";
			std::cout << green << "\t  [i]: " << white << "The Ettus B210 only supports up to 30.72 MHz (simplex).\n";
			std::cout << green << "\t  [i]: " << white << "Enter the new value [MHz]:\n";
			m_currentTerminalLine += 6;
			menuListBar(1);
			printError(answer);
			readInput(&answer);
		}
		else 
		{
			clear();
			systemInfo();
			std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
			std::cout << green << "\t   |-> " << yellow << "Settings.\n";
			std::cout << green << "\t   |-> " << yellow << "Sampling frequency.\n";
			std::cout << green << "\t  [i]: " << white << "The Ettus B210 only supports up to 30.72 MHz (simplex).\n";
			std::cout << green << "\t  [i]: " << white << "Enter the new value [MHz]:\n";
			m_currentTerminalLine += 6;
			menuListBar(1);
			std::cout << red << "\t[ERROR]: " << white << "The Ettus B210 does not accept a sampling rate of " << answer << " MHz.\n";
			readInput(&answer);
		}
	}

	answer *= 1e6;
	m_settingsStatusSDR = "Changed settings not uploaded to SDR.";
	m_settingsStatusYAML = "Changed settings not saved to YAML file.";
	m_txSamplingFrequencyTarget = answer;
	m_rxSamplingFrequencyTarget = answer;
	tx_rate = m_txSamplingFrequencyTarget;
	rx_rate = m_rxSamplingFrequencyTarget;
	settingsMenu();
}

void Interface::setWaveFrequency() 
{
	clear();
	systemInfo();
	std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
	std::cout << green << "\t   |-> " << yellow << "Settings.\n";
	std::cout << green << "\t   |-> " << yellow << "Wave frequency.\n";
	std::cout << green << "\t  [i]: " << white << "The Ettus B210 only supports between 46 and 6016 MHz.\n";
	std::cout << green << "\t  [i]: " << white << "Enter the new value [MHz]:\n";
	m_currentTerminalLine += 5;
	menuListBar(1);
	double answer;
	readInput(&answer);

	while (answer == -1 || answer < 46 || answer > 6016)
	{
		if (answer == -1) 
		{
			clear();
			systemInfo();
			std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
			std::cout << green << "\t   |-> " << yellow << "Settings.\n";
			std::cout << green << "\t   |-> " << yellow << "Wave frequency.\n";
			std::cout << green << "\t  [i]: " << white << "The Ettus B210 only supports between 46 and 6016 MHz.\n";
			std::cout << green << "\t  [i]: " << white << "Enter the new value [MHz]:\n";
			m_currentTerminalLine += 6;
			menuListBar(1);
			printError(answer);
			readInput(&answer);
		}
		else 
		{
			clear();
			systemInfo();
			std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
			std::cout << green << "\t   |-> " << yellow << "Settings.\n";
			std::cout << green << "\t   |-> " << yellow << "Wave frequency.\n";
			std::cout << green << "\t  [i]: " << white << "The Ettus B210 only supports between 46 and 6016 MHz.\n";
			std::cout << green << "\t  [i]: " << white << "Enter the new value [MHz]:\n";
			m_currentTerminalLine += 6;
			menuListBar(1);
			std::cout << red << "\t[ERROR]: " << white << "The Ettus B210 does not accept a wave frequency of " << answer << " MHz.\n";
			readInput(&answer);
		}
	}

	answer *= 1e6;
	m_settingsStatusSDR = "Changed settings not uploaded to SDR.";
	m_settingsStatusYAML = "Changed settings not saved to YAML file.";
	m_txFreqTarget = answer;
	m_rxFreqTarget = answer;
	tx_freq = m_txFreqTarget;
	rx_freq = m_rxFreqTarget;
	settingsMenu();
}

void Interface::setTXGain() 
{
	clear();
	systemInfo();
	std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
	std::cout << green << "\t   |-> " << yellow << "Settings.\n";
	std::cout << green << "\t   |-> " << yellow << "TX gain.\n";
	std::cout << green << "\t  [i]: " << white << "The Ettus B210 only supports up to 89.75 dB.\n";
	std::cout << green << "\t  [i]: " << white << "Enter the new value [dB]:\n";
	m_currentTerminalLine += 5;
	menuListBar(1);
	double answer;
	readInput(&answer);

	while (answer == -1 || answer < 0 || answer > 89.75)
	{
		if (answer == -1) 
		{
			clear();
			systemInfo();
			std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
			std::cout << green << "\t   |-> " << yellow << "Settings.\n";
			std::cout << green << "\t   |-> " << yellow << "TX gain.\n";
			std::cout << green << "\t  [i]: " << white << "The Ettus B210 only supports up to 89.75 dB.\n";
			std::cout << green << "\t  [i]: " << white << "Enter the new value [dB]:\n";
			m_currentTerminalLine += 6;
			menuListBar(1);
			printError(answer);
			readInput(&answer);
		}
		else
		{
			clear();
			systemInfo();
			std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
			std::cout << green << "\t   |-> " << yellow << "Settings.\n";
			std::cout << green << "\t   |-> " << yellow << "TX gain.\n";
			std::cout << green << "\t  [i]: " << white << "The Ettus B210 only supports up to 89.75 dB.\n";
			std::cout << green << "\t  [i]: " << white << "Enter the new value [dB]:\n";
			m_currentTerminalLine += 6;
			menuListBar(1);
			std::cout << red << "\t[ERROR]: " << white << "The Ettus B210 does not accept a TX gain of " << answer << " dB.\n";
			readInput(&answer);
		}
	}

	m_settingsStatusSDR = "Changed settings not uploaded to SDR.";
	m_settingsStatusYAML = "Changed settings not saved to YAML file.";
	m_txGainTarget = answer;
	tx_gain = m_txGainTarget;
	settingsMenu();
}

void Interface::setRXGain() 
{
	clear();
	systemInfo();
	std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
	std::cout << green << "\t   |-> " << yellow << "Settings.\n";
	std::cout << green << "\t   |-> " << yellow << "RX gain.\n";
	std::cout << green << "\t  [i]: " << white << "The Ettus B210 only supports up to 76 dB.\n";
	std::cout << green << "\t  [i]: " << white << "Enter the new value [dB]:\n";
	m_currentTerminalLine += 5;
	menuListBar(1);
	double answer;
	readInput(&answer);

	while (answer == -1 || answer < 0 || answer > 76)
	{
		if (answer == -1) 
		{
			clear();
			systemInfo();
			std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
			std::cout << green << "\t   |-> " << yellow << "Settings.\n";
			std::cout << green << "\t   |-> " << yellow << "RX gain.\n";
			std::cout << green << "\t  [i]: " << white << "The Ettus B210 only supports up to 76 dB.\n";
			std::cout << green << "\t  [i]: " << white << "Enter the new value [dB]:\n";
			m_currentTerminalLine += 6;
			menuListBar(1);
			printError(answer);
			readInput(&answer);
		}
		else 
		{
			clear();
			systemInfo();
			std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
			std::cout << green << "\t   |-> " << yellow << "Settings.\n";
			std::cout << green << "\t   |-> " << yellow << "RX gain.\n";
			std::cout << green << "\t  [i]: " << white << "The Ettus B210 only supports up to 76 dB.\n";
			std::cout << green << "\t  [i]: " << white << "Enter the new value [dB]:\n";
			m_currentTerminalLine += 6;
			menuListBar(1);
			std::cout << red << "\t[ERROR]: " << white << "The Ettus B210 does not accept a RX gain of " << answer << " dB.\n";
			readInput(&answer);
		}
	}

	m_settingsStatusSDR = "Changed settings not uploaded to SDR.";
	m_settingsStatusYAML = "Changed settings not saved to YAML file.";
	m_rxGainTarget = answer;
	rx_gain = m_rxGainTarget;
	settingsMenu();
}

void Interface::setFilterBandwidth() 
{
	clear();
	systemInfo();
	std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
	std::cout << green << "\t   |-> " << yellow << "Settings.\n";
	std::cout << green << "\t   |-> " << yellow << "Filter bandwidth.\n";
	std::cout << green << "\t  [i]: " << white << "The Ettus B210 supports a value of up to 56 MHz.\n";
	std::cout << green << "\t  [i]: " << white << "Enter the new value [MHz]:\n";
	m_currentTerminalLine += 5;
	menuListBar(1);
	double answer;
	readInput(&answer);

	while (answer == -1 || answer < 0 || answer > 56)
	{
		if (answer == -1)
		{
			clear();
			systemInfo();
			std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
			std::cout << green << "\t   |-> " << yellow << "Settings.\n";
			std::cout << green << "\t   |-> " << yellow << "Filter bandwidth.\n";
			std::cout << green << "\t  [i]: " << white << "The Ettus B210 supports a value of up to 56 MHz.\n";
			std::cout << green << "\t  [i]: " << white << "Enter the new value [MHz]:\n";
			m_currentTerminalLine += 6;
			menuListBar(1);
			printError(answer);
			readInput(&answer);
		}
		else 
		{
			clear();
			systemInfo();
			std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
			std::cout << green << "\t   |-> " << yellow << "Settings.\n";
			std::cout << green << "\t   |-> " << yellow << "Filter bandwidth.\n";
			std::cout << green << "\t  [i]: " << white << "The Ettus B210 supports a value of up to 56 MHz.\n";
			std::cout << green << "\t  [i]: " << white << "Enter the new value [MHz]:\n";
			m_currentTerminalLine += 6;
			menuListBar(1);
			std::cout << red << "\t[ERROR]: " << white << "The Ettus B210 does not accept a filter bandwidth of " << answer << " MHz.\n";
			readInput(&answer);
		}
	}

	answer *= 1e6;
	m_settingsStatusSDR = "Changed settings not uploaded to SDR.";
	m_settingsStatusYAML = "Changed settings not saved to YAML file.";
	m_txBWTarget = answer;
	m_rxBWTarget = answer;
	tx_bw = m_txBWTarget;
	rx_bw = m_rxBWTarget;
	settingsMenu();
}

void Interface::saveSettings() 
{
	clear();
	systemInfo();
	std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
	std::cout << green << "\t   |-> " << yellow << "Save settings.\n";
	std::cout << green << "\t  [i]: " << white << "Save the current settings to file?\n";
	std::cout << green << "\t  [1]: " << white << "Yes.\n";
	std::cout << green << "\t  [0]: " << white << "No.\n";
	m_currentTerminalLine += 5;
	menuListBar(1);
	unsigned int answer;
	readInput(&answer);

	while (answer != 0 && answer != 1) 
	{
		clear();
		systemInfo();
		std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
		std::cout << green << "\t   |-> " << yellow << "Save settings.\n";
		std::cout << green << "\t  [i]: " << white << "Save the current settings to file?\n";
		std::cout << green << "\t  [1]: " << white << "Yes.\n";
		std::cout << green << "\t  [0]: " << white << "No.\n";
		m_currentTerminalLine +=6;
		menuListBar(1);
		printError(answer);
		readInput(&answer);
	}
	if (answer == 1) { saveToYAML(); }
	mainMenu();
}

// ================================================================================================================================================================================ //
//  EOF.	                                                                                                                                                                        //
// ================================================================================================================================================================================ //