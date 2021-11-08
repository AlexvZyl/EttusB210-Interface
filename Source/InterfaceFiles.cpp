// ================================================================================================================================================================================ //
//  Includes.																																										//
// ================================================================================================================================================================================ //

#include "Interface.h"
#include <filesystem>
namespace fs = std::filesystem;

// ================================================================================================================================================================================ // 
// Functions.																																										//
// ================================================================================================================================================================================ //

void Interface::toggleAutoFiling()
{
    unsigned int answer;
    clear();
    systemInfo();
    // Disable auto filing.
    if (m_autoFiling)
    {
        std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
        std::cout << green << "\t   |-> " << yellow << "Toggle auto filing.";
        std::cout << green << "\n\t  [i]: " << white << "Disable auto filing?\n";
        std::cout << green << "\t  [1]: " << white << "Yes.\n";
        std::cout << green << "\t  [0]: " << white << "No.\n";
        std::cout << green << "\t   |\n";
        std::cout << green << "\t   |\n";
        std::cout << green << "\t   |\n";
        readInput(&answer);
        while (answer < 0 || answer > 1)
        {
            clear();
            systemInfo();
            std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
            std::cout << green << "\t   |-> " << yellow << "Toggle auto filing.";
            std::cout << green << "\n\t  [i]: " << white << "Disable auto filing?\n";
            std::cout << green << "\t  [1]: " << white << "Yes.\n";
            std::cout << green << "\t  [0]: " << white << "No.\n";
            std::cout << green << "\t   |\n";
            std::cout << green << "\t   |\n";
            printError(answer);
            readInput(&answer);
        }
        if (answer == 1) { m_autoFiling = false; }
        else { return; }
    }
    // Enable auto filing.
    else
    {
        std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
        std::cout << green << "\t   |-> " << yellow << "Toggle auto filing.";
        std::cout << green << "\n\t  [i]: " << white << "Enable auto filing?\n";
        std::cout << green << "\t  [1]: " << white << "Yes.\n";
        std::cout << green << "\t  [0]: " << white << "No.\n";
        std::cout << green << "\t   |\n";
        std::cout << green << "\t   |\n";
        std::cout << green << "\t   |\n";
        readInput(&answer);
        while (answer < 0 || answer > 1)
        {
            clear();
            systemInfo();
            std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
            std::cout << green << "\t   |-> " << yellow << "Toggle auto filing.";
            std::cout << green << "\n\t  [i]: " << white << "Enable auto filing?\n";
            std::cout << green << "\t  [1]: " << white << "Yes.\n";
            std::cout << green << "\t  [0]: " << white << "No.\n";
            std::cout << green << "\t   |\n";
            std::cout << green << "\t   |\n";
            printError(answer);
            readInput(&answer);
        }
        if (answer == 1) { m_autoFiling = true; }
        else { return; }
    }
}

void Interface::setFolder()
{
    std::string dataPath = "Data\\";
    clear();
    systemInfo();
    std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
    std::cout << green << "\t   |-> " << yellow << "Set folder.\n";
    int it = 1;
    for (const auto& entry : fs::directory_iterator(dataPath))
    {
        std::cout << green << "\t  [" << it << "] " << white << entry.path() << std::endl;
        it++;
    }
    it--;
    std::cout << green << "\t  [0] " << white << "Return." << std::endl;
    unsigned int answer;
    readInput(&answer);

    // Check if the answer is valid.
    while (answer<0 || answer>it)
    {
        clear();
        systemInfo();
        std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
        std::cout << green << "\t   |-> " << yellow << "Set folder.\n";
        it = 1;
        for (const auto& entry : fs::directory_iterator(dataPath))
        {
            std::cout << green << "\t  [" << it << "] " << white << entry.path() << std::endl;
            it++;
        }
        std::cout << green << "\t  [0] " << white << "Return." << std::endl;
        printError(answer);
        readInput(&answer);
    }

    if (answer == 0) { return; }
    else 
    {
        it = 0;
        // Set the current folder path.
        for (const auto& entry : fs::directory_iterator(dataPath))
        {
            if (it == answer - 1) { m_folderName = entry.path().string(); }
            it++;
        }
    }
}

void Interface::setFile() 
{
    if (m_folderName == "None") 
    {
        clear();
        systemInfo();
        std::cout << green << "\n\n[APP] [INFO]: " << white << "Main Menu:\n";
        std::cout << red << "\t[ERROR]: " << white << "A folder has not been selected.\n";
        std::cout << green << "\t[INPUT]: " << white << "Enter any key to continue.";
        std::string answer;
        std::cin.ignore();
        std::cin >> answer;
    }
    else
    {
        clear();
        systemInfo();
        std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
        std::cout << green << "\t   |-> " << yellow << "Set file.\n";
        int it = 1;
        for (const auto& entry : fs::directory_iterator(m_folderName))
        {
            std::cout << green << "\t  [" << it << "] " << white << entry.path() << std::endl;
            it++;
        }
        it--;
        std::cout << green << "\t  [0] " << white << "Return." << std::endl;
        unsigned int answer;
        readInput(&answer);

        // Check if the answer is valid.
        while (answer < 0 || answer > it)
        {
            clear();
            systemInfo();
            std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
            std::cout << green << "\t   |-> " << yellow << "Set file.\n";
            int it = 1;
            for (const auto& entry : fs::directory_iterator(m_folderName))
            {
                std::cout << green << "\t  [" << it << "] " << white << entry.path() << std::endl;
                it++;
            }
            it--;
            std::cout << green << "\t  [0] " << white << "Return." << std::endl;
            printError(answer);
            readInput(&answer);
        }

        if (answer == 0) { return; }
        else {
            it = 0;
            // Set the current folder path.
            for (const auto& entry : fs::directory_iterator(m_folderName))
            {
                if (it == answer) { m_currentFileName = entry.path().string(); }
                it++;
            }
        }
    }
}

// ================================================================================================================================================================================ //
//  EOF.																																											//
// ================================================================================================================================================================================ //