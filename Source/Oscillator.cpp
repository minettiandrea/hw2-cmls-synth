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

void Oscillator::setFundamental(float frequencyValue)
{
	fundamental = frequencyValue;
}

void Oscillator::setFrequencyOffset(AudioParameterFloat* freeOffset, AudioParameterFloat* harmonicOffset, AudioParameterBool* isHarmonic)
{
	this->freeOffset = freeOffset;
	this->harmonicOffset = harmonicOffset;
	this->isHarmonic = isHarmonic;
}

void Oscillator::setPhase(double phaseValue)
{
	phase = phaseValue;
}

void Oscillator::setSampleRate(double sampleRateValue) {
	sampleRate = sampleRateValue;
}

void Oscillator::setGain(AudioParameterFloat* gainValue)
{
	gain = gainValue;
}

void Oscillator::setAmplitude(float amplitude)
{
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

//Return the sine wave (gets called for each sample)
float Oscillator::getBlockSineWave(){
	float wave = this->gain->get()*envelope.getNextSample()*sin(phase)*amplitude;
	phase += (M_PI * 2.0f * ((this->fundamental + this->offset()) / (float) sampleRate));
	if (phase > M_PI * 2.0f) phase -= M_PI * 2.0f;

	return wave;
}

void Oscillator::play()
{
	envelope.noteOn();
}

void Oscillator::stop()
{
	envelope.noteOff();
}

void Oscillator::init(double sr)
{
	phase = 0.0f;
	sampleRate = sr;
	envelope.setSampleRate(sr);
}

float Oscillator::offset()
{

	float result;
	if (this->isHarmonic->get()) {
		result = this->fundamental * this->harmonicOffset->get();
	}
	else {
		result = this->freeOffset->get();
	}
	return result;
}




