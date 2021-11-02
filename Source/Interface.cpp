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
    m_samplingFrequency = 4e6;
    m_waveFrequency = 900e6;
    m_status = "Idle.";

    // SDR Defaults.
    ref = "internal";
    tx_rate = 1e6;
    rx_rate = 1e6;
    tx_freq = 1.1e9;
    rx_freq = 1.1e9;
    tx_channels = "0";
    rx_channels = "0";
}

Interface::~Interface()
{

}

// ================================================================================================================================================================================ //
//	Application Functions.  																																						//
// ================================================================================================================================================================================ //

void Interface::systemInfo() 
{
    std::cout <<
        red <<                 "----------------------------------\n" <<               
        red << "|" << yellow << "              ¶¶¶               "  << red << "|" << blue << "\t[STATUS]: " << white << m_status << "\n" <<
        red << "|" << yellow << "             ¶¶ ¶¶¶¶            "  << red << "|" << blue << "\n" <<
        red << "|" << yellow << "            ¶¶    ¶¶¶           "  << red << "|" << blue << "\t[FOLDER]: " << white << "'" << m_folderName << "'.\n" <<
        red << "|" << yellow << "           ¶¶¶      ¶¶          "  << red << "|" << blue << "\t[LATEST FILE]: " << white << "'" << m_latestFileName << "'.\n" <<
        red << "|" << yellow << "           ¶¶¶       ¶¶         "  << red << "|" << blue << "\t[FILE TARGET]: " << white << "'" << m_currentFileName << "'.\n" <<
        red << "|" << yellow << "          ¶¶¶¶        ¶¶        "  << red << "|" << blue << "\t[AUTO FILING]: " << white << m_autoFiling << ".\n" <<
        red << "|" << yellow << "          ¶ ¶¶         ¶¶       "  << red << "|" << blue << "\n" <<
        red << "|" << yellow << "          ¶  ¶¶         ¶¶    ¶¶"  << red << "|" << blue << "\t[SMAMPLING FREQUENCY]: " << white << m_samplingFrequency << " Hz.\n" <<
        red << "|" << yellow << "          ¶  ¶¶          ¶¶¶¶¶¶¶"  << red << "|" << blue << "\t[TX/RX FREQUENCY]: " << white << m_waveFrequency << " Hz.\n" <<
        red << "|" << yellow << "         ¶¶  ¶¶¶      ¶¶¶¶¶¶   ¶"  << red << "|" << blue << "\t[CLOCK REF]: " << white << ref << ".\n" <<
        red << "|" << yellow << "         ¶¶   ¶¶  ¶¶¶¶¶¶  ¶¶    "  << red << "|" << blue << "\t[TX CHANNELS]: " << white << tx_channels << ".\n" <<
        red << "|" << yellow << "       ¶¶ ¶    ¶¶¶¶        ¶¶   "  << red << "|" << blue << "\t[RX CHANNELS]: " << white <<rx_channels << ".\n" <<
        red << "|" << yellow << "      ¶¶  ¶¶   ¶¶          ¶¶   "  << red << "|" << blue << "\t" << white << "\n" <<
        red << "|" << yellow << "     ¶¶    ¶¶   ¶¶          ¶¶  "  << red << "|" << blue << "\t" << white << "\n" <<
        red << "|" << yellow << "   ¶¶       ¶¶   ¶¶         ¶¶  "  << red << "|" << blue << "\t" << white << "\n" <<
        red << "|" << yellow << "   ¶¶¶¶¶¶¶¶¶¶¶¶¶  ¶¶         ¶  "  << red << "|" << blue << "\t" << white << "\n" <<
        red << "|" << yellow << " ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶ ¶¶        ¶¶ "  << red << "|" << blue << "\t" << white << "\n" <<
        red << "|" << yellow << "¶¶  ¶¶¶¶¶¶    ¶¶¶¶¶¶¶¶¶      ¶¶ "  << red << "|" << blue << "\t" << white << "\n" <<
        red << "|" << yellow << "¶¶¶¶¶   ¶      ¶   ¶¶¶¶¶     ¶¶ "  << red << "|" << blue << "\t" << white << "\n" <<
        red << "|" << yellow << "        ¶¶¶¶¶¶¶¶      ¶¶¶¶¶ ¶¶  "  << red << "|" << blue << "\t" << white << "\n" <<
        red << "|" << yellow << "      ¶¶¶¶¶¶¶¶¶¶¶        ¶¶¶¶   "  << red << "|" << blue << "\t" << white << "\n" <<
        red << "|" << yellow << "      ¶¶¶¶¶¶¶¶¶¶¶¶              "  << red << "|" << blue << "\t" << white << "\n" <<
        red << "|" << yellow << "      ¶  ¶¶ ¶¶¶¶¶¶              "  << red << "|" << blue << "\t" << white << "\n" <<
        red << "|" << yellow << "     ¶¶      ¶   ¶              "  << red << "|" << blue << "\t" << white << "\n" <<
        red << "|" << yellow << "     ¶¶     ¶¶   ¶              "  << red << "|" << blue << "\t" << white << "\n" <<
        red << "|" << yellow << "     ¶      ¶¶   ¶              "  << red << "|" << blue << "\t" << white << "\n" <<
        red << "|" << yellow << "    ¶¶      ¶¶   ¶¶             "  << red << "|" << blue << "\t" << white << "\n" <<
        red << "|" << yellow << "    ¶¶      ¶¶   ¶¶             "  << red << "|" << blue << "\t" << white << "\n" <<
        red << "|" << yellow << "   ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶             "  << red << "|" << blue << "\t" << white << "\n" <<
        red << "|" << yellow << "  ¶¶¶¶¶¶¶¶¶ ¶¶¶¶¶¶¶¶            "  << red << "|" << blue << "\t" << white << "\n" <<
        red << "|" << yellow << "  ¶¶        ¶¶¶    ¶¶           "  << red << "|" << blue << "\t" << white << "\n" <<
        red << "|" << yellow << "   ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶            "  << red << "|" << blue << "\t[COPYRIGHT]:" << white <<" C.A van Zyl, calexandervanzyl@gmail.com, +27 76 888 7559.\n" <<
        red <<                 "----------------------------------\n"<< white;
}

