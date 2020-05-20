/*
  ==============================================================================

    State.h
    Created: 19 May 2020 10:02:47am
    Author:  Andrea Minetti

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"

class State {
public:
    State(AddsynthAudioProcessor* processor);
    ~State();

    EnvelopeState* getEnvelope();
    MixerState* getMixer();
    OffsetState* getOffset();
    float getOutput();
    void setOutput(float o);

private:
    float output;
    EnvelopeState* envelope[4];
    MixerState* mixer;
    OffsetState* offset;

};

class EnvelopeState {
public:
    EnvelopeState(AddsynthAudioProcessor* processor);
};

class MixerState {
public:
    MixerState(AddsynthAudioProcessor* processor);
};

class OffsetState {
public:
    OffsetState(AddsynthAudioProcessor* processor);
};