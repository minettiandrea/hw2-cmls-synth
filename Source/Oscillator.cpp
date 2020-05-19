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

void Oscillator::setFundamental(double frequencyValue)
{
	fundamental = frequencyValue;
	refreshFrequency();
}

void Oscillator::setFrequencyOffset(double offsetValue)
{
	frequencyOffset = offsetValue;
	refreshFrequency();
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

void Oscillator::setAmplitude(float amplitude)
{
	DBG("Oscillator::setAmplitude: " + std::to_string(amplitude));
	this->amplitude = amplitude;
}

void Oscillator::setEnvelopeParameters(double attack, double decay, double sustain, double release)
{
	envelopeParameters.attack = attack;
	envelopeParameters.decay = decay;
	envelopeParameters.sustain = sustain;
	envelopeParameters.release = release;

	envelope.setParameters(envelopeParameters);
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
	double wave = gain*envelope.getNextSample()*(double)sin((double)phase)*amplitude;

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
	envelope.noteOn();
}

void Oscillator::stop()
{
	envelope.noteOff();
}

void Oscillator::init(double sr, double freq)
{
	stop();
	fundamental = freq;
	frequencyOffset = 0;
	refreshFrequency();
	phase = 0;
	sampleRate = sr;
	gain = 1;
	amplitude = 0.5;
	envelope.setSampleRate(sr);
	setEnvelopeParameters(0.1, 0.1, 1, 0.1);
}

void Oscillator::refreshFrequency()
{
	frequency = fundamental + frequencyOffset;
}



