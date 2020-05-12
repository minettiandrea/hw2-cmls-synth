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
	void setFrequency(double value);
	void setAmplitude(double value);
	void setPhase(double value);
	void setSampleRate(double sr);
	double getFrequency();
	double getAmplitude();
	double getPhase();
	double getBlockSineWave();

private:
	double frequency;
	double amplitude;
	double phase;
	double sample_rate;
};

