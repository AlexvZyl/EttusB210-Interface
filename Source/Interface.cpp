// ================================================================================================================================================================================ //
//  Includes.																																										//
// ================================================================================================================================================================================ //

#include "Interface.h"
#include "../External/Misc/ConsoleColor.h"

// ================================================================================================================================================================================ //
//	Constructor and Destructor.																																						//
// ================================================================================================================================================================================ //

Interface::Interface()
{
    // Setup default vales.
    m_folderName = "None";
    m_targetFileName = "None";
    m_latestFileName = "None";
    m_autoFileState = "Disabled";
    m_txSamplingFrequencyTarget = 4e6;
    m_rxSamplingFrequencyTarget = 4e6;
    m_txFreqTarget = 900e6;
    m_rxFreqTarget = 900e6;
    m_txGainTarget = 89;
    m_rxGainTarget = 70;
    m_status = "Idle.";
    m_txBWTarget = 8000000;
    m_rxBWTarget = 8000000;

    // SDR Defaults.
    tx_rate = m_txSamplingFrequencyTarget;
    rx_rate = m_rxSamplingFrequencyTarget;
    tx_freq = m_txFreqTarget;
    rx_freq = m_rxFreqTarget;
    tx_gain = m_txGainTarget;
    rx_gain = m_rxGainTarget;
    tx_bw = m_txBWTarget;
    rx_bw = m_rxBWTarget;
    tx_args = "";
    rx_args = "";
    ref = "internal";
    tx_channels = "0";
    rx_channels = "0";
    tx_ant = "";
    rx_ant = "";
    tx_int_n = "";
    rx_int_n = "";
    wave_freq = 0;
    wave_type = "CONST";
    type = "float";
    settling = 0.2;
    spb = 0;
    ampl = 0.3;
    otw = "sc16";
    total_num_samps = 2 * tx_rate;

    loadFromYAML();
}

Interface::~Interface()
{
}

// ================================================================================================================================================================================ //
//	Application Functions.  																																						//
// ================================================================================================================================================================================ //

