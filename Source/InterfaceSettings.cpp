// ================================================================================================================================================================================ //
//  Includes.                                                                                                                                                                       //
// ================================================================================================================================================================================ //

#include "Interface.h"

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
	std::cout << green << "\t  [3]: " << white << "TX Gain.\n";
	std::cout << green << "\t  [4]: " << white << "RX Gain.\n";
	std::cout << green << "\t  [5]: " << white << "Filter bandwidth.\n";
	std::cout << green << "\t  [0]: " << white << "Return.\n";
	unsigned int answer;
	readInput(&answer);

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
	std::cout << green << "\t  [i]: " << white << "Enter the new value:\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	double answer;
	readInput(&answer);

	while (answer == -1) 
	{
		clear();
		systemInfo();
		std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
		std::cout << green << "\t   |-> " << yellow << "Settings.\n";
		std::cout << green << "\t   |-> " << yellow << "Sampling frequency.\n";
		std::cout << green << "\t  [i]: " << white << "Enter the new value:\n";
		std::cout << green << "\t   |\n";
		std::cout << green << "\t   |\n";
		std::cout << green << "\t   |\n";
		printError(answer);
		readInput(&answer);
	}

	m_settingsStatus = "Changed settings not uploaded.";
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
	std::cout << green << "\t  [i]: " << white << "Enter the new value:\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	double answer;
	readInput(&answer);
	m_settingsStatus = "Changed settings not uploaded.";
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
	std::cout << green << "\t  [i]: " << white << "Enter the new value:\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	double answer;
	readInput(&answer);
	m_settingsStatus = "Changed settings not uploaded.";
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
	std::cout << green << "\t  [i]: " << white << "Enter the new value:\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	double answer;
	readInput(&answer);
	m_settingsStatus = "Changed settings not uploaded.";
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
	std::cout << green << "\t  [i]: " << white << "Enter the new value:\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	std::cout << green << "\t   |\n";
	double answer;
	readInput(&answer);
	m_settingsStatus = "Changed settings not uploaded.";
	m_txBWTarget = answer;
	m_rxBWTarget = answer;
	tx_bw = m_txBWTarget;
	rx_bw = m_rxBWTarget;
	settingsMenu();
}

// ================================================================================================================================================================================ //
//  EOF.	                                                                                                                                                                        //
// ================================================================================================================================================================================ //