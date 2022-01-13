// ================================================================================================================================================================================ //
//  Includes.                                                                                                                                                                       //
// ================================================================================================================================================================================ //

#include "Interface.h"				//  Class running the app.
#include "Utils/Waveforms.h"        // Waveform generation.
#include <chrono>                   // For time.             
#include <time.h>                   // "

// ================================================================================================================================================================================ //
//  SDR Setup.                                                                                                                                                                      //
// ================================================================================================================================================================================ //

void Interface::setupSDR() 
{
    // If the SDR has already been setup, we just want to update the settings.
    if (m_sdrInfo != "SDR has not been connected.")
    {
        updateSDR();
        return;
    }

    m_status = "Setting up SDR...";
	clear();
	systemInfo();
    std::cout << green << "\n\n[APP] [INFO]: " << white << "Setting up the SDR...\n";

    // ------------------------------------- //
    //  C R E A T E   U S R P   D E V I C E  //
    // ------------------------------------- //

    // Create a usrp device.
    std::cout << std::endl;
    std::cout << boost::format("Creating the transmit usrp device with: %s...") % tx_args << std::endl;
    tx_usrp = uhd::usrp::multi_usrp::make(tx_args);
    std::cout << std::endl;
    std::cout << boost::format("Creating the receive usrp device with: %s...") % rx_args << std::endl;
    rx_usrp = uhd::usrp::multi_usrp::make(rx_args);
     
    // --------------------- //
    //  S U B D E V I C E S  //
    // --------------------- //

    // Always select the subdevice first, the channel mapping affects the other settings.
    if (tx_subdev.size()) { tx_usrp->set_tx_subdev_spec(tx_subdev); }
    if (rx_subdev.size()) { rx_usrp->set_rx_subdev_spec(rx_subdev); }

    // ----------------- //
    //  Print new frame  //
    clear();
    systemInfo();
    std::cout << green << "\n\n[APP] [INFO]: " << white << "Setting up the SDR...\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "TX & RX USRP devices created.\n\n";
    // ----------------- //

    // ----------------- //
    //  C H A N N E L S  //
    // ----------------- //

    // TX Channels.
    std::vector<std::string> tx_channel_strings;
    boost::split(tx_channel_strings, tx_channels, boost::is_any_of("\"',"));
    for (size_t ch = 0; ch < tx_channel_strings.size(); ch++) 
    {
        size_t chan = std::stoi(tx_channel_strings[ch]);
        if (chan >= tx_usrp->get_tx_num_channels()) { throw std::runtime_error("Invalid TX channel(s) specified."); }
        else { tx_channel_nums.push_back(std::stoi(tx_channel_strings[ch])); }
    }
    // RX Channels.
    std::vector<std::string> rx_channel_strings;
    boost::split(rx_channel_strings, rx_channels, boost::is_any_of("\"',"));
    for (size_t ch = 0; ch < rx_channel_strings.size(); ch++) 
    {
        size_t chan = std::stoi(rx_channel_strings[ch]);
        if (chan >= rx_usrp->get_rx_num_channels()) { throw std::runtime_error("Invalid RX channel(s) specified."); }
        else { rx_channel_nums.push_back(std::stoi(rx_channel_strings[ch])); }
    }

    // ------------------------- //
    //  C L O C K   S O U R C E  //
    // ------------------------- //
    
    // Lock clock sources.
    tx_usrp->set_clock_source(ref);
    rx_usrp->set_clock_source(ref);

    // ---------------- //
    // S A M P L I N G  //
    // ---------------- //

    // Setup TX sampling.
    std::cout << boost::format("Setting TX Rate: %f Msps...") % (tx_rate / 1e6) << std::endl;
    tx_usrp->set_tx_rate(tx_rate);
    std::cout << boost::format("Actual TX Rate: %f Msps...") % (tx_usrp->get_tx_rate() / 1e6) << std::endl << std::endl;
    m_txSamplingFrequencyActual = tx_usrp->get_tx_rate();

    // Setup RX sampling.
    std::cout << boost::format("Setting RX Rate: %f Msps...") % (rx_rate / 1e6) << std::endl;
    rx_usrp->set_rx_rate(rx_rate);
    std::cout << boost::format("Actual RX Rate: %f Msps...") % (rx_usrp->get_rx_rate() / 1e6)<< std::endl << std::endl;
    m_rxSamplingFrequencyActual = rx_usrp->get_rx_rate();

    
    // ----------------- //
    //  Print new frame  //
    clear();
    systemInfo();
    std::cout << green << "\n\n[APP] [INFO]: " << white << "Setting up the SDR...\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "TX & RX USRP devices created.\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "Sampling frequencies set up.\n\n";
    // ----------------- //

    // ------------------------------------- //
    //  S E T U P   T R A N S M I S S I O N  //
    // ------------------------------------- //

    for (size_t ch = 0; ch < tx_channel_nums.size(); ch++) 
    {
        size_t channel = tx_channel_nums[ch];
        if (tx_channel_nums.size() > 1) { std::cout << "Configuring TX Channel " << channel << std::endl; }

        // Set TX frequency.
        std::cout << boost::format("Setting TX Freq: %f MHz...") % (tx_freq / 1e6) << std::endl;
        uhd::tune_request_t tx_tune_request(tx_freq);
        if (tx_int_n.size()) { tx_tune_request.args = uhd::device_addr_t("mode_n=integer"); }
        tx_usrp->set_tx_freq(tx_tune_request, channel);
        std::cout << boost::format("Actual TX Freq: %f MHz...") % (tx_usrp->get_tx_freq(channel) / 1e6) << std::endl << std::endl;
        m_txFreqActual = tx_usrp->get_tx_freq();

        // Set the TX gain.
        std::cout << boost::format("Setting TX Gain: %f dB...") % tx_gain << std::endl;
        tx_usrp->set_tx_gain(tx_gain, channel);
        std::cout << boost::format("Actual TX Gain: %f dB...") % tx_usrp->get_tx_gain(channel) << std::endl << std::endl;
        m_txGainActual = tx_usrp->get_tx_gain();

        // Set the analog frontend filter bandwidth.        
        std::cout << boost::format("Setting TX Bandwidth: %f MHz...") % tx_bw << std::endl;
        tx_usrp->set_tx_bandwidth(tx_bw, channel);
        std::cout << boost::format("Actual TX Bandwidth: %f MHz...") % tx_usrp->get_tx_bandwidth(channel) << std::endl << std::endl;
        m_txBWActual = tx_usrp->get_tx_bandwidth();
        
        // Set the TX antenna.
        if (tx_ant.size()) { tx_usrp->set_tx_antenna(tx_ant, channel); }
    }

    // ----------------- //
    //  Print new frame  //
    clear();
    systemInfo();
    std::cout << green << "\n\n[APP] [INFO]: " << white << "Setting up the SDR...\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "TX & RX USRP devices created.\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "Sampling frequencies set up.\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "TX set up.\n\n";
    // ----------------- //

    // --------------------------------- //
    //  S E T U P   R E C E P T I O N S  //
    // --------------------------------- //

    for (size_t ch = 0; ch < rx_channel_nums.size(); ch++) 
    {
        size_t channel = rx_channel_nums[ch];
        if (rx_channel_nums.size() > 1) { std::cout << "Configuring RX Channel " << channel << std::endl; }

        // Set RX freq.
        std::cout << boost::format("Setting RX Freq: %f MHz...") % (rx_freq / 1e6) << std::endl;
        uhd::tune_request_t rx_tune_request(rx_freq);
        if (rx_int_n.size()) { rx_tune_request.args = uhd::device_addr_t("mode_n=integer"); }
        rx_usrp->set_rx_freq(rx_tune_request, channel);
        std::cout << boost::format("Actual RX Freq: %f MHz...") % (rx_usrp->get_rx_freq(channel) / 1e6) << std::endl << std::endl;
        m_rxFreqActual = rx_usrp->get_rx_freq();

        // Set RX gain.
        std::cout << boost::format("Setting RX Gain: %f dB...") % rx_gain << std::endl;
        rx_usrp->set_rx_gain(rx_gain, channel);
        std::cout << boost::format("Actual RX Gain: %f dB...") % rx_usrp->get_rx_gain(channel) << std::endl << std::endl;
        m_rxGainActual = rx_usrp->get_rx_gain();

        // Set the receive analog frontend filter bandwidth.
        std::cout << boost::format("Setting RX Bandwidth: %f MHz...") % (rx_bw / 1e6) << std::endl;
        rx_usrp->set_rx_bandwidth(rx_bw, channel);
        std::cout << boost::format("Actual RX Bandwidth: %f MHz...") % (rx_usrp->get_rx_bandwidth(channel) / 1e6) << std::endl << std::endl;
        m_rxBWActual = rx_usrp->get_rx_bandwidth();
        
        // Set RX antenna.
        if (rx_ant.size()) { rx_usrp->set_rx_antenna(rx_ant, channel); }
    }

    // ----------------- //
    //  Print new frame  //
    clear();
    systemInfo();
    std::cout << green << "\n\n[APP] [INFO]: " << white << "Setting up the SDR...\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "TX & RX USRP devices created.\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "Sampling frequencies set up.\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "TX set up.\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "RX set up.\n";
    // ----------------- //
    
    // ----------------- //
    //  W A V E F O R M  //
    // ----------------- // 

    generateTransmissionPusle();

    // Ensure the waveform does not break Nyquist rule.
    if (std::abs(m_waveBandwidth) > (m_txSamplingFrequencyActual / 2)) 
        throw std::runtime_error("[WAVEFORM] [ERROR]: Wave frequency is out of Nyquist zone.");

    // Create the transmission streamer.
    uhd::stream_args_t stream_args(m_cpuFormat, m_overTheWire);
    stream_args.channels = tx_channel_nums;
    tx_stream = tx_usrp->get_tx_stream(stream_args);

    // ----------------- //
    //  Print new frame  //
    clear();
    systemInfo();
    std::cout << green << "\n\n[APP] [INFO]: " << white << "Setting up the SDR...\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "TX & RX USRP devices created.\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "Sampling frequencies set up.\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "TX set up.\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "RX set up.\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "Waveform precomputed.\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "TX streamer created.\n";
    // ----------------- //

    // Setup the metadata.
    md.start_of_burst = true;
    md.end_of_burst = false;
    md.has_time_spec = true;
    md.time_spec = uhd::time_spec_t(0.5); // Time given to setup the buffers.

    // --------------------------- //
    //  L O C K   R E F   &   L O  //
    // --------------------------- //

    std::vector<std::string> tx_sensor_names, rx_sensor_names;
    // TX Sensor.
    tx_sensor_names = tx_usrp->get_tx_sensor_names(0);
    if (std::find(tx_sensor_names.begin(), tx_sensor_names.end(), "lo_locked")
        != tx_sensor_names.end()) 
    {
        uhd::sensor_value_t lo_locked = tx_usrp->get_tx_sensor("lo_locked", 0);
        std::cout << boost::format("Checking TX: %s ...") % lo_locked.to_pp_string() << std::endl;
        UHD_ASSERT_THROW(lo_locked.to_bool());
    }

    // RX Sensor.
    rx_sensor_names = rx_usrp->get_rx_sensor_names(0);
    if (std::find(rx_sensor_names.begin(), rx_sensor_names.end(), "lo_locked")
        != rx_sensor_names.end()) 
    {
        uhd::sensor_value_t lo_locked = rx_usrp->get_rx_sensor("lo_locked", 0);
        std::cout << boost::format("Checking RX: %s ...") % lo_locked.to_pp_string() << std::endl;
        UHD_ASSERT_THROW(lo_locked.to_bool());
    }

    // TX mboard sensor.
    tx_sensor_names = tx_usrp->get_mboard_sensor_names(0);
    if ((ref == "mimo")
        and (std::find(tx_sensor_names.begin(), tx_sensor_names.end(), "mimo_locked")
            != tx_sensor_names.end())) 
    {
        uhd::sensor_value_t mimo_locked = tx_usrp->get_mboard_sensor("mimo_locked", 0);
        std::cout << boost::format("Checking TX: %s ...") % mimo_locked.to_pp_string() << std::endl;
        UHD_ASSERT_THROW(mimo_locked.to_bool());
    }
    if ((ref == "external")
        and (std::find(tx_sensor_names.begin(), tx_sensor_names.end(), "ref_locked")
            != tx_sensor_names.end())) 
    {
        uhd::sensor_value_t ref_locked = tx_usrp->get_mboard_sensor("ref_locked", 0);
        std::cout << boost::format("Checking TX: %s ...") % ref_locked.to_pp_string() << std::endl;
        UHD_ASSERT_THROW(ref_locked.to_bool());
    }

    // RX mboard sensor.
    rx_sensor_names = rx_usrp->get_mboard_sensor_names(0);
    if ((ref == "mimo")
        and (std::find(rx_sensor_names.begin(), rx_sensor_names.end(), "mimo_locked")
            != rx_sensor_names.end())) 
    {
        uhd::sensor_value_t mimo_locked = rx_usrp->get_mboard_sensor("mimo_locked", 0);
        std::cout << boost::format("Checking RX: %s ...") % mimo_locked.to_pp_string() << std::endl;
        UHD_ASSERT_THROW(mimo_locked.to_bool());
    }
    if ((ref == "external")
        and (std::find(rx_sensor_names.begin(), rx_sensor_names.end(), "ref_locked")
            != rx_sensor_names.end())) 
    {
        uhd::sensor_value_t ref_locked = rx_usrp->get_mboard_sensor("ref_locked", 0);
        std::cout << boost::format("Checking RX: %s ...") % ref_locked.to_pp_string() << std::endl;
        UHD_ASSERT_THROW(ref_locked.to_bool());
    }

    // ----------------- //
    //  Print new frame  //
    m_status = "Setup complete.";
    m_sdrInfo = "SDR is connected.";
    m_settingsStatusSDR = "Settings loaded to SDR.";
    clear();
    systemInfo();
    std::cout << green << "\n\n[APP] [INFO]: " << white << "Setting up the SDR...\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "TX & RX USRP devices created.\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "Sampling frequencies set up.\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "TX set up.\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "RX set up.\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "Waveform precomputed.\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "TX streamer created.\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "Sensors locked.\n";
    std::cout << green << "[APP] [INFO]: " << white << "Set up complete.\n";
    std::cout << green << "[APP] [INPUT]: " << white << "Enter any key to continue.\n";
    hold();
    // ----------------- //
}

