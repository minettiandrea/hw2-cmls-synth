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
#include <memory>
#include "State.h"

class Synth {
public:

    Synth(State* state);
    int numOscillators();
    void setFoundamentalFrequency(double freq);
    void setAmplitude(float amp);
    void initialize(double sampleRate);
    void Synth::process(float*& channelDataL, float*& channelDataR, int samples);
    void startNote();
    void stopNote();
    bool active();

private:
    State* state;
    int nOsc = 4;
    std::array<std::unique_ptr<Oscillator>, 4> oscillators;
};