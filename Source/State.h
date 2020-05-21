/*
  ==============================================================================

    State.h
    Created: 19 May 2020 10:02:47am
    Author:  Andrea Minetti

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

#include <array>

class EnvelopeState {
public:
    EnvelopeState(std::string id);
    ~EnvelopeState();
    void setAttack(float a);
    void setDecay(float d);
    void setSustain(float s);
    void setRelease(float r);
    AudioParameterFloat* getAttack();
    AudioParameterFloat* getDecay();
    AudioParameterFloat* getSustain();
    AudioParameterFloat* getRelease();
    std::vector<AudioProcessorParameter*> getParameters();
private:
    AudioParameterFloat* attack;
    AudioParameterFloat* decay;
    AudioParameterFloat* sustain;
    AudioParameterFloat* release;
};

class MixerState {
public:
    MixerState();
    ~MixerState();
    std::array<AudioParameterFloat*, 4> getParameters();
    AudioParameterFloat* get(int i);
    void set(int i, float v);
private:
    std::array<AudioParameterFloat*,4> mix = std::array<AudioParameterFloat*, 4>();
};

class OffsetState {
public:
    OffsetState();
    ~OffsetState();
    void setHarmonic(bool h);
    AudioParameterFloat* getFree(int i);
    AudioParameterFloat* getHarmonics(int i);
    AudioParameterBool* isHarmonic();
    void setFree(int i, float v);
    void setHarmonics(int i, float v);
    std::vector<AudioProcessorParameter*> getParameters();
private:
    AudioParameterBool* harmonic;
    std::array<AudioParameterFloat*, 4> free = std::array<AudioParameterFloat*, 4>();
    std::array<AudioParameterFloat*, 4> harmonics = std::array<AudioParameterFloat*, 4>();
};

class State {
public:
    State();
    ~State();

    EnvelopeState* getEnvelope(int i);
    MixerState* getMixer();
    OffsetState* getOffset();
    AudioParameterFloat* getOutput();
    void setOutput(float o);
    std::vector<AudioProcessorParameter*> getParameters();
private:
    AudioParameterFloat* output;
    std::array<EnvelopeState*, 4> envelope;
    MixerState* mixer;
    OffsetState* offset;

};

