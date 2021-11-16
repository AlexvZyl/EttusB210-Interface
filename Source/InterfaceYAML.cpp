// ================================================================================================================================================================================ //
//  Includes.																																										//
// ================================================================================================================================================================================ //

#include "Interface.h"
#include "../External/YAML-CPP/Includes/yaml-cpp/yaml.h"
#include <filesystem>
#include <Windows.h>
HMODULE getCurrentModule();

// ================================================================================================================================================================================ // 
// Loading  & saving.																																										//
// ================================================================================================================================================================================ //

void Interface::saveToYAML()
{
    // Find the path to the exe.
    TCHAR pathWindows[100];
    GetModuleFileNameA(getCurrentModule(), pathWindows, 100);
    std::string path = pathWindows;
    std::string toErase = "EttusB210-Interface.exe";
    size_t pos = path.find(toErase);
    path.erase(pos, toErase.length());
    path = path + "Settings\\Settings.yml";

    // Open the yaml file.
    std::ofstream yamlFile;
    yamlFile.open(path);

    // Define titles.
    std::string header = "# ================================================= # \n"
        "#  Settings of the SDR interface.                   # \n"
        "#  Allows the saving of sessions for later use.     # \n"
        "# ================================================= # \n";
    std::string filingTitle = "\n#  Filing settings.\n";
    std::string sdrTitle = "\n\n#  SDR settings.\n";
    std::string deviceTitle = "\n\n#  Device settings.\n";
    std::string end = "\n\n# ================================================= #";

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
    filingOut << YAML::Key << "auto-filing";
    filingOut << YAML::Value << m_autoFileState;
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
    // Find the path to the exe.
    TCHAR pathWindows[100];
    GetModuleFileNameA(getCurrentModule(), pathWindows, 100);
    std::string path = pathWindows;
    std::string toErase = "EttusB210-Interface.exe";
    size_t pos = path.find(toErase);
    path.erase(pos, toErase.length());
    path = path + "Settings\\Settings.yml";

    // Load the YAML file.
    YAML::Node yamlFile = YAML::LoadFile(path);

    // Load file settings.
    m_folderName = yamlFile["folder"].as<std::string>();
    m_latestFileName = yamlFile["file-latest"].as<std::string>();
    m_targetFileName = yamlFile["file-target"].as<std::string>();
    m_autoFileState = yamlFile["auto-filing"].as<std::string>();
    // Load SDR settings.
    m_txSamplingFrequencyTarget = yamlFile["sample-rate-tx"].as<float>();
    m_rxSamplingFrequencyTarget = yamlFile["sample-rate-rx"].as<float>();
    m_txFreqTarget = yamlFile["wave-frequency-tx"].as<double>();
    m_rxFreqTarget = yamlFile["wave-frequency-rx"].as<double>();
    m_txGainTarget = yamlFile["gain-tx"].as<double>();
    m_rxGainTarget = yamlFile["gain-rx"].as<double>();
    m_txBWTarget = yamlFile["filter-bandwidth-tx"].as<double>();
    m_rxBWTarget = yamlFile["filter-bandwidth-rx"].as<double>();
    // Load device settings.
    ref = yamlFile["clock-ref"].as<std::string>();
    tx_channels = yamlFile["channels-tx"].as<std::string>();
    rx_channels = yamlFile["channels-rx"].as<std::string>();
    tx_ant = yamlFile["antenna-tx"].as<std::string>();
    rx_ant = yamlFile["antenna-rx"].as<std::string>();

    m_settingsStatusYAML = "Settings loaded from YAML file.";

    // Check that a folder name was loaded.
    if (m_folderName != "None")
    {
        // Generate a file name if auto filing is enabled.
        if (m_autoFileState == "Enabled") { generateFileName(); }
        else { getLatestFile(); }
    }

    // Update SDR used variables.
    tx_rate = m_txSamplingFrequencyTarget;
    rx_rate = m_rxSamplingFrequencyTarget;
    tx_gain = m_txGainTarget;
    rx_gain = m_rxGainTarget;
    tx_freq = m_txFreqTarget;
    rx_freq = m_rxFreqTarget;
    tx_bw = m_txBWTarget;
    rx_bw = m_rxBWTarget;
}


// Get the current windows module.
HMODULE getCurrentModule()
{
    HMODULE hModule = NULL;
    GetModuleHandleEx(
        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
        (LPCTSTR)getCurrentModule,
        &hModule);
    return hModule;
}

// ================================================================================================================================================================================ // 
// EOF.																																										        //
// ================================================================================================================================================================================ //
