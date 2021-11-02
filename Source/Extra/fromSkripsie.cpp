//
//// UHD includes
////#include <uhd/utils/thread_priority.hpp>
//#include <uhd/utils/thread.hpp>
//#include <uhd/types/device_addr.hpp>
//#include <uhd/utils/safe_main.hpp>
//#include <uhd/usrp/multi_usrp.hpp>
//#include <uhd/exception.hpp>
//#include <uhd/types/tune_request.hpp>
//#include <uhd/types/stream_cmd.hpp>
//#include <uhd/types/metadata.hpp>
//#include <uhd/stream.hpp>
//
//// Boost
//#include <boost/program_options.hpp>
//#include <boost/format.hpp>
//#include <boost/thread.hpp>
//
//// Standard libraries
//#include <iostream>
//#include <fstream>
//#include <cmath>
//
////  Include xcorr file
//#include <fasttransforms.h>
//
////  Function Definitions
//void TX_STR_Thread(uhd::tx_streamer::sptr TXS, std::vector<std::complex<float>*> TXPTR, size_t TXPS, uhd::tx_metadata_t TXMD, size_t TPS);
//void RX_STR_Thread(uhd::rx_streamer::sptr RXS, uhd::stream_cmd_t RXSC, uhd::usrp::multi_usrp::sptr SDR);
//void RX_RECV_Thread(uhd::rx_streamer::sptr RXS, std::vector<std::complex<float>*> RXPTR, size_t RXPS, uhd::rx_metadata_t RXMD, size_t TPS);
//
//int UHD_SAFE_MAIN(int argc, char* argv[])
//{
//    //------------------------------------------------------------------------------------------------------------------------------------------------------------------
//    //  Setup parameters
//    //------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//    uhd::set_thread_priority();
//
//    //  Radar Parameter setings
//    float c = 299792458;
//    float PI = 3.14159265358979323846l;
//    std::string device_args("");
//    std::string subdev("A:A");
//    std::string RX_ant("RX2");
//    std::string TX_ant("RX/TX");
//    std::string ref("internal");
//    //float fs(32e6);
//    float fs(16e6);
//    double fc(1.1e9);
//    double gain_TX(83);
//    double gain_RX(0);
//    double PRF(150e3);
//    float delta_f(7e6);
//    double bw(delta_f * 1.2);
//    double TX_time = 2;
//    int PULSE_SAMPLES = 13;//37;  //  Has to be odd number
//    //int PULSE_SAMPLES = 19;  //  Has to be odd number
//    float T_s = std::pow(fs, -1);
//    float LRR_DZ = (c * PULSE_SAMPLES * T_s) / 2;
//    int CPI(2);
//
//    //  Print parameters
//    std::cout << std::endl;
//    std::cout << "Parameters:" << std::endl;
//    std::cout << "Sampling Frequency: " << fs << std::endl;
//    std::cout << "Carrier Frequency: " << fc << std::endl;
//    std::cout << "TX Gain: " << gain_TX << "dB" << std::endl;
//    std::cout << "RX Gain: " << gain_RX << "dB" << std::endl;
//    std::cout << "IF Bandwidth: " << bw << std::endl;
//    std::cout << "Chirp Frequency: " << delta_f << std::endl;
//    std::cout << "Transmit Time: " << TX_time << std::endl;
//    std::cout << "Long Range Radar DZ: " << LRR_DZ << std::endl;
//    std::cout << "Pulse length (samples): " << PULSE_SAMPLES << std::endl;
//    std::cout << "CPI: " << CPI << std::endl;
//
//    //------------------------------------------------------------------------------------------------------------------------------------------------------------------
//    //  Setup Devices
//    //------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//    //Create a USRP device
//    std::cout << std::endl;
//    std::cout << boost::format("Creating the USRP device...") << std::endl;
//    uhd::usrp::multi_usrp::sptr EttusB210 = uhd::usrp::multi_usrp::make(device_args);
//    std::cout << std::endl;
//    // Lock mboard clocks
//    std::cout << boost::format("Lock Mboard Clocks: %f") % ref << std::endl;
//    EttusB210->set_clock_source(ref);
//
//    //------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//    //  Setting up the RX device
//    std::cout << "Set up RX:" << std::endl;
//    // set sample rate
//    std::cout << boost::format("Setting RX Sampling Frequency: %f Msps.") % (fs / 1e6) << std::endl;
//    EttusB210->set_rx_rate(fs);
//    std::cout << boost::format("Actual RX Sampling Frequency: %f Msps.") % (EttusB210->get_rx_rate() / 1e6) << std::endl;
//    // set freq
//    std::cout << boost::format("Setting RX Center Frequency: %f MHz.") % (fc / 1e6) << std::endl;
//    uhd::tune_request_t tune_request_RX(fc);
//    EttusB210->set_rx_freq(tune_request_RX);
//    std::cout << boost::format("Actual RX Center Frequency: %f MHz.") % (EttusB210->get_rx_freq() / 1e6) << std::endl;
//    // set the rf gain
//    std::cout << boost::format("Setting RX Gain: %f dB.") % gain_RX << std::endl;
//    EttusB210->set_rx_gain(gain_RX);
//    std::cout << boost::format("Actual RX Gain: %f dB.") % EttusB210->get_rx_gain() << std::endl;
//    // set the IF filter bandwidth
//    std::cout << boost::format("Setting RX IF Filter Bandwidth: %f MHz.") % (bw / 1e6) << std::endl;
//    EttusB210->set_rx_bandwidth(bw);
//    std::cout << boost::format("Actual RX IF Filter Bandwidth: %f MHz.") % (EttusB210->get_rx_bandwidth() / 1e6) << std::endl;
//    // set the antenna
//    std::cout << boost::format("Setting RX Antenna: %s.") % RX_ant << std::endl;
//    EttusB210->set_rx_antenna(RX_ant);
//    std::cout << boost::format("Actual RX Antenna: %s.") % EttusB210->get_rx_antenna() << std::endl << std::endl;
//
//    //------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//    //  Setting up the TX device
//    std::cout << "Set up TX:" << std::endl;
//    // set sample rate
//    std::cout << boost::format("Setting TX Sampling Frequency: %f Msps.") % (fs / 1e6) << std::endl;
//    EttusB210->set_tx_rate(fs);
//    std::cout << boost::format("Actual TX Sampling Frequency: %f Msps.") % (EttusB210->get_tx_rate() / 1e6) << std::endl;
//    // set freq
//    std::cout << boost::format("Setting TX Center Frequency: %f MHz.") % (fc / 1e6) << std::endl;
//    uhd::tune_request_t tune_request_TX(fc);
//    EttusB210->set_tx_freq(tune_request_TX);
//    std::cout << boost::format("Actual TX Center Frequency: %f MHz.") % (EttusB210->get_tx_freq() / 1e6) << std::endl;
//    // set the rf gain
//    std::cout << boost::format("Setting TX Gain: %f dB.") % gain_TX << std::endl;
//    EttusB210->set_tx_gain(gain_TX);
//    std::cout << boost::format("Actual TX Gain: %f dB.") % EttusB210->get_tx_gain() << std::endl;
//    // set the IF filter bandwidth
//    std::cout << boost::format("Setting TX IF Filter Bandwidth: %f MHz.") % (bw / 1e6) << std::endl;
//    EttusB210->set_tx_bandwidth(bw);
//    std::cout << boost::format("Actual TX IF Filter Bandwidth: %f MHz.") % (EttusB210->get_tx_bandwidth() / 1e6) << std::endl;
//    // set the antenna
//    std::cout << boost::format("Setting TX Antenna: %s.") % TX_ant << std::endl;
//    EttusB210->set_tx_antenna(TX_ant);
//    std::cout << boost::format("Actual TX Antenna: %s.") % EttusB210->get_tx_antenna() << std::endl << std::endl;
//
//    std::cout << "Settling...";
//    Sleep(1000);
//    std::cout << " Done." << "\n" << "\n";
//
//    //------------------------------------------------------------------------------------------------------------------------------------------------------------------
//    //  Tuning
//    //------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//    std::cout << "Tuning...";
//    EttusB210->clear_command_time();
//    EttusB210->set_command_time(EttusB210->get_time_now() + uhd::time_spec_t(0.1)); //set cmd time for .1s in the future
//    uhd::tune_request_t tune_request(fc);
//    EttusB210->set_rx_freq(tune_request);
//    EttusB210->set_tx_freq(tune_request);
//    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //sleep 110ms (~10ms after retune occurs) to allow LO to lock
//    EttusB210->clear_command_time();
//    Sleep(1000);
//    std::cout << " Done." << "\n" << "\n";
//
//    //------------------------------------------------------------------------------------------------------------------------------------------------------------------
//    //  Setup Streamers
//    //------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//    //  Setup streaming format  
//    uhd::stream_args_t stream_args = uhd::stream_args_t("fc32", "sc16");
//    stream_args.args["underflow_policy"] = "next_packet";
//
//    //  Setup TX Streamer
//    uhd::tx_streamer::sptr TX_streamer = EttusB210->get_tx_stream(stream_args);
//    uhd::tx_metadata_t TX_metadata;
//    TX_metadata.start_of_burst = false;
//    TX_metadata.end_of_burst = false;
//    TX_metadata.has_time_spec = true;
//
//    //  Setup RX Streamer
//    uhd::rx_streamer::sptr RX_streamer = EttusB210->get_rx_stream(stream_args);
//    uhd::stream_cmd_t RX_stream_cmd(uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS);
//    RX_stream_cmd.stream_now = false;
//
//    //  RX Buffer Settings
//    uhd::rx_metadata_t RX_metadata;
//    RX_metadata.has_time_spec = false;
//
//    //------------------------------------------------------------------------------------------------------------------------------------------------------------------
//    //  Generate transmission signal
//    //------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//    //  Transmission Signal Variables
//    double PRF_TIME = std::pow(PRF, -1);
//    int PRF_SAMPLES = std::ceil(PRF_TIME / T_s);
//    int ZERO_AREA_SAMPLES = PRF_SAMPLES - PULSE_SAMPLES;
//    const std::complex<float> i(0, 1);
//
//    //  Packet sizes
//    size_t TEMP_PACKET = TX_streamer->get_max_num_samps();
//    size_t TX_SAMPLES_LENGTH = PRF * PRF_SAMPLES;
//    size_t PULSES_PER_PACKET = std::floor(TEMP_PACKET / PRF_SAMPLES);
//    size_t TX_PACKET_SIZE = PULSES_PER_PACKET * PRF_SAMPLES;
//    size_t TOT_PACKETS_SEND = (TX_SAMPLES_LENGTH / TX_PACKET_SIZE) * TX_time;
//    TX_SAMPLES_LENGTH = TOT_PACKETS_SEND * PULSES_PER_PACKET * PRF_SAMPLES;
//    size_t RX_PACKET_SIZE = RX_streamer->get_max_num_samps();
//    size_t RX_PACKETS = std::ceil(TX_SAMPLES_LENGTH / RX_PACKET_SIZE);
//
//    //  Create TX Signal Modulated signal
//    float m = (float)(delta_f) / ((float)PULSE_SAMPLES - (float)1);
//    int index = 0;
//    float FREQ;
//    std::vector<std::complex<float>> TX_Signal_i(PULSE_SAMPLES);
//    for (int n = -(PULSE_SAMPLES - 1) / 2; n <= (PULSE_SAMPLES - 1) / 2; n++)
//    {
//        FREQ = ((m * index) - (delta_f / 2)) / fs;
//        TX_Signal_i[index] = std::exp(n * -2 * PI * FREQ * i);
//        index++;
//    }
//
//    //  Implement blackman window
//    std::vector<float> BWind(PULSE_SAMPLES);
//    for (int n = 0; n < PULSE_SAMPLES; n++)
//    {
//        BWind[n] = 0.42 - 0.5 * std::cos((2 * PI * n) / (PULSE_SAMPLES - 1)) + 0.08 * std::cos(((4 * PI * n) / (PULSE_SAMPLES - 1)));
//    }
//
//    //  Multiply with BM window
//    for (int n = 0; n < PULSE_SAMPLES; n++)
//    {
//        TX_Signal_i[n] = TX_Signal_i[n] * BWind[n];
//    }
//
//    //  Create signal to be correlated
//    std::vector<std::complex<float>> TX_Signal_Pulse(PULSE_SAMPLES);
//    for (int n=0; n<PULSE_SAMPLES; n++)
//    {
//        TX_Signal_Pulse[n] = TX_Signal_i[n];
//    }
//
//    //  Combine signal to one vector
//    std::vector<std::complex<float>> TX_Signal_Zeros(ZERO_AREA_SAMPLES, std::complex<float>(0, 0));
//    std::vector<std::complex<float>> TX_Signal;
//    TX_Signal_i.insert(TX_Signal_i.end(), TX_Signal_Zeros.begin(), TX_Signal_Zeros.end());
//
//    std::cout << "Pulse length in samples: " << PRF_SAMPLES << "\n" << "\n";
//
//    int CPulse = 0;
//    while (CPulse < TOT_PACKETS_SEND * PULSES_PER_PACKET)
//    {
//        TX_Signal.insert(TX_Signal.end(), TX_Signal_i.begin(), TX_Signal_i.end());
//        CPulse++;
//    }
//
//    //------------------------------------------------------------------------------------------------------------------------------------------------------------------
//    //  Setup buffers
//    //------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//    //  TX Signal Pointer
//    std::vector<std::complex<float>*> TX_PTR(TOT_PACKETS_SEND);
//    //  Assign Buffer Ptr Values
//    for (int k = 0; k < TOT_PACKETS_SEND; k++)
//    {
//        TX_PTR[k] = &TX_Signal[k * TX_PACKET_SIZE];
//    }
//
//    std::vector<std::complex<float>> RX_Signal(RX_PACKETS * RX_PACKET_SIZE, std::complex<float>(0, 0));
//    std::vector<std::complex<float>*> RX_PTR(RX_PACKETS);
//    //  Assign Buffer Ptr Values
//    for (int k = 0; k < RX_PACKETS; k++)
//    {
//        RX_PTR[k] = &RX_Signal[k * RX_PACKET_SIZE];
//    }
//
//    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
//    //  Transmit and Receive
//    //------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//    std::cout << "Press to transmit." << "\n";
//    int dummy;
//    std::cin >> dummy;
//
//    //  Setup time synchronization
//    uhd::time_spec_t cur_time(EttusB210->get_time_now());
//    uhd::time_spec_t wait = uhd::time_spec_t(double(1));
//    uhd::time_spec_t exe_time = uhd::time_spec_t(cur_time + wait);
//    TX_metadata.time_spec = uhd::time_spec_t(exe_time);
//    RX_stream_cmd.time_spec = uhd::time_spec_t(exe_time);
//    RX_metadata.time_spec = uhd::time_spec_t(exe_time);
//
//    std::cout << "Transmitting..." << std::endl;
//
//    //  Setup Threading
//    std::thread TX_S_Thread(&TX_STR_Thread, TX_streamer, TX_PTR, TX_PACKET_SIZE, TX_metadata, TOT_PACKETS_SEND);
//    std::thread RX_S_Thread(&RX_STR_Thread, RX_streamer, RX_stream_cmd, EttusB210);
//    std::thread RX_R_Thread(&RX_RECV_Thread, RX_streamer, RX_PTR, RX_PACKET_SIZE, RX_metadata, RX_PACKETS);
//
//    //  Wait for all the threads to finish
//    TX_S_Thread.join();
//    RX_S_Thread.join();
//    RX_R_Thread.join();
//
//    // Stop continuous streaming
//    RX_stream_cmd.stream_mode = uhd::stream_cmd_t::STREAM_MODE_STOP_CONTINUOUS;
//    RX_streamer->issue_stream_cmd(RX_stream_cmd);
//
//    std::cout << std::endl << "Done." << std::endl << std::endl;
//
//    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
//    //  Synchronize
//    //------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//    std::cout << "Processing..." << std::endl << "\n";
//
//    //  Remove first pulses since these are missed
//    int Offset = 300;
//    RX_Signal.erase(RX_Signal.begin(), RX_Signal.begin() + PRF_SAMPLES*Offset);
//
//    //  Extract a Pulse to sync
//    std::vector<std::complex<float>> SinglePulse(PRF_SAMPLES);
//    int PulseOffset = 0;
//    for (int n = 0; n < PRF_SAMPLES; n++)
//    {
//        SinglePulse[n] = RX_Signal[n + (int)PulseOffset * PRF_SAMPLES];
//    }
//
//    //  Signal to be correlated
//    std::vector<std::complex<float>> SignalCorr(PRF_SAMPLES, std::complex<float>(0, 0));
//
//    //  Add zeros to the signal so that a full correlation can be done
//    std::vector<std::complex<float>> SinglePulseZeros(PULSE_SAMPLES - 1, std::complex<float>(0, 0));
//    std::vector<std::complex<float>> Corr_zeros(PULSE_SAMPLES - 1, std::complex<float>(0, 0));
//    SinglePulseZeros.insert(SinglePulseZeros.end(), SinglePulse.begin(), SinglePulse.end());
//    SinglePulseZeros.insert(SinglePulseZeros.end(), Corr_zeros.begin(), Corr_zeros.end());
//
//    //  Implement xcorrelation
//    for (int n = 0; n < PRF_SAMPLES; n++)
//    {
//        for (int m = 0; m < PULSE_SAMPLES; m++)
//        {
//            SignalCorr[n] += TX_Signal_Pulse[m] * SinglePulseZeros[m + (PULSE_SAMPLES - 1) / 2 + n];
//        }
//    }
//
//    //  Find absolute value
//    std::vector<float> SignalCorrAbs(PRF_SAMPLES);
//    for (int k = 0; k < PRF_SAMPLES; k++)
//    {
//        SignalCorrAbs[k] = std::abs(SignalCorr[k]);
//    }
//
//    //  Find max value
//    float max = SignalCorrAbs[0];
//    int maxIndex = 0;
//    for (int k = 1; k < PRF_SAMPLES; k++)
//    {   
//        if (SignalCorrAbs[k] > max) { max = SignalCorrAbs[k]; maxIndex = k; }
//    }
//
//    //  Correct signal by factor
//    RX_Signal.erase(RX_Signal.begin(), RX_Signal.begin()+maxIndex/2);
//
//    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
//    //  Align into matrix
//    //------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//    int Pulses = PRF - 1000;
//    std::vector<std::vector<std::complex<float>>> DataMatrix(PRF_SAMPLES, std::vector<std::complex<float>>(Pulses*CPI,(0,0)));
//
//    for (int i=0; i<Pulses*CPI; i++) 
//    {
//        for (int j = 0; j < PRF_SAMPLES; j++) 
//        {
//            DataMatrix[j][i] = RX_Signal[j + i*(PRF_SAMPLES)];
//        }
//    }
//
//    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
//    //  Pulse Compression
//    //------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//    //  Find conj of tx pulse to use as matched filter
//    std::vector<std::complex<float>> TX_Signal_Pulse_Conj(PULSE_SAMPLES);
//    for (int j = 0; j < PULSE_SAMPLES; j++) 
//    {
//        TX_Signal_Pulse_Conj[j] = std::conj(TX_Signal_Pulse[j]);
//    }
//
//    //  Create empty array to convolute to
//    std::vector<std::vector<std::complex<float>>> DataMatrixFiltered(PRF_SAMPLES, std::vector<std::complex<float>>(Pulses*CPI, (0, 0)));
//
//    //  Add the zeros to be able to convolute
//    std::vector<std::vector<std::complex<float>>> DataMatrixZeros(PRF_SAMPLES + 2*(PULSE_SAMPLES-1), std::vector<std::complex<float>>(Pulses*CPI, (0, 0)));
//    std::vector<std::complex<float>> Conv_zeros(PULSE_SAMPLES - 1, std::complex<float>(0, 0));
//    //  Add zeros to each pulse
//    for (int j=0; j<Pulses*CPI; j++) 
//    {
//        std::vector<std::complex<float>> NewData(PULSE_SAMPLES-1, std::complex<float>(0, 0));
//        std::vector<std::complex<float>> LoadedFromData(PRF_SAMPLES, std::complex<float>(0, 0));
//        for (int k = 0; k < PRF_SAMPLES; k++)
//        {
//            LoadedFromData[k] = DataMatrix[k][j];
//        }
//        NewData.insert(NewData.end(), LoadedFromData.begin(), LoadedFromData.end());
//        NewData.insert(NewData.end(), Conv_zeros.begin(), Conv_zeros.end());
//        //  Put into new matrix
//        for (int k = 0; k < PRF_SAMPLES + 2 * (PULSE_SAMPLES - 1); k++)
//        {
//            DataMatrixZeros[k][j] = NewData[k];
//        }
//    }
//
//    //  Filter loop for each Pulse
//    for (int j=0; j<Pulses*CPI; j++) 
//    {   
//        //  Convolute each pulse
//        for (int n = 0; n < PRF_SAMPLES; n++)
//        {
//            for (int m = 0; m < PULSE_SAMPLES; m++)
//            {
//                DataMatrixFiltered[n][j] += TX_Signal_Pulse_Conj[m] * DataMatrixZeros[(m+1) + (PULSE_SAMPLES - 1) / 2 + n][j];
//            }
//        }
//    }
//
//    //------------------------------------
//    //  Write real component of data matrix to file
//    //------------------------------------
//
//    //int PulsesToWrite = 295000;
//    //std::cout << "Writing data matrix real to file...";
//    //std::ofstream DataMatrixRealFile;
//
//    //std::string File_Name_VI = "DataMatrixReal3.txt";
//    //DataMatrixRealFile.open(File_Name_VI, std::ofstream::out);
//
//    //for (int p = 0; p < PulsesToWrite; p++)
//    //{
//    //    for (int s = 0; s < PRF_SAMPLES; s++)
//    //    {
//    //        DataMatrixRealFile << std::real(DataMatrixFiltered[s][p]) << '\n';
//    //    }
//    //}
//    //DataMatrixRealFile.close();
//    //std::cout << " Done." << "\n";
//
//    ////------------------------------------
//    ////  Write complex component of data matrix to file
//    ////------------------------------------
//
//    //std::cout << "Writing data matrix complex to file...";
//    //std::ofstream DataMatrixComplexFile;
//
//    //std::string File_Name_VII = "DataMatrixComplex3.txt";
//    //DataMatrixComplexFile.open(File_Name_VII, std::ofstream::out);
//
//    //for (int p = 0; p < PulsesToWrite; p++)
//    //{
//    //    for (int s = 0; s < PRF_SAMPLES; s++)
//    //    {
//    //        DataMatrixComplexFile << std::imag(DataMatrixFiltered[s][p]) << '\n';
//    //    }
//    //}
//    //DataMatrixComplexFile.close();
//    //std::cout << " Done." << "\n";
//    
//    std::cout << "\n" << "Done." << "\n";
//    return EXIT_SUCCESS;
//
//};
//
////--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
////  Threading functions
////--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
////  Transmit streamer
//void TX_STR_Thread(uhd::tx_streamer::sptr TXS, std::vector<std::complex<float>*> TXPTR, size_t TXPS, uhd::tx_metadata_t TXMD, size_t TPS)
//{
//    TXS->send(TXPTR[0], TXPS, TXMD);
//    TXMD.has_time_spec = false;
//    size_t CP = 0;
//    while (CP < TPS)
//    {
//        TXS->send(TXPTR[CP], TXPS, TXMD);
//        CP++;
//    }
//    // Send EOB packet
//    TXMD.end_of_burst = true;
//    TXS->send("", 0, TXMD);
//}
//
////  Receive streamer
//void RX_STR_Thread(uhd::rx_streamer::sptr RXS, uhd::stream_cmd_t RXSC, uhd::usrp::multi_usrp::sptr SDR)
//{
//    RXS->issue_stream_cmd(RXSC);
//}
//
////  Receive buffer
//void RX_RECV_Thread(uhd::rx_streamer::sptr RXS, std::vector<std::complex<float>*> RXPTR, size_t RXPS, uhd::rx_metadata_t RXMD, size_t TPS)
//{
//    RXS->recv(RXPTR[0], RXPS, RXMD, 0.1, true);
//    RXMD.has_time_spec = false;
//    size_t CP = 0;
//    while (CP < TPS)
//    {
//        RXS->recv(RXPTR[CP], RXPS, RXMD, 0.1, true);
//        CP++;
//    }
//}