void Interface::systemInfo() 
{
    std::cout << blue << "[COPYRIGHT]:" << white << " C.A van Zyl, calexandervanzyl@gmail.com, +27 76 888 7559.\n\n" << 
        red <<                 "----------------------------------" << blue << "\t[APP STATUS]: " << white << m_status << "\n" <<
        red << "|" << yellow << "              ¶¶¶               " << red << "|" << blue << "\t[SDR STATUS]: " << white << m_sdrInfo << "\n" <<
        red << "|" << yellow << "             ¶¶ ¶¶¶¶            " << red << "|" << blue << "\t[SETTINGS SDR]: " << white << m_settingsStatusSDR << '\n' <<
        red << "|" << yellow << "            ¶¶    ¶¶¶           " << red << "|" << blue << "\t[SETTINGS YAML]: " << white << m_settingsStatusYAML << '\n' << 
        red << "|" << yellow << "           ¶¶¶      ¶¶          " << red << "|" << blue << "\n" <<
        red << "|" << yellow << "           ¶¶¶       ¶¶         " << red << "|" << blue << "\t[FOLDER]: " << white << "'" << m_folderName << "'\n" <<
        red << "|" << yellow << "          ¶¶¶¶        ¶¶        " << red << "|" << blue << "\t[LATEST FILE]: " << white << "'" << m_latestFileName << "'\n" <<
        red << "|" << yellow << "          ¶ ¶¶         ¶¶       " << red << "|" << blue << "\t[TARGET FILE]: " << white << "'" << m_targetFileName << "'\n" <<
        red << "|" << yellow << "          ¶  ¶¶         ¶¶    ¶¶" << red << "|" << blue << "\t[AUTO FILING]: " << white << m_autoFileState << "\n" <<
        red << "|" << yellow << "          ¶  ¶¶          ¶¶¶¶¶¶¶" << red << "|" << blue << "\n" <<
        red << "|" << yellow << "         ¶¶  ¶¶¶      ¶¶¶¶¶¶   ¶" << red << "|" << blue << "\t[TX SMAMPLING]--[TARGET]: " << white << m_txSamplingFrequencyTarget / (1e6) << " MHz\n" <<
        red << "|" << yellow << "         ¶¶   ¶¶  ¶¶¶¶¶¶  ¶¶    " << red << "|" << blue << "\t\t\t[" << green << "ACTUAL" << blue << "]: " << white << m_txSamplingFrequencyActual / (1e6) << " MHz\n" <<
        red << "|" << yellow << "      ¶¶  ¶¶   ¶¶          ¶¶   " << red << "|" << blue << "\t[RX SMAMPLING]--[TARGET]: " << white << m_rxSamplingFrequencyTarget / (1e6) << " MHz\n" <<
        red << "|" << yellow << "       ¶¶ ¶    ¶¶¶¶        ¶¶   " << red << "|" << blue << "\t\t\t[" << green << "ACTUAL" << blue << "]: " << white << m_rxSamplingFrequencyActual / (1e6) << " MHz\n" <<
        red << "|" << yellow << "     ¶¶    ¶¶   ¶¶          ¶¶  " << red << "|" << blue << "\t[TX FREQUENCY]--[TARGET]: " << white << m_txFreqTarget / (1e6) << " MHz\n" <<
        red << "|" << yellow << "   ¶¶       ¶¶   ¶¶         ¶¶  " << red << "|" << blue << "\t\t\t[" << green << "ACTUAL" << blue << "]: " << white << m_txFreqActual / (1e6) << " MHz\n" <<
        red << "|" << yellow << "   ¶¶¶¶¶¶¶¶¶¶¶¶¶  ¶¶         ¶  " << red << "|" << blue << "\t[RX FREQUENCY]--[TARGET]: " << white << m_rxFreqTarget / (1e6) << " MHz\n" <<
        red << "|" << yellow << " ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶ ¶¶        ¶¶ " << red << "|" << blue << "\t\t\t[" << green << "ACTUAL" << blue << "]: " << white << m_rxFreqActual / (1e6) << " MHz\n" <<
        red << "|" << yellow << "¶¶  ¶¶¶¶¶¶    ¶¶¶¶¶¶¶¶¶      ¶¶ " << red << "|" << blue << "\t[TX GAIN]-------[TARGET]: " << white << m_txGainTarget << " dB\n" <<
        red << "|" << yellow << "¶¶¶¶¶   ¶      ¶   ¶¶¶¶¶     ¶¶ " << red << "|" << blue << "\t\t\t[" << green << "ACTUAL" << blue << "]: " << white << m_txGainActual << " dB\n" <<
        red << "|" << yellow << "        ¶¶¶¶¶¶¶¶      ¶¶¶¶¶ ¶¶  " << red << "|" << blue << "\t[RX GAIN]-------[TARGET]: " << white << m_rxGainTarget << " dB\n" <<
        red << "|" << yellow << "      ¶¶¶¶¶¶¶¶¶¶¶        ¶¶¶¶   " << red << "|" << blue << "\t\t\t[" << green << "ACTUAL" << blue << "]: " << white << m_rxGainActual << " dB\n" <<
        red << "|" << yellow << "      ¶¶¶¶¶¶¶¶¶¶¶¶              " << red << "|" << blue << "\t[TX BW]---------[TARGET]: " << white << m_txBWTarget / (1e6) << " MHz\n" <<
        red << "|" << yellow << "      ¶  ¶¶ ¶¶¶¶¶¶              " << red << "|" << blue << "\t\t\t[" << green << "ACTUAL" << blue << "]: " << white << m_txBWActual / (1e6) << " MHz\n" <<
        red << "|" << yellow << "     ¶¶      ¶   ¶              " << red << "|" << blue << "\t[RX BW]---------[TARGET]: " << white << m_rxBWTarget / (1e6) << " MHz\n" <<
        red << "|" << yellow << "     ¶¶     ¶¶   ¶              " << red << "|" << blue << "\t\t\t[" << green << "ACTUAL" << blue << "]: " << white << m_rxBWActual / (1e6) << " MHz\n" <<
        red << "|" << yellow << "     ¶      ¶¶   ¶              " << red << "|" << blue << "\n" <<
        red << "|" << yellow << "    ¶¶      ¶¶   ¶¶             " << red << "|" << blue << "\t[CLOCK REF]: " << white << ref << "\n" <<
        red << "|" << yellow << "    ¶¶      ¶¶   ¶¶             " << red << "|" << blue << "\t[TX CHANNELS]: " << white << tx_channels << "\n" <<
        red << "|" << yellow << "   ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶             " << red << "|" << blue << "\t[RX CHANNELS]: " << white << rx_channels << "\n" <<
        red << "|" << yellow << "  ¶¶¶¶¶¶¶¶¶ ¶¶¶¶¶¶¶¶            " << red << "|" << blue << "\t[TX ANTENNA]: " << white << tx_ant << "\n" <<
        red << "|" << yellow << "  ¶¶        ¶¶¶    ¶¶           " << red << "|" << blue << "\t[RX ANTENNA]: " << white << rx_ant << "\n" <<
        red << "|" << yellow << "   ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶            " << red << "|" << "\n" <<
        red <<                "----------------------------------\n" << white;

    // Update the terminal line.
    m_currentTerminalLine = 38;
}

