/*
  ==============================================================================

    Oscillator.h
    Created: 12 May 2020 2:21:44pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#pragma once


class Oscillator {
public:
	void setFrequency(double frequencyValue);
	void setPhase(double phaseValue);
	void setSampleRate(double sampleRateValue);
	void setGain(double gainValue);
	double getFrequency();
	double getPhase();
	double getBlockSineWave();
	double getGain();
	void play();
	void stop();

private:
	double frequency;
	float amplitude;		//Sinewave amplitude, controlled only by MIDI key press. Can be 0 (note off) or 0.5 (note on)
	double phase;
	double sampleRate;
	double gain;		//Oscillator volume, controlled only by the GUI. Can be any value in the range 0:1
};

