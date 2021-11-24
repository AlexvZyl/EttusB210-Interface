// ********************************************************************************************************************************
// 
// This function implements pulse compression that is to be used on a received signal
// Taken from the code used in the skripsie
// 
// ******************************************************************************************************************************** 
// 
// Includes
// 
// ******************************************************************************************************************************** 

#include <uhd/exception.hpp>
#include <uhd/types/tune_request.hpp>
#include <uhd/usrp/multi_usrp.hpp>
#include <uhd/utils/safe_main.hpp>
#include <uhd/utils/static.hpp>
#include <uhd/utils/thread.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/program_options.hpp>
#include <boost/thread/thread.hpp>
#include <csignal>
#include <fstream>
#include <functional>
#include <iostream>
#include <complex>

// ******************************************************************************************************************************** 
// 
// Function
// 
// ******************************************************************************************************************************** 

int pulseCompression(std::vector<std::complex<float>>* TX_Signal_Pulse, int PULSE_SAMPLES, int PRF_SAMPLES, int Pulses, int CPI)
{

    //  Find conj of tx pulse to use as matched filter
    std::vector<std::complex<float>> TX_Signal_Pulse_Conj(PULSE_SAMPLES);
    for (int j = 0; j < PULSE_SAMPLES; j++)
    {
        TX_Signal_Pulse_Conj[j] = std::conj(TX_Signal_Pulse[j]);
    }

    //  Create empty array to convolute to
    std::vector<std::vector<std::complex<float>>> DataMatrixFiltered(PRF_SAMPLES, std::vector<std::complex<float>>(Pulses * CPI, (0, 0)));

    //  Add the zeros to be able to convolute
    std::vector<std::vector<std::complex<float>>> DataMatrixZeros(PRF_SAMPLES + 2 * (PULSE_SAMPLES - 1), std::vector<std::complex<float>>(Pulses * CPI, (0, 0)));
    std::vector<std::complex<float>> Conv_zeros(PULSE_SAMPLES - 1, std::complex<float>(0, 0));
    //  Add zeros to each pulse
    for (int j = 0; j < Pulses * CPI; j++)
    {
        std::vector<std::complex<float>> NewData(PULSE_SAMPLES - 1, std::complex<float>(0, 0));
        std::vector<std::complex<float>> LoadedFromData(PRF_SAMPLES, std::complex<float>(0, 0));
        for (int k = 0; k < PRF_SAMPLES; k++)
        {
            LoadedFromData[k] = DataMatrix[k][j];
        }
        NewData.insert(NewData.end(), LoadedFromData.begin(), LoadedFromData.end());
        NewData.insert(NewData.end(), Conv_zeros.begin(), Conv_zeros.end());
        //  Put into new matrix
        for (int k = 0; k < PRF_SAMPLES + 2 * (PULSE_SAMPLES - 1); k++)
        {
            DataMatrixZeros[k][j] = NewData[k];
        }
    }

    //  Filter loop for each Pulse
    for (int j = 0; j < Pulses * CPI; j++)
    {
        //  Convolute each pulse
        for (int n = 0; n < PRF_SAMPLES; n++)
        {
            for (int m = 0; m < PULSE_SAMPLES; m++)
            {
                DataMatrixFiltered[n][j] += TX_Signal_Pulse_Conj[m] * DataMatrixZeros[(m + 1) + (PULSE_SAMPLES - 1) / 2 + n][j];
            }
        }
    }

    return 0;
}

// ******************************************************************************************************************************** 
// EOF
// ******************************************************************************************************************************** 