void Interface::mainMenu() 
{
    clear();
    systemInfo();
    std::cout << green << "\n\n[APP] [MENU]: " << white << "Select an option:\n";
    std::cout << green << "\t[1]: " << white << "Setup the SDR.\n";
    std::cout << green << "\t[2]: " << white << "Change folder name.\n";
    std::cout << green << "\t[3]: " << white << "Change file name.\n";
    std::cout << green << "\t[4]: " << white << "Toggle auto file naming.\n";
    std::cout << green << "\t[0]: " << white << "Quit.\n";
    std::cout << green << "\t[INPUT]: " << white;
    int answer=0;
    std::cin >> answer;
    while (answer<0 || answer >4) 
    {
        clear();
        systemInfo();
        std::cout << green << "\n\n[APP] [MENU]: " << white << "Select an option:\n";
        std::cout << green << "\t[1]: " << white << "Setup the SDR.\n";
        std::cout << green << "\t[2]: " << white << "Change folder name.\n";
        std::cout << green << "\t[3]: " << white << "Change file name.\n";
        std::cout << green << "\t[4]: " << white << "Toggle auto file naming.\n";
        std::cout << green << "\t[0]: " << white << "Quit.\n";
        std::cout << red   << "\t[ERROR]: " << white << "Please select a valid option.\n";
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
        setFolder();
        break;
    case 3:
        setFile();
        break;
    case 4:
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


// ================================================================================================================================================================================ //
//	Main Menu Functions.																																							//
// ================================================================================================================================================================================ //

void Interface::setFolder()
{

}

void Interface::setFile()
{

}

void Interface::toggleAutoFiling()
{
    clear();
    systemInfo();
    // Disable auto filing.
    if (m_autoFiling) 
    {
        int answer;
        std::cout << green << "\n\n[APP] [MENU]: " << white << "Disable auto filing?\n";
        std::cout << green << "\t[1]: " << white << "Yes.\n";
        std::cout << green << "\t[0]: " << white << "No.\n";
        std::cout << green << "\t[INPUT]: " << white;
        std::cin >> answer;
        while (answer < 0 || answer > 1) 
        {
            clear();
            systemInfo();
            std::cout << green  << "\n\n[APP] [MENU]: " << white << "Disable auto filing?\n";
            std::cout << green  << "\t[1]: " << white << "Yes.\n";
            std::cout << green  << "\t[0]: " << white << "No.\n";
            std::cout << red    << "\t[ERROR]: " << white << "Please select a valid option.\n";
            std::cout << green  << "\t[INPUT]: " << white;
            std::cin >> answer;
        }
        if (answer == 1) { m_autoFiling = false; }
        else { return; }
    }
    // Enable auto filing.
    else
    {
        int answer;
        std::cout << green << "\n\n[APP] [MENU]: " << white << "Enable auto filing?\n";
        std::cout << green << "\t[1]: " << white << "Yes.\n";
        std::cout << green << "\t[0]: " << white << "No.\n";
        std::cout << green << "\t[INPUT]: " << white;
        std::cin >> answer;
        while (answer < 0 || answer > 1)
        {
            clear();
            systemInfo();
            std::cout << green << "\n\n[APP] [MENU]: " << white << "Enable auto filing?\n";
            std::cout << green << "\t[1]: " << white << "Yes.\n";
            std::cout << green << "\t[0]: " << white << "No.\n";
            std::cout << red << "\t[ERROR]: " << white << "Please select a valid option.\n";
            std::cout << green << "\t[INPUT]: " << white;
            std::cin >> answer;
        }
        if (answer == 1) { m_autoFiling = true; }
        else { return; }
    }
}

void Interface::quit() 
{
    clear();
    systemInfo();
    std::cout << green << "\n\n[APP] [MENU]: " << white << "Are you sure you want to quit?\n";
    std::cout << green << "\t[1]: " << white << "Yes.\n";
    std::cout << green << "\t[0]: " << white << "No.\n";
    std::cout << green << "\t[INPUT]: " << white;
    int answer;
    std::cin >> answer;
    while (answer < 0 || answer > 1)
    {
        clear();
        systemInfo();
        std::cout << green << "\n\n[APP] [MENU]: " << white << "Are you sure you want to quit?\n";
        std::cout << green << "\t[1]: " << white << "Yes.\n";
        std::cout << green << "\t[0]: " << white << "No.\n";
        std::cout << red << "\t[ERROR]: " << white << "Please select a valid option.\n";
        std::cout << green << "\t[INPUT]: " << white;
        std::cin >> answer;
    }
    if (answer == 1) { shouldClose = true; }
    clear();
    systemInfo();
    std::cout << "\n";
}

// ================================================================================================================================================================================ //
//	SDR Interface.																																									//
// ================================================================================================================================================================================ //



// ================================================================================================================================================================================ //
//  EOF.																																											//
// ================================================================================================================================================================================ //