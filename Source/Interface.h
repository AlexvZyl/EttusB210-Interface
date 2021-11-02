#pragma once

/*
* This class will contain all of the menu functions and the SDR interfacing functions.
*/

// ================================================================================================================================================================================ //
//  Includes.                                                                                                                                                                       //
// ================================================================================================================================================================================ //

#include "wavetable.hpp"
#include <string>									// String handling.
#include <vector>									// C++ vectors.
#include <uhd/exception.hpp>						// -- Ettus UHD.
#include <uhd/types/tune_request.hpp>				// \/
#include <uhd/usrp/multi_usrp.hpp>					// \/
#include <uhd/utils/safe_main.hpp>					// \/
#include <uhd/utils/static.hpp>						// \/
#include <uhd/utils/thread.hpp>						// --
#include <boost/algorithm/string.hpp>				// -- Boost.
#include <boost/filesystem.hpp>						// \/ 
#include <boost/format.hpp>							// \/
#include <boost/math/special_functions/round.hpp>	// \/ 
#include <boost/program_options.hpp>				// \/ 
#include <boost/thread/thread.hpp>					// --
#include <complex>

// ================================================================================================================================================================================ //
//  Global variables.                                                                                                                                                               //
// ================================================================================================================================================================================ //

static bool stop_signal_called=false;			// Should the workers stop?

// ================================================================================================================================================================================ //
//  Class definition.																																								//
// ================================================================================================================================================================================ //

class Interface 
{
private:

	// --------------------------------- //
	//  S Y S T E M   V A R I A B L E S  //
	// --------------------------------- //

	std::string m_folderName;				// The current folder data will be saved to.
	std::string m_latestFileName;			// The latest file.
	std::string m_currentFileName;			// The current file data will be written to.
	bool m_autoFiling;						// Sets if the application should determine the file name and
											// automatically increment as required.
	float m_samplingFrequency;				// Set the sampling frequency of the SDR.
	float m_waveFrequency;					// Set the TX/RX frequency of the variable.
	std::vector<void*> m_mainMenuOptions;	// Vector containing all of the menu otption as functions.
	std::string m_status;					// The status of the app.

	// -------------------------- //
	// S D R   V A R I A B L E S  //
	// -------------------------- //

	// Transmit variables set by po.
	std::string tx_args, wave_type, tx_ant, tx_subdev, ref, otw, tx_channels;
	double tx_rate, tx_freq, tx_gain, wave_freq, tx_bw;
	float ampl;

	// Receive variables set by po.
	std::string rx_args, file, type, rx_ant, rx_subdev, rx_channels;
	size_t total_num_samps, spb;
	double rx_rate, rx_freq, rx_gain, rx_bw;
	double settling;


public:

	bool shouldClose = false;			// Determines if the app should close.

	// ------------------------------------------------- //
	//  C O N S T R U C T O R   &   D E S T R U C T O R  //
	// ------------------------------------------------- //

	// Set the default values for the system.
	Interface();		
	// Destroy objects and clear memory.
	~Interface();

	// --------------------------------- //
	//  A P P L I C A T I O N   M E N U  //
	// --------------------------------- //

	// Prints the current information of the system.
	void systemInfo();
	// Prints the main menu of the app, as well as handle inputs.
	void mainMenu();
	// Clears the console.
	void clear();

	// Main menu functions.
	void setupSDR();
	void setFolder();
	void setFile();
	void toggleAutoFiling();
	void quit();

	// --------------------------- //
	//  S D R   I N T E R F A C E  //
	// --------------------------- //

	// Signal handler.
	void sig_int_handler(int);
	// Change to filename, e.g. from usrp_samples.dat to usrp_samples.00.dat,
	// but only if multiple names are to be generated.
	std::string generate_out_filename(const std::string& base_fn, 
									  size_t n_names, size_t this_name);
	// Recv_to_file function.
	template <typename samp_type>
	void recv_to_file(uhd::usrp::multi_usrp::sptr usrp,
		const std::string& cpu_format,
		const std::string& wire_format,
		const std::string& file,
		size_t samps_per_buff,
		int num_requested_samples,
		double settling_time,
		std::vector<size_t> rx_channel_nums);

};

// ================================================================================================================================================================================ //
//  Function definitions.                                                                                                                                                           //
// ================================================================================================================================================================================ //

void transmit_worker(std::vector<std::complex<float>> buff,
	wave_table_class wave_table,
	uhd::tx_streamer::sptr tx_streamer,
	uhd::tx_metadata_t metadata,
	size_t step,
	size_t index,
	int num_channels);

// ================================================================================================================================================================================ //
//  EOF.																																											//
// ================================================================================================================================================================================ //