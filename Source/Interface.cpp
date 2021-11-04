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
    m_currentFileName = "None";
    m_latestFileName = "None";
    m_autoFiling = false;
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
    type = "short";
    settling = 0.2;
    spb = 0;
    ampl = 0.3;
    otw = "sc16";
}

Interface::~Interface()
{
    delete buff;
    delete wave_table;
}

// ================================================================================================================================================================================ //
//	Application Functions.  																																						//
// ================================================================================================================================================================================ //

void Interface::systemInfo() 
{
    std::cout << blue << "[COPYRIGHT]:" << white << " C.A van Zyl, calexandervanzyl@gmail.com, +27 76 888 7559.\n\n" << 
        red <<                 "----------------------------------\n" <<
        red << "|" << yellow << "              ¶¶¶               " << red << "|" << blue << "\t[APP STATUS]: " << white << m_status << "\n" <<
        red << "|" << yellow << "             ¶¶ ¶¶¶¶            " << red << "|" << blue << "\t[SDR STATUS]: " << white << m_sdrInfo << "\n" <<
        red << "|" << yellow << "            ¶¶    ¶¶¶           " << red << "|" << blue << "\t[SETTINGS STATUS]: " << white << m_settingsStatus << '\n' <<
        red << "|" << yellow << "           ¶¶¶      ¶¶          " << red << "|" << blue << "\n" <<
        red << "|" << yellow << "           ¶¶¶       ¶¶         " << red << "|" << blue << "\t[FOLDER]: " << white << "'" << m_folderName << "'\n" <<
        red << "|" << yellow << "          ¶¶¶¶        ¶¶        " << red << "|" << blue << "\t[LATEST FILE]: " << white << "'" << m_latestFileName << "'\n" <<
        red << "|" << yellow << "          ¶ ¶¶         ¶¶       " << red << "|" << blue << "\t[TARGET FILE]: " << white << "'" << m_currentFileName << "'\n" <<
        red << "|" << yellow << "          ¶  ¶¶         ¶¶    ¶¶" << red << "|" << blue << "\t[AUTO FILING]: " << white << m_autoFiling << "\n" <<
        red << "|" << yellow << "          ¶  ¶¶          ¶¶¶¶¶¶¶" << red << "|" << blue << "\n" <<
        red << "|" << yellow << "         ¶¶  ¶¶¶      ¶¶¶¶¶¶   ¶" << red << "|" << blue << "\t[TX SMAMPLING TARGET]: " << white << m_txSamplingFrequencyTarget / (1e6) << " MHz\n" <<
        red << "|" << yellow << "         ¶¶   ¶¶  ¶¶¶¶¶¶  ¶¶    " << red << "|" << blue << "\t[TX SMAMPLING " << green << "ACTUAL" << blue << "]: " << white << m_txSamplingFrequencyActual / (1e6) << " MHz\n" <<
        red << "|" << yellow << "      ¶¶  ¶¶   ¶¶          ¶¶   " << red << "|" << blue << "\t[RX SMAMPLING TARGET]: " << white << m_rxSamplingFrequencyTarget / (1e6) << " MHz\n" <<
        red << "|" << yellow << "       ¶¶ ¶    ¶¶¶¶        ¶¶   " << red << "|" << blue << "\t[RX SMAMPLING " << green << "ACTUAL" << blue << "]: " << white << m_rxSamplingFrequencyActual / (1e6) << " MHz\n" <<
        red << "|" << yellow << "     ¶¶    ¶¶   ¶¶          ¶¶  " << red << "|" << blue << "\t[TX FREQUENCY TARGET]: " << white << m_txFreqTarget / (1e6) << " MHz\n" <<
        red << "|" << yellow << "   ¶¶       ¶¶   ¶¶         ¶¶  " << red << "|" << blue << "\t[TX FREQUENCY " << green << "ACTUAL" << blue << "]: " << white << m_txFreqActual / (1e6) << " MHz\n" <<
        red << "|" << yellow << "   ¶¶¶¶¶¶¶¶¶¶¶¶¶  ¶¶         ¶  " << red << "|" << blue << "\t[RX FREQUENCY TARGET]: " << white << m_rxFreqTarget / (1e6) << " MHz\n" <<
        red << "|" << yellow << " ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶ ¶¶        ¶¶ " << red << "|" << blue << "\t[RX FREQUENCY " << green << "ACTUAL" << blue << "]: " << white << m_rxFreqActual / (1e6) << " MHz\n" <<
        red << "|" << yellow << "¶¶  ¶¶¶¶¶¶    ¶¶¶¶¶¶¶¶¶      ¶¶ " << red << "|" << blue << "\t[TX GAIN TARGET]: " << white << m_txGainTarget << " dB\n" <<
        red << "|" << yellow << "¶¶¶¶¶   ¶      ¶   ¶¶¶¶¶     ¶¶ " << red << "|" << blue << "\t[TX GAIN " << green << "ACTUAL" << blue << "]: " << white << m_txGainActual << " dB\n" <<
        red << "|" << yellow << "        ¶¶¶¶¶¶¶¶      ¶¶¶¶¶ ¶¶  " << red << "|" << blue << "\t[RX GAIN TARGET]: " << white << m_rxGainTarget << " dB\n" <<
        red << "|" << yellow << "      ¶¶¶¶¶¶¶¶¶¶¶        ¶¶¶¶   " << red << "|" << blue << "\t[RX GAIN " << green << "ACTUAL" << blue << "]: " << white << m_rxGainActual << " dB\n" <<
        red << "|" << yellow << "      ¶¶¶¶¶¶¶¶¶¶¶¶              " << red << "|" << blue << "\t[TX BW TARGET]: " << white << m_txBWTarget / (1e6) << " MHz\n" <<
        red << "|" << yellow << "      ¶  ¶¶ ¶¶¶¶¶¶              " << red << "|" << blue << "\t[TX BW " << green << "ACTUAL" << blue << "]: " << white << m_txBWActual / (1e6) << " MHz\n" <<
        red << "|" << yellow << "     ¶¶      ¶   ¶              " << red << "|" << blue << "\t[RX BW TARGET]: " << white << m_rxBWTarget / (1e6) << " MHz\n" <<
        red << "|" << yellow << "     ¶¶     ¶¶   ¶              " << red << "|" << blue << "\t[RX BW " << green << "ACTUAL" << blue << "]: " << white << m_rxBWActual / (1e6) << " MHz\n" <<
        red << "|" << yellow << "     ¶      ¶¶   ¶              " << red << "|" << blue << "\n" <<
        red << "|" << yellow << "    ¶¶      ¶¶   ¶¶             " << red << "|" << blue << "\t[CLOCK REF]: " << white << ref << "\n" <<
        red << "|" << yellow << "    ¶¶      ¶¶   ¶¶             " << red << "|" << blue << "\t[TX CHANNELS]: " << white << tx_channels << "\n" <<
        red << "|" << yellow << "   ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶             " << red << "|" << blue << "\t[RX CHANNELS]: " << white << rx_channels << "\n" <<
        red << "|" << yellow << "  ¶¶¶¶¶¶¶¶¶ ¶¶¶¶¶¶¶¶            " << red << "|" << blue << "\t[TX ANTENNA]: " << white << tx_ant << "\n" <<
        red << "|" << yellow << "  ¶¶        ¶¶¶    ¶¶           " << red << "|" << blue << "\t[RX ANTENNA]: " << white << rx_ant << "\n" <<
        red << "|" << yellow << "   ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶            " << red << "|" << "\n" <<
        red <<                "----------------------------------\n" << white;
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
    std::cout << green << "\t[0]: " << white << "Quit.\n";
    std::cout << green << "\t[INPUT]: " << white;
    int answer=0;
    std::cin >> answer;
    while (answer < 0 || answer > 6) 
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
        std::cout << green << "\t[0]: " << white << "Quit.\n";
        std::cout << red   << "\t[ERROR]: " << white << "'" << answer << "' is not a valid option.\n";
        std::cout << green << "\t[INPUT]: " << white;
        std::cin >> answer;
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
    std::cout << green << "\t   |\n";
    std::cout << green << "\t   |\n";
    std::cout << green << "\t   |\n";
    std::cout << green << "\t[INPUT]: " << white;
    int answer;
    std::cin >> answer;
    while (answer < 0 || answer > 1)
    {
        clear();
        systemInfo();
        std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
        std::cout << green << "\t   |-> " << yellow << "Quit.\n";
        std::cout << green << "\t  [i]: " << white << "Are you sure you want to quit?\n";
        std::cout << green << "\t  [1]: " << white << "Yes.\n";
        std::cout << green << "\t  [0]: " << white << "No.\n";
        std::cout << green << "\t   |\n";
        std::cout << green << "\t   |\n";
        std::cout << red << "\t[ERROR]: " << white << "'" << answer << "' is not a valid option.\n";
        std::cout << green << "\t[INPUT]: " << white;
        std::cin >> answer;
    }
    if (answer == 1) { shouldClose = true; }
    clear();
    systemInfo();
    std::cout << "\n";
}

// ================================================================================================================================================================================ //
//  EOF.																																											//
// ================================================================================================================================================================================ //