void Interface::readInput(unsigned int* answer)
{
    std::cout << green << "\t[INPUT]: " << white;
    std::string answerString = "";
    std::cin >> answerString;
    // Make sure the user enters a number and not a string.
    try { *answer =  std::stoi(answerString); }
    catch (const std::exception& e) { *answer = -1; }
}

void Interface::readInput(double* answer)
{
    std::cout << green << "\t[INPUT]: " << white;
    std::string answerString = "";
    std::cin >> answerString;
    // Make sure the user enters a number and not a string.
    try { *answer = std::stod(answerString); }
    catch (const std::exception& e) { *answer = -1; }
}

void Interface::readInput(std::string* input)
{
    std::cout << green << "\t[INPUT]: " << white;
    std::cin.ignore();
    std::getline(std::cin, *input);
}

void Interface::menuListBar(unsigned level) 
{
    if (level == 0) 
    {
        if (m_currentTerminalLine >= m_maxTerminalLine)
        {
            std::cout << green << "\t |\n";
        }
        else {
            for (int i = m_currentTerminalLine; i < m_maxTerminalLine; i++)
            {
                std::cout << green << "\t |\n";
            }
        }
    }
    else if (level == 1) 
    {
        if (m_currentTerminalLine >= m_maxTerminalLine)
        {
            std::cout << green << "\t   |\n";
        }
        else {
            for (int i = m_currentTerminalLine; i < m_maxTerminalLine; i++)
            {
                std::cout << green << "\t   |\n";
            }
        }
    }
    m_currentTerminalLine = m_maxTerminalLine;
}

void Interface::printError(unsigned int answer) 
{
    if (answer == -1) { std::cout << red << "\t[ERROR]: " << white << "Invalid input.\n"; }
    else { std::cout << red << "\t[ERROR]: " << white << "'" << answer << "' is not in the list of options.\n"; }
}

