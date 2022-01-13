#pragma once

// ================================================================================================================================================================================ //
//  Includes.	                                                                                                                                                                    //
// ================================================================================================================================================================================ //

#include <vector>
#include <complex>

// ================================================================================================================================================================================ //
//  Declerations.                                                                                                                                                                   //
// ================================================================================================================================================================================ //

// Generate a frequency ramp complex wave.
std::vector<std::complex<float>> generateLinearChirp(int nSamples, float bandwidth, float amplitude, unsigned samplingFreq, std::string window = "None");

// Generate a constant sine complex wave.
std::vector<std::complex<float>> generateConstSine(int nSamples, float frequency, float amplitude, unsigned samplingFreq, std::string window = "None");

// Generate a non linear frequency chirp.
std::vector<std::complex<float>> generateNonLinearChirp(int nSamples, float bandwidth, float amplitude, unsigned samplingFreq, std::string window = "None");

// ================================================================================================================================================================================ //
//  EOF.	                                                                                                                                                                        //
// ================================================================================================================================================================================ //

