/*
  ==============================================================================

    Oscillator.h
    Created: 12 May 2020 2:21:44pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Oscillator {
public:
	void setFundamental(float frequency);
	void setFrequencyOffset(AudioParameterFloat* freeOffset, AudioParameterFloat* harmonicOffset, AudioParameterBool* isHarmonic);
	void setPhase(double phaseValue);
	void setSampleRate(double sampleRateValue);
	void setGain(AudioParameterFloat* gain);
	void setAmplitude(float amplitude);
	void setEnvelopeParameters(double attack, double decay, double sustain, double release);
	float getBlockSineWave();
	void play();
	void stop();
	void init(double sr);

private:
	float fundamental;
	AudioParameterFloat* freeOffset;
	AudioParameterFloat* harmonicOffset;
	AudioParameterBool* isHarmonic;
	float amplitude;		//Sinewave amplitude, controlled only by MIDI key press. Can be 0 (note off) or 0.5 (note on)
	float phase;
	double sampleRate;
	AudioParameterFloat* gain;		//Oscillator volume, controlled only by the GUI. Can be any value in the range 0:1
	ADSR envelope;
	ADSR::Parameters envelopeParameters;

	float offset();
};