void Interface::mainMenu()
{
    m_status = "Idle.";
    clear();
    systemInfo();
    std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
    std::cout << green << "\t[1]: " << white << "Connect/Update SDR.\n";
    std::cout << green << "\t[2]: " << white << "Start transmission.\n";
    std::cout << green << "\t[3]: " << white << "Settings.\n";
    std::cout << green << "\t[4]: " << white << "Set folder.\n";
    std::cout << green << "\t[5]: " << white << "Set file.\n";
    std::cout << green << "\t[6]: " << white << "Toggle auto filing.\n";
    std::cout << green << "\t[7]: " << white << "Save settings.\n";
    std::cout << green << "\t[0]: " << white << "Quit.\n";
    m_currentTerminalLine += 9;
    menuListBar(0);
    unsigned int answer;
    readInput(&answer);
    // Error handling.
    while (answer < 0 || answer > 7 || (answer == 2 && m_sdrInfo == "SDR has not been connected.") )
    {
        // Make sure the SDR has been connected.
        if (answer == 2 && m_sdrInfo == "SDR has not been connected.")
        {
            clear();
            systemInfo();
            std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
            std::cout << green << "\t[1]: " << white << "Connect/Update SDR.\n";
            std::cout << green << "\t[2]: " << white << "Start transmission.\n";
            std::cout << green << "\t[3]: " << white << "Settings.\n";
            std::cout << green << "\t[4]: " << white << "Set folder.\n";
            std::cout << green << "\t[5]: " << white << "Set file.\n";
            std::cout << green << "\t[6]: " << white << "Toggle auto filing.\n";
            std::cout << green << "\t[7]: " << white << "Save settings.\n";
            std::cout << green << "\t[0]: " << white << "Quit.\n";
            m_currentTerminalLine += 10;
            menuListBar(0);
            std::cout << red << "\t[ERROR]: " << white << "SDR has not been connected.\n";
            readInput(&answer);
        }
        else
        {
            clear();
            systemInfo();
            std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
            std::cout << green << "\t[1]: " << white << "Connect/Update SDR.\n";
            std::cout << green << "\t[2]: " << white << "Start transmission.\n";
            std::cout << green << "\t[3]: " << white << "Settings.\n";
            std::cout << green << "\t[4]: " << white << "Set folder.\n";
            std::cout << green << "\t[5]: " << white << "Set file.\n";
            std::cout << green << "\t[6]: " << white << "Toggle auto filing.\n";
            std::cout << green << "\t[7]: " << white << "Save settings.\n";
            std::cout << green << "\t[0]: " << white << "Quit.\n";
            m_currentTerminalLine += 10;
            menuListBar(0);
            printError(answer);
            readInput(&answer);
        }
    }
    // Handle the cases for the options.
    switch (answer)
    {
    case 1:
        setupSDR();
        break;
    case 2:
        startTransmission();
        break;
    case 3:
        settingsMenu();
        break;
    case 4:
        setFolder();
        break;
    case 5:
        setFile();
        break;
    case 6:
        toggleAutoFiling();
        break;
    case 7:
        saveSettings();
        break;
    case 0:
        quit();
        break;
    }
}

void Interface::clear()
{
    system("cls");
}

void Interface::quit()
{
    clear();
    systemInfo();
    std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
    std::cout << green << "\t   |-> " << yellow << "Quit.\n";
    std::cout << green << "\t  [i]: " << white << "Are you sure you want to quit?\n";
    std::cout << green << "\t  [1]: " << white << "Yes.\n";
    std::cout << green << "\t  [0]: " << white << "No.\n";
    m_currentTerminalLine += 5;
    menuListBar(1);
    unsigned int answer;
    readInput(&answer);
    while (answer < 0 || answer > 1)
    {
        clear();
        systemInfo();
        std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
        std::cout << green << "\t   |-> " << yellow << "Quit.\n";
        std::cout << green << "\t  [i]: " << white << "Are you sure you want to quit?\n";
        std::cout << green << "\t  [1]: " << white << "Yes.\n";
        std::cout << green << "\t  [0]: " << white << "No.\n";
        m_currentTerminalLine += 6;
        menuListBar(1);
        printError(answer);
        readInput(&answer);
    }
    if (answer == 1) { shouldClose = true; }
    clear();
    systemInfo();
    std::cout << "\n";
}

void Interface::displayDeviceInformation() 
{
    std::cout << boost::format("Using TX Device: %s") % tx_usrp->get_pp_string() << std::endl;
    std::cout << boost::format("Using RX Device: %s") % rx_usrp->get_pp_string() << std::endl;
}

// ================================================================================================================================================================================ //
//  EOF.																																											//
// ================================================================================================================================================================================ //