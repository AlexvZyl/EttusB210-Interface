// ================================================================================================================================================================================ //
//  Includes.																																										//
// ================================================================================================================================================================================ //

#include "Interface.h"
#include <filesystem>
namespace fs = std::filesystem;
#include <string>

// ================================================================================================================================================================================ // 
// Functions.																																										//
// ================================================================================================================================================================================ //

void Interface::toggleAutoFiling()
{
    unsigned int answer;
    clear();
    systemInfo();
    // Disable auto filing.
    if (m_autoFileState == "Enabled")
    {
        std::cout << green << "\n\n[APP] [INFO]: " << yellow << "Main Menu:\n";
        std::cout << green << "\t   |-> " << yellow << "Toggle auto filing.";
        std::cout << green << "\n\t  [i]: " << white << "Disable auto filing?\n";
        std::cout << green << "\t  [1]: " << white << "Yes.\n";
        std::cout << green << "\t  [0]: " << white << "No.\n";
        m_currentTerminalLine += 5;
        menuListBar(1);
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
            m_currentTerminalLine += 6;
            menuListBar(1);
            printError(answer);
            readInput(&answer);
        }
        if (answer == 1) 
        { 
            m_autoFileState = "Disabled"; 
            m_settingsStatusYAML = "Changed settings not saved to YAML file.";
            m_targetFileName = "None";
        }
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
        m_currentTerminalLine += 5;
        menuListBar(1);
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
            m_currentTerminalLine += 6;
            menuListBar(1);
            printError(answer);
            readInput(&answer);
        }
        if (answer == 1) 
        { 
            m_autoFileState = "Enabled"; 
            m_settingsStatusYAML = "Changed settings not saved to YAML file.";
            generateFileName();
        }
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
    m_currentTerminalLine += it+3;
    menuListBar(1);
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
        m_currentTerminalLine += it + 3;
        menuListBar(1);
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

    // If auto filing is enabled afile name should be generated automatically 
    // when a folder is selected.
    if (m_autoFileState == "Enabled") { generateFileName(); }
    else { getLatestFile(); m_targetFileName = "None"; }
}

void Interface::setFile() 
{
    // If a folder has not been chosen the files cannot be opened.
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
    // If autofiling is enabled the user should not be able to select a file manually.
    else if (m_autoFileState == "Enabled")
    {
        clear();
        systemInfo();
        std::cout << green << "\n\n[APP] [INFO]: " << white << "Main Menu:\n";
        std::cout << green << "\t   |-> " << yellow << "Current files.\n";
        int it = 1;
        for (const auto& entry : fs::directory_iterator(m_folderName))
        {
            std::cout << green << "\t  [" << it << "] " << white << entry.path() << std::endl;
            it++;
        }
        it--;
        m_currentTerminalLine += it + 4;
        menuListBar(1);
        std::cout << yellow << "\t[WARN]: " << white << "Autofiling is enabled and a file cannot be chosen.\n";
        std::cout << green << "\t[INPUT]: " << white << "Enter any key to continue.";
        std::string answer;
        std::cin.ignore();
        std::cin >> answer;
    }
    // Show all of the available files in the folder and allow the user
    // to select one.
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
        m_currentTerminalLine += it + 3;
        menuListBar(1);
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
            m_currentTerminalLine += it + 4;
            menuListBar(1);
            printError(answer);
            readInput(&answer);
        }

        // Return to the menu.
        if (answer == 0) { return; }
        // Choose the file selected by the user.
        else {
            it = 1;
            // Set the current folder path.
            for (const auto& entry : fs::directory_iterator(m_folderName))
            {
                std::cout << answer << std::endl;
                if (it == answer) { m_targetFileName = entry.path().string(); cleanFileName(m_targetFileName); }
                it++;
            }
        }
    }
}

void Interface::generateFileName() 
{
    if (m_autoFileState == "Enabled") 
    {
        // Vector containing all of the current files.
        std::string currentFile;
        std::vector<int> fileNumbers;
        // Iterate through the files.
        for (const auto& file : fs::directory_iterator(m_folderName)) 
        {   
            // Add the file to the vector.
            currentFile = file.path().string(); 
            // Remove file extension.
            size_t pos = currentFile.find(m_extension);
            currentFile.erase(pos, m_extension.length());
            // Clean the file.
            cleanFileName(currentFile);
            // Remove file prefix.
            pos = currentFile.find(m_dataPrefix);
            currentFile.erase(pos, m_dataPrefix.length());
            // Remove folder prefix.
            currentFile.erase(0, m_folderName.length() - 4);
            // Store file number.
            fileNumbers.push_back(std::stoi(currentFile));
        }
        // Check if folder is not empty.
        if (fileNumbers.size()) 
        {
            // Find the max number.
            int latest = *std::max_element(fileNumbers.begin(), fileNumbers.end());
            std::string folderTemp = m_folderName + "_";
            folderTemp.erase(0, 5);
            m_latestFileName = m_dataPrefix + folderTemp + std::to_string(latest) + m_extension;
            // Set the target file.
            int target = latest + 1;
            m_targetFileName = m_dataPrefix + folderTemp + std::to_string(target) + m_extension;
        }
        // If folder is empty.
        else 
        {
            m_latestFileName = "Empty folder";
            std::string folderTemp = m_folderName + "_";
            folderTemp.erase(0, 5);
            m_targetFileName = m_dataPrefix + folderTemp + "0" + m_extension;
        }
        
    }
    // Do not generate a file name if auto filing is disabled.
    else { std::cout << yellow << "[APP] [WARN]: " << white << "Auto filing is not enabled and a new file name will not be generated."; }
}

void Interface::getLatestFile() 
{
    // Vector containing all of the current files.
    std::string currentFile;
    std::vector<int> fileNumbers;
    
    // Iterate through the files.
    for (const auto& file : fs::directory_iterator(m_folderName))
    {
        // Add the file to the vector.
        currentFile = file.path().string();
        cleanFileName(currentFile);
        // Remove file prefix.
        size_t pos = currentFile.find(m_dataPrefix);
        currentFile.erase(pos, m_dataPrefix.length());
        // Remove folder prefix.
        currentFile.erase(0, m_folderName.length() - 4);
        // Remove file extension.
        pos = currentFile.find(m_extension);
        currentFile.erase(pos, m_extension.length());
        // Extract the file number.
        fileNumbers.push_back(std::stoi(currentFile));
    }
    // Check if folder is not empty.
    if (fileNumbers.size())
    {
        // Find the max number.
        int latest = *std::max_element(fileNumbers.begin(), fileNumbers.end());
        std::string folderTemp = m_folderName + "_";
        folderTemp.erase(0, 5);
        m_latestFileName = m_dataPrefix + folderTemp + std::to_string(latest) + m_extension;
    }
    // If folder is empty.
    else
    { m_latestFileName = "Empty folder"; }
}


void Interface::cleanFileName(std::string& fileName) 
{
    std::cout << fileName << std::endl;
    // Remove the path and only keep the actual name.
    size_t pos = fileName.find(m_folderName);
    fileName.erase(pos, m_folderName.length() + 1);
    std::cout << fileName << std::endl;
}

// ================================================================================================================================================================================ //
//  EOF.																																											//
// ================================================================================================================================================================================ //