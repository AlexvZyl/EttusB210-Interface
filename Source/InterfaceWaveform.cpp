// ================================================================================================================================================================================ //
//  Includes.                                                                                                                                                                       //
// ================================================================================================================================================================================ //

#include "Interface.h"
#include "Utils/Waveforms.h"

// ================================================================================================================================================================================ //
//  Menu.                                                                                                                                                                           //
// ================================================================================================================================================================================ //

void Interface::waveFormMenu() 
{
	clear();
	systemInfo();
	std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
	std::cout << green << "\t   |-> " << yellow << "Waveform.\n";
	std::cout << green << "\t  [1]: " << white << "Wave type.\n";
	std::cout << green << "\t  [2]: " << white << "Radar max range.\n";
	std::cout << green << "\t  [3]: " << white << "Radar dead zone range.\n";
	std::cout << green << "\t  [4]: " << white << "Radar transmission time.\n";
	std::cout << green << "\t  [5]: " << white << "Window function.\n";
	std::cout << green << "\t  [0]: " << white << "Return.\n";
	m_currentTerminalLine += 8;
	menuListBar(1);
	unsigned int answer;
	readInput(&answer);

	// Handle errors.
	while (answer < 0 || answer > 4)
	{
		clear();
		systemInfo();
		std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
		std::cout << green << "\t   |-> " << yellow << "Waveform.\n";
		std::cout << green << "\t  [1]: " << white << "Wave type.\n";
		std::cout << green << "\t  [2]: " << white << "Radar max range.\n";
		std::cout << green << "\t  [3]: " << white << "Radar dead zone range.\n";
		std::cout << green << "\t  [4]: " << white << "Radar transmission time.\n";
		std::cout << green << "\t  [5]: " << white << "Window function.\n";
		std::cout << green << "\t  [0]: " << white << "Return.\n";
		m_currentTerminalLine += 9;
		menuListBar(1);
		printError(answer);
		readInput(&answer);
	}

	switch (answer)
	{
	case 1:
		setWaveType();
		break;
	case 2:
		setMaxRange();
		break;
	case 3:
		setDeadzoneRange();
		break;
	case 4:
		setTxTime();
		break;
	case 5:
		setPulseWaveform();
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

void Interface::setPulseWaveform()
{
	clear();
	systemInfo();
	std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
	std::cout << green << "\t   |-> " << yellow << "Waveform.\n";
	std::cout << green << "\t   |-> " << yellow << "Window function.\n";
	std::cout << green << "\t  [i]: " << white << "Applied to the pulse to reduce aliasing.\n";
	std::cout << green << "\t  [i]: " << white << "Select the waveform:\n";
	std::cout << green << "\t  [1]: " << white << "None.\n";
	std::cout << green << "\t  [2]: " << white << "Blackman.\n";
	std::cout << green << "\t  [3]: " << white << "Hamming.\n";
	std::cout << green << "\t  [0]: " << white << "Return.\n";
	m_currentTerminalLine += 9;
	menuListBar(1);
	double answer;
	readInput(&answer);
	while (answer > 3 || answer < 0)
	{
		clear();
		systemInfo();
		std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
		std::cout << green << "\t   |-> " << yellow << "Waveform.\n";
		std::cout << green << "\t   |-> " << yellow << "Window function.\n";
		std::cout << green << "\t  [i]: " << white << "Applied to the pulse to reduce aliasing.\n";
		std::cout << green << "\t  [i]: " << white << "Select the waveform:\n";
		std::cout << green << "\t  [1]: " << white << "None.\n";
		std::cout << green << "\t  [2]: " << white << "Blackman.\n";
		std::cout << green << "\t  [3]: " << white << "Hamming.\n";
		std::cout << green << "\t  [0]: " << white << "Return.\n";
		m_currentTerminalLine += 10;
		menuListBar(1);
		printError(answer);
		readInput(&answer);
	}
	m_settingsStatusSDR = "Changed settings not uploaded to SDR.";
	m_settingsStatusYAML = "Changed settings not saved to YAML file.";
	if (answer == 1) m_windowFunction = "None";
	else if (answer == 2) m_windowFunction = "Blackman";
	else if (answer == 3) m_windowFunction = "Hamming";
	waveFormMenu();
}

void Interface::calculatePulsesPerTX()
{
	// Now calculate the amount of pulses that are transmitted with each transmission cycle.
	m_pulsesPerTransmission = std::floor((m_txDurationActual * m_txSamplingFrequencyTarget) / m_waveLengthSamples);
}

void Interface::setWaveType() 
{
	clear();
	systemInfo();
	std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
	std::cout << green << "\t   |-> " << yellow << "Waveform.\n";
	std::cout << green << "\t   |-> " << yellow << "Wave type.\n";
	std::cout << green << "\t  [i]: " << white << "The waveform that is transmitted.\n";
	std::cout << green << "\t  [i]: " << white << "Select the waveform:\n";
	std::cout << green << "\t  [1]: " << white << "Linear Frequency Chirp.\n";
	std::cout << green << "\t  [2]: " << white << "Non-Linear Frequency Chirp.\n";
	std::cout << green << "\t  [3]: " << white << "Constant sine.\n";
	std::cout << green << "\t  [0]: " << white << "Return.\n";
	m_currentTerminalLine += 9;
	menuListBar(1);
	double answer;
	readInput(&answer);
	while (answer > 3 || answer < 0)
	{
		clear();
		systemInfo();
		std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
		std::cout << green << "\t   |-> " << yellow << "Waveform.\n";
		std::cout << green << "\t   |-> " << yellow << "Wave type.\n";
		std::cout << green << "\t  [i]: " << white << "The waveform that is transmitted.\n";
		std::cout << green << "\t  [i]: " << white << "Select the waveform:\n";
		std::cout << green << "\t  [1]: " << white << "Linear Frequency Chirp.\n";
		std::cout << green << "\t  [2]: " << white << "Non-Linear Frequency Chirp.\n";
		std::cout << green << "\t  [3]: " << white << "Constant sine.\n";
		std::cout << green << "\t  [0]: " << white << "Return.\n";
		m_currentTerminalLine += 10;
		menuListBar(1);
		printError(answer);
		readInput(&answer);
	}
	m_settingsStatusSDR = "Changed settings not uploaded to SDR.";
	m_settingsStatusYAML = "Changed settings not saved to YAML file.";
	if (answer == 1) m_waveType = "Linear Frequency Chirp";
	else if (answer == 2) m_waveType = "Non-Linear Frequency Chirp";
	else if (answer == 3) m_waveType = "Constant sine";
	else if (answer == 4) m_waveType = "Hamming";
	waveFormMenu();
}

void Interface::generateTransmissionPusle() 
{
	// Calculate wave samples.
	m_waveLengthSamples = std::round((m_maxRange * 2 / c) * m_txSamplingFrequencyActual);
	m_maxRangeActual = ((m_waveLengthSamples / 2) / m_txSamplingFrequencyActual) * c;
	m_pulseLengthSamples = std::round((m_deadzone * 2 / c) * m_txSamplingFrequencyActual);
	// Ensure wave samples is uneven.
	if (m_pulseLengthSamples % 2 == 0) { m_pulseLengthSamples++; }
	m_deadzoneActual = (m_pulseLengthSamples / 2 / m_txSamplingFrequencyActual) * c;
	m_waveAmplitude = 1;
	m_waveBandwidth = m_txSamplingFrequencyActual / 2.1;    // Nyquist.
	// Update total samples.
	total_num_samps = m_txDuration * m_txSamplingFrequencyActual;
	m_txDurationActual = std::floor((total_num_samps / m_waveLengthSamples)) * m_waveLengthSamples / m_txSamplingFrequencyActual;
	total_num_samps = m_txDurationActual * m_txSamplingFrequencyActual;
	// Generate the transmission wave.
	if (m_waveType == "Linear Frequency Chirp") m_transmissionWave = generateLinearChirp(m_pulseLengthSamples, m_waveBandwidth, m_waveAmplitude, m_txSamplingFrequencyActual, m_windowFunction);
	else if (m_waveType == "Non Linear Frequency Chirp") m_transmissionWave = generateNonLinearChirp(m_pulseLengthSamples, m_txSamplingFrequencyActual / 2.5, m_waveAmplitude, m_txSamplingFrequencyActual, m_windowFunction);
	else if (m_waveType == "Constant Sine") m_transmissionWave = generateConstSine(m_pulseLengthSamples, m_txSamplingFrequencyActual / 2.5, m_waveAmplitude, m_txSamplingFrequencyActual, m_windowFunction);
	else { std::cout << red << "[ERROR]: " << white << "Wave type '" << m_waveType << "' not supported.\n"; hold(); }
	std::vector<std::complex<float>> zeros(m_waveLengthSamples - m_pulseLengthSamples, 0);
	m_transmissionWave.insert(m_transmissionWave.end(), zeros.begin(), zeros.end());
}

// ================================================================================================================================================================================ //
//  EOF.	                                                                                                                                                                        //
// ================================================================================================================================================================================ //