void Interface::updateSDR() 
{
    clear();
    systemInfo();
    std::cout << green << "\n\n[APP] [INFO]: " << white << "Updating up the SDR...\n";

    // ------------------------- //
    //  T R A N S M I S S I O N  //
    // ------------------------- //

    for (size_t ch = 0; ch < tx_channel_nums.size(); ch++)
    {
        size_t channel = tx_channel_nums[ch];

        // Update TX frequency.
        uhd::tune_request_t tx_tune_request(tx_freq);
        if (tx_int_n.size()) { tx_tune_request.args = uhd::device_addr_t("mode_n=integer"); }
        tx_usrp->set_tx_freq(tx_tune_request, channel);
        m_txFreqActual = tx_usrp->get_tx_freq();

        // Update the TX gain.
        tx_usrp->set_tx_gain(tx_gain, channel);
        m_txGainActual = tx_usrp->get_tx_gain();

        // Update the analog frontend filter bandwidth.        
        tx_usrp->set_tx_bandwidth(tx_bw, channel);
        m_txBWActual = tx_usrp->get_tx_bandwidth();
    }

    std::cout << blue << "[SDR] [INFO]: " << white << "Transmission parameters updated.\n";

    // ------------------- //
    //  R E C E P T I O N  //
    // ------------------- //

    for (size_t ch = 0; ch < rx_channel_nums.size(); ch++)
    {
        size_t channel = rx_channel_nums[ch];

        // Set RX freq.
        uhd::tune_request_t rx_tune_request(rx_freq);
        if (rx_int_n.size()) { rx_tune_request.args = uhd::device_addr_t("mode_n=integer"); }
        rx_usrp->set_rx_freq(rx_tune_request, channel);
        m_rxFreqActual = rx_usrp->get_rx_freq();

        // Set RX gain.
        rx_usrp->set_rx_gain(rx_gain, channel);
        m_rxGainActual = rx_usrp->get_rx_gain();

        // Set the receive analog frontend filter bandwidth.
        rx_usrp->set_rx_bandwidth(rx_bw, channel);
        m_rxBWActual = rx_usrp->get_rx_bandwidth();
    }

    std::cout << blue << "[SDR] [INFO]: " << white << "Reception parameters updated.\n";

    // ----------------- //
    //  S A M P L I N G  //
    // ----------------- //

    // TX.
    if (tx_rate * 4 > 61.44) tx_usrp->set_master_clock_rate(tx_rate * 2);
    else                     tx_usrp->set_master_clock_rate(tx_rate * 4);
    tx_usrp->set_tx_rate(tx_rate);
    m_txSamplingFrequencyActual = tx_usrp->get_tx_rate();

    // RX.
    if (rx_rate * 4 > 61.44) rx_usrp->set_master_clock_rate(rx_rate * 2);
    else                     rx_usrp->set_master_clock_rate(rx_rate * 4);
    rx_usrp->set_rx_rate(rx_rate);
    m_rxSamplingFrequencyActual = rx_usrp->get_rx_rate();

    std::cout << blue << "\n[SDR] [INFO]: " << white << "Sampling frequencies updated.\n";

    hold();

    // Waveform updates.
    generateTransmissionPusle();

    // Update state information.
    m_status = "SDR updated.";
    m_sdrInfo = "SDR is connected.";
    m_settingsStatusSDR = "Settings loaded to SDR.";

    // Final frame.
    clear();
    systemInfo();
    std::cout << green << "\n\n[APP] [INFO]: " << white << "Updating up the SDR...\n";
    std::cout << blue << "\n[SDR] [INFO]: " << white << "Sampling frequencies updated.\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "Transmission parameters updated.\n";
    std::cout << blue << "[SDR] [INFO]: " << white << "Reception parameters updated.\n";
    std::cout << green << "\n[APP] [INFO]: " << white << "Update complete.\n";
    std::cout << green << "[APP] [INPUT]: " << white << "Enter any key to continue.\n";
    hold();
}

