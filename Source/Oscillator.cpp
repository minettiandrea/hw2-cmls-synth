/*
  ==============================================================================

    Oscillator.cpp
    Created: 12 May 2020 2:22:47pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#define _USE_MATH_DEFINES
#include "Oscillator.h"
#include <cmath>

void Oscillator::setFrequency(double frequencyValue)
{
	frequency = frequencyValue;
}

void Oscillator::setPhase(double phaseValue)
{
	phase = phaseValue;
}

void Oscillator::setSampleRate(double sampleRateValue) {
	sampleRate = sampleRateValue;
}

void Oscillator::setGain(double gainValue)
{
	gain = gainValue;
}

double Oscillator::getFrequency()
{
	return frequency;
}

double Oscillator::getPhase()
{
	return phase;
}

//Return the sine wave (gets called for each sample)
double Oscillator::getBlockSineWave(){

	double wave = gain*amplitude*(double)sin((double)phase);

	phase += (double)(M_PI * 2. * (frequency / sampleRate));
	if (phase > M_PI * 2.) phase -= M_PI * 2.;

	return wave;
}

double Oscillator::getGain()
{
	return gain;
}

void Oscillator::play()
{
	amplitude = 0.5;
}

void Oscillator::stop()
{
	amplitude = 0;
}


