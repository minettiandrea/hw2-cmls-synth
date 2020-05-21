/*
  ==============================================================================

    Synth.cpp
    Created: 12 May 2020 2:24:20pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#include "Synth.h"

Synth::Synth(State* state)
{
    this->state = state;
    for (int i = 0; i < 4; i++) {
        oscillators[i] = std::make_unique<Oscillator>();
        oscillators[i]->setGain(state->getMixer()->get(i));
        oscillators[i]->setFrequencyOffset(state->getOffset()->getFree(i), state->getOffset()->getHarmonics(i), state->getOffset()->isHarmonic());
    }
}

int Synth::numOscillators()
{
    return nOsc;
}




//Set the frequency of the oscillator (the offset get applied in the setFrequency method)
void Synth::setFoundamentalFrequency(double freq)
{
    for (auto &osc : oscillators) {
        osc->setFundamental(freq);
    }
}

void Synth::setAmplitude(float amp)
{
    for (auto &osc : oscillators) {
        osc->setAmplitude(amp);
    }
}

//Initialize all oscillators: 
//Frequency: main oscillator with 440 and the secondaries with multiple integers of 440
//Gain: 1
//Envelope: 0.1, 0.1, 1, 0.2
//Output Gain: 0.5
void Synth::initialize(double sampleRate)
{
    for (auto &osc : oscillators) {
        osc->init(sampleRate);
    }

}

//Process the sound for all the samples in buffer
void Synth::process(float*& channelDataL, float*& channelDataR, int samples)
{

    for (int i = 0; i < samples; ++i) {
        float channelData = 0.0f;
        for (auto &o : oscillators) {
            channelData += o->getBlockSineWave();
        }
        auto synthChannelData = this->state->getOutput()->get() * channelData;
        channelDataL[i] = channelDataL[i] + synthChannelData;
        channelDataR[i] = channelDataR[i] + synthChannelData;
    }
}

//Set values of the played note
void Synth::startNote()
{
    for (int i = 0; i < 4; i++) {
        oscillators[i]->setEnvelopeParameters(
            state->getEnvelope(i)->getAttack()->get(),
            state->getEnvelope(i)->getDecay()->get(),
            state->getEnvelope(i)->getSustain()->get(),
            state->getEnvelope(i)->getRelease()->get()
           );
        oscillators[i]->play();
    }
}

void Synth::stopNote()
{
    for (auto &osc : oscillators) {
        osc->stop();
    }
}
