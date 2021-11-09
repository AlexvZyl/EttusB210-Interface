// ================================================================================================================================================================================ //
//  Includes.                                                                                                                                                                       //
// ================================================================================================================================================================================ //

#include "Interface.h"
#include "../External/YAML-CPP/Includes/yaml-cpp/yaml.h"
#include <string>
#include <iostream>
#include <filesystem>

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
	std::cout << green << "\t  [6]: " << white << "Save settings.\n";
	std::cout << green << "\t  [0]: " << white << "Return.\n";
	m_currentTerminalLine += 9;
	menuListBar(1);
	unsigned int answer;
	readInput(&answer);

	// Handle errors.
	while (answer < 0 || answer > 6) 
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
		std::cout << green << "\t  [6]: " << white << "Save settings.\n";
		std::cout << green << "\t  [0]: " << white << "Return.\n";
		m_currentTerminalLine += 10;
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
	case 6:
		saveSettings();
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
	// 56
	// 
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
	std::cout << green << "\t  [i]: " << white << "Save the current settings to file?.\n";
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
		std::cout << green << "\t  [i]: " << white << "Save the current settings to file?.\n";
		std::cout << green << "\t  [1]: " << white << "Yes.\n";
		std::cout << green << "\t  [0]: " << white << "No.\n";
		m_currentTerminalLine +=6;
		menuListBar(1);
		printError(answer);
		readInput(&answer);
	}
	if (answer == 1) { saveToYAML(); }
	settingsMenu();
}

void Interface::saveToYAML() 
{
	// Open the yaml file.

#ifdef _DEBUG
	std::string path = std::filesystem::current_path().string() + "\\Source\\Settings\\Settings.yml";
#else
	std::string path = std::filesystem::current_path().string() + "\\Settings\\Settings.yml";
#endif

	std::ofstream yamlFile;
	yamlFile.open(path);

	// Define titles.
	std::string header		=	   "# ================================================= # \n"
								   "#  Settings of the SDR interface.                   # \n"
								   "#  Allows the saving of sessions for later use.     # \n"
								   "# ================================================= # \n";
	std::string filingTitle	=    "\n#  Filing settings.\n";
	std::string sdrTitle	=  "\n\n#  SDR settings.\n";
	std::string deviceTitle	=  "\n\n#  Device settings.\n";
	std::string end			=  "\n\n# ================================================= #";

	// Write header.
	yamlFile << header;

	// Write filing data.
	yamlFile << filingTitle;
	YAML::Emitter filingOut;
	filingOut << YAML::BeginMap;
	filingOut << YAML::Key << "folder";
	filingOut << YAML::Value << m_folderName;
	filingOut << YAML::Key << "file-latest";
	filingOut << YAML::Value << m_latestFileName;
	filingOut << YAML::Key << "file-target";
	filingOut << YAML::Value << m_targetFileName;
	filingOut << YAML::EndMap;
	yamlFile << filingOut.c_str();

	// Write SDR data.
	yamlFile << sdrTitle;
	YAML::Emitter sdrOut;
	sdrOut << YAML::BeginMap;
	sdrOut << YAML::Key << "sample-rate-tx";
	sdrOut << YAML::Value << m_txSamplingFrequencyTarget;
	sdrOut << YAML::Key << "sample-rate-rx";
	sdrOut << YAML::Value << m_rxSamplingFrequencyTarget;
	sdrOut << YAML::Key << "wave-frequency-tx";
	sdrOut << YAML::Value << m_txFreqTarget;
	sdrOut << YAML::Key << "wave-frequency-rx";
	sdrOut << YAML::Value << m_rxFreqTarget;
	sdrOut << YAML::Key << "gain-tx";
	sdrOut << YAML::Value << m_txGainTarget;
	sdrOut << YAML::Key << "gain-rx";
	sdrOut << YAML::Value << m_rxGainTarget;
	sdrOut << YAML::Key << "filter-bandwidth-tx";
	sdrOut << YAML::Value << m_txBWTarget;
	sdrOut << YAML::Key << "filter-bandwidth-rx";
	sdrOut << YAML::Value << m_rxBWTarget;
	sdrOut << YAML::EndMap;
	yamlFile << sdrOut.c_str();

	// Write device data.
	yamlFile << deviceTitle;
	YAML::Emitter deviceOut;
	deviceOut << YAML::BeginMap;
	deviceOut << YAML::Key << "clock-ref";
	deviceOut << YAML::Value << ref;
	deviceOut << YAML::Key << "channels-tx";
	deviceOut << YAML::Value << tx_channels;
	deviceOut << YAML::Key << "channels-rx";
	deviceOut << YAML::Value << rx_channels;
	deviceOut << YAML::Key << "antenna-tx";
	deviceOut << YAML::Value << tx_ant;
	deviceOut << YAML::Key << "antenna-rx";
	deviceOut << YAML::Value << rx_ant;
	deviceOut << YAML::EndMap;
	yamlFile << deviceOut.c_str();

	yamlFile << end;
	// Close the yaml file.
	yamlFile.close();

	m_settingsStatusYAML = "Settings saved to YAML file.";
}

void Interface::loadFromYAML() 
{
		// Open the yaml file.
#ifdef _DEBUG
	std::string path = std::filesystem::current_path().string() + "\\Source\\Settings\\Settings.yml";
#else
	std::string path = std::filesystem::current_path().string() + "\\Settings\\Settings.yml";
#endif

	YAML::Node yamlFile = YAML::LoadFile(path);

	// Load file settings.
	m_folderName				= yamlFile["folder"].as<std::string>();
	m_latestFileName			= yamlFile["file-latest"].as<std::string>();
	m_targetFileName			= yamlFile["file-target"].as<std::string>();
	// Load SDR settings.
	m_txSamplingFrequencyTarget	= yamlFile["sample-rate-tx"].as<float>();
	m_rxSamplingFrequencyTarget	= yamlFile["sample-rate-rx"].as<float>();
	m_txFreqTarget				= yamlFile["wave-frequency-tx"].as<double>();
	m_rxFreqTarget				= yamlFile["wave-frequency-rx"].as<double>();
	m_txGainTarget				= yamlFile["gain-tx"].as<double>();
	m_rxGainTarget				= yamlFile["gain-rx"].as<double>();
	m_txBWTarget				= yamlFile["filter-bandwidth-tx"].as<double>();
	m_rxBWTarget				= yamlFile["filter-bandwidth-rx"].as<double>();
	// Load device settings.
	ref							= yamlFile["clock-ref"].as<std::string>();
	tx_channels					= yamlFile["channels-tx"].as<std::string>();
	rx_channels					= yamlFile["channels-rx"].as<std::string>();
	tx_ant						= yamlFile["antenna-tx"].as<std::string>();
	rx_ant						= yamlFile["antenna-rx"].as<std::string>();

	m_settingsStatusYAML = "Settings loaded from YAML file.";
}

// ================================================================================================================================================================================ //
//  EOF.	                                                                                                                                                                        //
// ================================================================================================================================================================================ //