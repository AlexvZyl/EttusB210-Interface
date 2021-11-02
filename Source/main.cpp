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
#include "Interface.h"								//  Class running the app.

// ================================================================================================================================================================================ //
//  Main.                                                                                                                                                                           //
// ================================================================================================================================================================================ //

int UHD_SAFE_MAIN(int argc, char* argv[])
{	
	//  Create a new interface.
	Interface SDRInterface = Interface();

	//  [MAIN LOOP]
	while (!SDRInterface.shouldClose) 
	{
		SDRInterface.mainMenu();
	}

	// Done.
	return EXIT_SUCCESS;
}

// ================================================================================================================================================================================ //
// EOF.			                                                                                                                                                                    //
// ================================================================================================================================================================================ //