/*
  ==============================================================================

    Synth.h
    Created: 12 May 2020 2:23:34pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Oscillator.h"

class Synth {
public:
    Oscillator getMainOsc();
    Oscillator* getSecondaryOsc();
    void initialize(double sampleRate);
    void process(AudioBuffer<float>& buffer);
    void startNote(double freq);
    void stopNote();

private:
    Oscillator mainOsc;
    Oscillator secondaryOsc[3];
    double outputGain;
};