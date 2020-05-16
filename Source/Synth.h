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
    void setOutputGain(double gainValue);
    void setOscGain(int osc_id, double gain);
    void setFoundamentalFrequency(double freq);
    void initialize(double sampleRate);
    void process(AudioBuffer<float>& buffer);
    void startNote();
    void stopNote();

private:
    int nOsc = 4;
    Oscillator mainOsc;
    Oscillator secondaryOsc[3];
    std::array<Oscillator*, 4> oscillators;
    double outputGain;          //Main output volume controlled by the GUI. Can be any value in the range 0:1
};