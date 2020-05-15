/*
  ==============================================================================

    Synth.h
    Created: 12 May 2020 2:23:34pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#pragma once
#include "Oscillator.h"

class Synth {
public:
    Oscillator* getMainOsc();
    Oscillator* getSecondaryOsc();
    double getOutputGain();
    void setOutputGain(double gainValue);
    void initialize(double sampleRate);
    void process(AudioBuffer<float>& buffer);
    void startNote(double freq);
    void stopNote();

private:
    Oscillator mainOsc;
    Oscillator secondaryOsc[3];
    double outputGain;          //Main output volume controlled by the GUI. Can be any value in the range 0:1
};