// ================================================================================================================================================================================ //
//  SDR Transmission.                                                                                                                                                               //
// ================================================================================================================================================================================ //

void Interface::startTransmission()
{
    // reset usrp time to prepare for transmit/receive
    m_status = "Streaming...";
    clear();
    systemInfo();
    std::cout << blue << "\n\n[SDR] [INFO]: " << white << "Transmitting...\n";
    std::cout << blue << "[SDR] [BUFFERS]: " << red;
    tx_usrp->set_time_now(uhd::time_spec_t(0.0));

    // The default buffer size in the Ettus example is 20 400 samples.
    // It is the max number of samples of the buffer times 10.  I do not 
    // know why they use this number, but for now it is going to be
    // used in this code.
    // Adjust the max number so that the waves fit in perfectly.
    size_t maxBufferSize = 20400;
    size_t wavesPerBuffer = std::floor(maxBufferSize / m_pulseLengthSamples);
    size_t bufferSize = wavesPerBuffer * m_pulseLengthSamples;

    // ----------------------- //
    //  T R A N S M I T T E R  //
    // ----------------------- //

    // Start transmit worker thread
    std::thread transmit_thread([&]() { Interface::transmitBuffer(m_transmissionWave, tx_stream, md, wavesPerBuffer); });

    // ------------------------- //
    //  R E C E I V E   F I L E  //
    // ------------------------- //

    std::string file = m_folderName + "\\" + m_targetFileName;
    receiveBufferToFile(rx_usrp, file, bufferSize, total_num_samps, settling);

    // --------------- //
    //  C L E A N U P  //
    // --------------- //

    // Clean up transmit worker.
    m_stopSignalCalled = true;
    transmit_thread.join();

    std::cout << blue << "\n[SDR] [INFO]: " << white << "Transmission complete.\n";
    std::cout << green << "[APP] [INFO]: " << white << "Add a transmission note:\n";
    // Remove .bin extension and add .txt.
    std::string tempFileName = m_targetFileName;
    tempFileName.erase(m_targetFileName.length() - 4, 4);
    tempFileName = m_folderName + "\\" + tempFileName + ".txt";
    // Create note file.
    std::ofstream noteFile(tempFileName);
    noteFile << "---------------------------------------------------------------------------------------\n";
    noteFile << "|                                  Details                                            |\n";
    noteFile << "---------------------------------------------------------------------------------------\n\n";
    std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char timeBuffer[50];
    ctime_s(timeBuffer, sizeof(timeBuffer), &currentTime);
    noteFile << "Time of transmission: " << timeBuffer;
    noteFile << "TX error: " << m_txError << "\n";
    noteFile << "RX error: " << m_rxError << "\n";
    noteFile << "OTW format: " << m_overTheWire << "\n";
    noteFile << "CPU format: " << m_cpuFormat << "\n\n";
    noteFile <<   "The data is packed as I Q I Q samples." <<
                "\nEach sample size is given by the CPU format." <<
                "\nOTW format is not required for parsing the .bin file, " <<
                "\nsince this describes how data is transferred on the SDR." <<
                "\nThe .bin file does not contain any type of headers, it is just IQ samples.\n";
    noteFile << "\n---------------------------------------------------------------------------------------\n";
    noteFile << "|                               Radar Settings                                        |\n";
    noteFile << "---------------------------------------------------------------------------------------\n\n";
    noteFile << "TX sampling rate: " << m_txSamplingFrequencyActual/ 1e6 << " MHz\n";
    noteFile << "RX sampling rate: " << m_rxSamplingFrequencyActual/ 1e6 << " MHz\n";
    noteFile << "TX wave frequency: " << m_txFreqActual/ 1e6 << " MHz\n";
    noteFile << "RX wave frequency: " << m_rxFreqActual/ 1e6 << " MHz\n";
    noteFile << "Wave bandwidth: " << m_waveBandwidth / 1e6 << " MHz\n";
    noteFile << "TX gain: " << m_txGainActual << " dB\n";
    noteFile << "RX gain: " << m_rxGainActual << " dB\n";
    noteFile << "TX filter BW: " << m_txBWActual/ 1e6 << " MHz\n";
    noteFile << "RX filter BW: " << m_rxBWActual/ 1e6 << " MHz\n";
    noteFile << "Transmission duration: " << m_txDurationActual << " s\n";
    noteFile << "PRF: " << m_pulsesPerTransmission / m_txDuration << " pulses/s\n";
    noteFile << "Total pulses: " << m_pulsesPerTransmission << "\n";
    noteFile << "Radar max range: " << m_maxRangeActual << " m\n";
    noteFile << "Radar deadzone: " << m_deadzoneActual << " m\n";
    noteFile << "Wave type: " << m_waveType << "\n";
    noteFile << "Window function: " << m_windowFunction << "\n\n";
    noteFile << "---------------------------------------------------------------------------------------\n";
    noteFile << "|                                     Note                                            |\n";
    noteFile << "---------------------------------------------------------------------------------------\n\n";
    std::string note;
    readInput(&note);
    noteFile << note << std::endl << std::endl;
    noteFile << "---------------------------------------------------------------------------------------\n";
    noteFile << "|                                      EOF                                            |\n";
    noteFile << "---------------------------------------------------------------------------------------\n\n";
    noteFile.close();
    // Update files.
    if (m_autoFileState == "Enabled") { generateFileName(); }
    getLatestFile();
    // Reset.
    m_stopSignalCalled = false;
    m_txError = "None";
    m_rxError = "None";
}

