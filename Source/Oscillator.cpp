/*
  ==============================================================================

    Oscillator.cpp
    Created: 12 May 2020 2:22:47pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#include "Oscillator.h"
#include <cmath>

#ifndef M_PI
#define M_PI (3.14159265)
#endif

void Oscillator::setFrequency(double value)
{
	frequency = value;
}

void Oscillator::setAmplitude(double value)
{
	amplitude = value;
}

void Oscillator::setPhase(double value)
{
	phase = value;
}

void Oscillator::setSampleRate(double sr) {
	sample_rate = sr;
}

double Oscillator::getFrequency()
{
	return frequency;
}

double Oscillator::getAmplitude()
{
	return amplitude;
}

double Oscillator::getPhase()
{
	return phase;
}

//Return the sine wave (gets called for each sample)
double Oscillator::getBlockSineWave(){

	double wave = amplitude*(double)sin((double)phase);

	phase += (double)(M_PI * 2. * (frequency / sample_rate));
	if (phase > M_PI * 2.) phase -= M_PI * 2.;

	return wave;
}


