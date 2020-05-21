/*
  ==============================================================================

    State.cpp
    Created: 19 May 2020 10:02:47am
    Author:  Andrea Minetti

  ==============================================================================
*/

#include "State.h"

State::State()
{
    this->envelope[0] = new EnvelopeState("osc1");
    this->envelope[1] = new EnvelopeState("osc2");
    this->envelope[2] = new EnvelopeState("osc3");
    this->envelope[3] = new EnvelopeState("osc4");
    this->mixer = new MixerState();
    this->offset = new OffsetState();
    this->output = new AudioParameterFloat("output", "Output", 0.0f, 1.0f, 0.5f);
}

State::~State()
{
    DBG("~State");
    //delete this->output;
    delete this->envelope[0];
    delete this->envelope[1];
    delete this->envelope[2];
    delete this->envelope[3];
    delete this->mixer;
    //delete this->offset;
}

EnvelopeState* State::getEnvelope(int i)
{
	return this->envelope.at(i);
}

MixerState* State::getMixer()
{
    return this->mixer;
}

OffsetState* State::getOffset()
{
    return this->offset;
}

AudioParameterFloat* State::getOutput()
{
    return this->output;
}

void State::setOutput(float o)
{
    this->output->setValueNotifyingHost(o);
}

std::vector<AudioProcessorParameter*> State::getParameters()
{
    auto params = std::vector<AudioProcessorParameter*>();
    for (auto& e : this->envelope) {
        for (auto& p : e->getParameters()) {
            params.push_back(p);
        }
    }
    for (auto& p : this->mixer->getParameters()) {
        params.push_back(p);
    }
    for (auto& p : this->offset->getParameters()) {
        params.push_back(p);
    }
    params.push_back(output);
    return params;
}

EnvelopeState::EnvelopeState(std::string id)
{
    this->attack    = new AudioParameterFloat(id + "_attack", id + " Attack", 0.0f, 1.0f, 0.1f);
    this->decay     = new AudioParameterFloat(id + "_decay", id + " Decay", 0.0f, 1.0f, 0.1f);
    this->sustain   = new AudioParameterFloat(id + "_sustain", id + " Sustain", 0.0f, 1.0f, 1.0f);
    this->release   = new AudioParameterFloat(id + "_release", id + " Release", 0.0f, 1.0f, 0.2f);
}

EnvelopeState::~EnvelopeState()
{
    DBG("~EnvelopeState");
    //delete this->attack;
    //delete this->decay;
    //delete this->sustain;
    //delete this->release;
}

void EnvelopeState::setAttack(float a)
{
    this->attack->setValueNotifyingHost(a);
}

void EnvelopeState::setDecay(float d)
{
    this->decay->setValueNotifyingHost(d);
}

void EnvelopeState::setSustain(float s)
{
    this->decay->setValueNotifyingHost(s);
}

void EnvelopeState::setRelease(float r)
{
    this->decay->setValueNotifyingHost(r);
}

AudioParameterFloat* EnvelopeState::getAttack()
{
    return this->attack;
}

AudioParameterFloat* EnvelopeState::getDecay()
{
    return this->decay;
}

AudioParameterFloat* EnvelopeState::getSustain()
{
    return this->sustain;
}

AudioParameterFloat* EnvelopeState::getRelease()
{
    return this->release;
}

std::vector<AudioProcessorParameter*> EnvelopeState::getParameters()
{
    auto params = std::vector<AudioProcessorParameter*>();
    params.push_back(this->attack);
    params.push_back(this->decay);
    params.push_back(this->sustain);
    params.push_back(this->release);
    return params;
}

MixerState::MixerState()
{
    for (int i = 1; i <= 4; i++) {
        mix[(i-1)] = new AudioParameterFloat("osc"+std::to_string(i)+"_mix", "OSC"+ std::to_string(i) +" Mix", 0.0f, 1.0f, 1.0f);
    }
}

MixerState::~MixerState()
{
    DBG("~MixerState");
    //delete mix[0];
    //delete mix[1];
    //delete mix[2];
    //delete mix[3];
}

std::array<AudioParameterFloat*, 4> MixerState::getParameters()
{
    return mix;
}

void MixerState::set(int i,float v)
{
    DBG("Changed free offset state to:" + std::to_string(v));
    mix[i]->setValueNotifyingHost(v);
    DBG("Reading offset state:" + std::to_string(mix[i]->get()));
}

AudioParameterFloat* MixerState::get(int i)
{
    return mix[i];
}

OffsetState::OffsetState()
{
    for (int i = 0; i < 4; i++) {
        free[i] = new AudioParameterFloat("osc" + std::to_string(i+1) + "_free", "OSC" + std::to_string(i+1) + " Offset free", 0.0f, 1000.0f, 0.0f);
    }
    for (int i = 0; i < 4; i++) {
        harmonics[i] = new AudioParameterFloat("osc" + std::to_string(i+1) + "_harmonic", "OSC" + std::to_string(i+1) + " Offset harmonic", 0.0f, 10.0f, 0.0f);
    }
    harmonic = new AudioParameterBool("harmonic", "Harmonic", false);
}

OffsetState::~OffsetState()
{
    /*delete free[0];
    delete free[1];
    delete free[2];
    delete free[3];
    delete harmonics[0];
    delete harmonics[1];
    delete harmonics[2];
    delete harmonics[3];
    delete harmonic;*/
}

AudioParameterFloat* OffsetState::getFree(int i)
{
    return free[i];
}

AudioParameterFloat* OffsetState::getHarmonics(int i)
{
    return harmonics[i];
}

void OffsetState::setHarmonic(bool h)
{
    this->harmonic->setValueNotifyingHost(h);
}

AudioParameterBool* OffsetState::isHarmonic()
{
    return harmonic;
}

void OffsetState::setHarmonics(int i, float v)
{
    harmonics[i]->setValueNotifyingHost(v / 10.0f);
}

void OffsetState::setFree(int i, float v)
{
    free[i]->setValueNotifyingHost(v / 1000.0f);
}

std::vector<AudioProcessorParameter*> OffsetState::getParameters()
{
    auto params = std::vector<AudioProcessorParameter*>();
    params.push_back(harmonic);
    for (auto p : free) {
        params.push_back(p);
    }
    for (auto p : harmonics) {
        params.push_back(p);
    }
    return params;
}