// ================================================================================================================================================================================ //
//  Reception.  	                                                                                                                                                                //
// ================================================================================================================================================================================ //

void Interface::receiveBufferToFile(uhd::usrp::multi_usrp::sptr usrp,
                                    const std::string& file,
                                    size_t samps_per_buff,
                                    int num_requested_samples,
                                    double settling_time)
{
    // ----------- //
    //  S E T U P  //
    // ----------- //

    // Create a receive streamer.
    uhd::stream_args_t stream_args(m_cpuFormat, m_overTheWire);
    // Only receiving in channel 0.
    stream_args.channels = { 0 };
    uhd::rx_streamer::sptr rx_stream = usrp->get_rx_stream(stream_args);
    // Receive buffer data.
    std::vector<std::complex<float>> receiveBuffer(samps_per_buff);
    // Receive buffer pointer.
    std::complex<float>* receiveBufferPtr = &receiveBuffer.front();

    // Create offstream object for reception.
    std::shared_ptr<std::ofstream> outfile = std::make_shared<std::ofstream>(file, std::ofstream::binary);

    // Error handling.
    bool overflow_message = true;

    // We increase the first timeout to cover for the delay between now + the
    // command time, plus 500ms of buffer. In the loop, we will then reduce the
    // timeout for subsequent receives.
    double timeout = settling_time + 1.f;

    // Issue stream command.
    uhd::stream_cmd_t stream_cmd(uhd::stream_cmd_t::STREAM_MODE_NUM_SAMPS_AND_DONE);
    stream_cmd.num_samps = num_requested_samples;
    stream_cmd.stream_now = false;
    stream_cmd.time_spec = usrp->get_time_now() + uhd::time_spec_t(settling_time);
    rx_stream->issue_stream_cmd(stream_cmd);

    // ------------------- //
    //  S T R E A M I N G  //
    // ------------------- //

    // Loop variables.
    size_t totalReceivedSamples = 0;
    size_t currentReceivedSamples = 0;
    // Receive metadata.  Used for error catching.
    uhd::rx_metadata_t rxMD;
    // Receive the number of requested samples.
    while (num_requested_samples > totalReceivedSamples)
    {
        currentReceivedSamples = rx_stream->recv(receiveBufferPtr, samps_per_buff, rxMD, timeout);
        timeout = 0.1f; // small timeout for subsequent recv   

        // Error handling.
        if (rxMD.error_code == uhd::rx_metadata_t::ERROR_CODE_TIMEOUT) { std::cout << boost::format("Timeout while streaming") << std::endl; m_rxError = "Timeout while streaming"; break; }
        if (rxMD.error_code == uhd::rx_metadata_t::ERROR_CODE_OVERFLOW) { m_rxError = "Overflow occured"; break; }
        if (rxMD.error_code != uhd::rx_metadata_t::ERROR_CODE_NONE) { throw std::runtime_error(str(boost::format("Receiver error %s") % rxMD.strerror())); m_rxError = rxMD.strerror(); }

        totalReceivedSamples += currentReceivedSamples;
        outfile->write((const char*)receiveBufferPtr, currentReceivedSamples * sizeof(std::complex<float>));
    }

    // Close file.
    outfile->close();
}

