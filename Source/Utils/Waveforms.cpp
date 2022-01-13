// ================================================================================================================================================================================ //
//  Includes.                                                                                                                                                                       //
// ================================================================================================================================================================================ //

#include <iostream>
#include "Waveforms.h"
#include <string>
#include <vector>
#include <complex>
#include <math.h>
#include "../External/Misc/ConsoleColor.h"

// ================================================================================================================================================================================ //
//  Constants.                                                                                                                                                                      //
// ================================================================================================================================================================================ //

const float PI = 3.14159265359;
const std::complex<float> i(0, 1);

// ================================================================================================================================================================================ //
//  Frequency ramp.                                                                                                                                                                 //
// ================================================================================================================================================================================ //

std::vector<std::complex<float>> generateLinearChirp(int nSamples, float bandwidth, float amplitude, unsigned samplingFreq, std::string window)
{
	// --------------------- //
	//  G E N E R A T I O N  //
	// --------------------- //

	std::vector<std::complex<float>> wave(nSamples);

	// Ensure nSamples is odd.
	if (nSamples % 2 == 0) { std::cout << red << "\n[WAVEFORM] [ERROR]: " << white << "nSamples is not an odd number.\n"; }

	else
	{
		// Calculate wave parameters.
		float freqGradient = bandwidth / ((float)nSamples - 1.f);
		int index = 0;
		float FREQ;
		// Populate wave vector.
		for (int n = floor(-(nSamples - 1) / 2); n <= ceil((nSamples - 1) / 2); n++)
		{
			FREQ = ((freqGradient * index) - (bandwidth / 2)) / samplingFreq;
			wave[index] = std::exp(n * -2 * PI * FREQ * i);
			index++;
		}
	}

	// ------------------- //
	//  W I N D O W I N G  //
	// ------------------- //

	// [NOTE]: Window calculations may change with even and odd lengths?
	//		   ATM even waveforms cannot be generated.

	// No window.
	if(window=="None")
		return wave;

	// Blackman window.
	if (window == "Blackman")
	{
		std::vector<float> blackmanWindow(nSamples);
		for (int n = 0; n < nSamples; n++)
			blackmanWindow[n] = 0.42 - 0.5 * std::cos((2 * PI * n) / (nSamples - 1)) + 0.08 * std::cos(((4 * PI * n) / (nSamples - 1)));
		for (int n = 0; n < nSamples; n++)
			wave[n] *= blackmanWindow[n];
	}

	// Hamming window.
	else if (window == "Hamming")
	{
		std::vector<float> hammingWindow(nSamples);
		int min = -std::floor(nSamples / 2);
		int max = std::floor(nSamples / 2);
		for (int n = min; n <= max; n++)
			hammingWindow[n-min] = 0.54 + 0.46 * std::cos( ( 2 * PI * n ) / nSamples );
		for (int n = 0; n < nSamples; n++)
			wave[n] *= hammingWindow[n];
	}

	// Return windowed wave.
	return wave;
}

// ================================================================================================================================================================================ //
//  Constant sine wave.                                                                                                                                                                 //
// ================================================================================================================================================================================ //

std::vector<std::complex<float>> generateConstSine(int nSamples, float frequency, float amplitude, unsigned samplingFreq, std::string window)
{
	// --------------------- //
	//  G E N E R A T I O N  //
	// --------------------- //

	std::vector<std::complex<float>> wave(nSamples);

	// Ensure nSamples is odd.
	if (nSamples % 2 == 0) { std::cout << red << "\n[WAVEFORM] [ERROR]: " << white << "nSamples is not an odd number.\n"; }

	else
	{
		// Populate wave vector.
		for (int n = 0; n < nSamples; n++)
		{
			wave[n] = std::exp(n * -2 * PI * frequency * i);
		}
	}

	// ------------------- //
	//  W I N D O W I N G  //
	// ------------------- //

	// [NOTE]: Window calculations may change with even and odd lengths?
	//		   ATM even waveforms cannot be generated.

	// No window.
	if (window == "None")
		return wave;

	// Blackman window.
	if (window == "Blackman")
	{
		std::vector<float> blackmanWindow(nSamples);
		for (int n = 0; n < nSamples; n++)
			blackmanWindow[n] = 0.42 - 0.5 * std::cos((2 * PI * n) / (nSamples - 1)) + 0.08 * std::cos(((4 * PI * n) / (nSamples - 1)));
		for (int n = 0; n < nSamples; n++)
			wave[n] *= blackmanWindow[n];
	}

	// Hamming window.
	else if (window == "Hamming")
	{
		std::vector<float> hammingWindow(nSamples);
		int min = -std::floor(nSamples / 2);
		int max = std::floor(nSamples / 2);
		for (int n = min; n <= max; n++)
			hammingWindow[n - min] = 0.54 + 0.46 * std::cos((2 * PI * n) / nSamples);
		for (int n = 0; n < nSamples; n++)
			wave[n] *= hammingWindow[n];
	}

	// Return windowed wave.
	return wave;
}

// ================================================================================================================================================================================ //
//  Non Linear Frequency Chirp.                                                                                                                                                     //
// ================================================================================================================================================================================ //

std::vector<std::complex<float>> generateNonLinearChirp(int nSamples, float bandwidth, float amplitude, unsigned samplingFreq, std::string window)
{
	// --------------------- //
	//  G E N E R A T I O N  //
	// --------------------- //
	
	// The transmission interval.
	float t_i = (float)nSamples / (float)samplingFreq; 
	// The wave.
	std::vector<std::complex<float>> wave(nSamples);
	// The sidelobe paramter.
	int delta = 50e6;

	// Populate wave vector.
	for (int n = 0; n < nSamples; n++)
	{
		//  Current time.
		float t = n / samplingFreq;  
		// Calculate components of the NLFM equation.
		float a = ( t_i * std::sqrt(delta^2 + 4) ) / (2 * delta);
		float b = ( t_i * t_i * (delta^2+4) ) / ( 4 * delta^2 );
		float c = ( t - ( t_i / 2 ) ) * (t - (t_i / 2));
		float PHASE = a - std::sqrt(b - c);
		wave[n] = amplitude * std::exp(2 * PI * i * PHASE * bandwidth);
	}

	// ------------------- //
	//  W I N D O W I N G  //
	// ------------------- //

	// [NOTE]: Window calculations may change with even and odd lengths?
	//		   ATM even waveforms cannot be generated.

	// No window.
	if (window == "None")
		return wave;

	// Blackman window.
	if (window == "Blackman")
	{
		std::vector<float> blackmanWindow(nSamples);
		for (int n = 0; n < nSamples; n++)
			blackmanWindow[n] = 0.42 - 0.5 * std::cos((2 * PI * n) / (nSamples - 1)) + 0.08 * std::cos(((4 * PI * n) / (nSamples - 1)));
		for (int n = 0; n < nSamples; n++)
			wave[n] *= blackmanWindow[n];
	}

	// Hamming window.
	else if (window == "Hamming")
	{
		std::vector<float> hammingWindow(nSamples);
		int min = -std::floor(nSamples / 2);
		int max = std::floor(nSamples / 2);
		for (int n = min; n <= max; n++)
			hammingWindow[n - min] = 0.54 + 0.46 * std::cos((2 * PI * n) / nSamples);
		for (int n = 0; n < nSamples; n++)
			wave[n] *= hammingWindow[n];
	}

	// Return windowed wave.
	return wave;
}

// ================================================================================================================================================================================ //
//  EOF.	                                                                                                                                                                        //
// ================================================================================================================================================================================ //
