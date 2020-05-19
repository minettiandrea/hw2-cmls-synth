/*
  ==============================================================================

    Synth.h
    Created: 12 May 2020 2:23:34pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#pragma once
#include "Oscillator.h"
#include <array>

class Synth {
public:

    Synth();
    int numOscillators();
    double getOutputGain();
    double getFundamentalFrequency();
    void setOutputGain(double gainValue);
    void setOscGain(int osc_id, double gain);
    void setOscEnvelope(int osc_id, double a, double d, double s, double r);
    void setOscOffset(int osc_id, double offset);
    void setFoundamentalFrequency(double freq);
    void setAmplitude(float amp);
    void initialize(double sampleRate);
    void Synth::process(float*& channelDataL, float*& channelDataR, int samples);
    void startNote();
    void stopNote();

private:
    int nOsc = 4;
    Oscillator mainOsc;
    Oscillator secondaryOsc[3];
    std::array<Oscillator*, 4> oscillators;
    double outputGain;          //Main output volume controlled by the GUI. Can be any value in the range 0:1
};