// ================================================================================================================================================================================ //
//  Transmission.	                                                                                                                                                                //
// ================================================================================================================================================================================ //

void Interface::transmitBuffer(std::vector<std::complex<float>> transmitWave,
                               uhd::tx_streamer::sptr tx_streamer,
                               uhd::tx_metadata_t metadata,
                               size_t wavesPerBuffer)
{
    // Generate a larger buffer that contains the waveform.
    std::vector<std::complex<float>> waveBuffer;
    waveBuffer.reserve(transmitWave.size());
    for (int i = 0; i < wavesPerBuffer; i++) { waveBuffer.insert(waveBuffer.end(), transmitWave.begin(), transmitWave.end()); }
    std::complex<float>* bufferPtr = &waveBuffer.front();
    // Transmit the data until the stop signal is called.
    while (not m_stopSignalCalled)
    {
        // Transmit the contents of the buffer.
        tx_streamer->send(bufferPtr, waveBuffer.size(), metadata);
        metadata.start_of_burst = false;
        metadata.has_time_spec = false;
    }
    // Send an End-Of-Burst packet.
    metadata.end_of_burst = true;
    tx_streamer->send("", 0, metadata);
}

// ================================================================================================================================================================================ //
//  EOF.	                                                                                                                                                                        //
// ================================================================================================================================================================================ //