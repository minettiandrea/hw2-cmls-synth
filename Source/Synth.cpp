/*
  ==============================================================================

    Synth.cpp
    Created: 12 May 2020 2:24:20pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#include "Synth.h"

Synth::Synth()
{
    this->oscillators = { &mainOsc,&secondaryOsc[0],&secondaryOsc[1],&secondaryOsc[2] };
}

int Synth::numOscillators()
{
    return nOsc;
}

double Synth::getOutputGain()
{
	return outputGain;
}

void Synth::setOutputGain(double gainValue)
{
    outputGain = gainValue;
}

void Synth::setOscGain(int osc_id, double gain)
{
    oscillators[osc_id]->setGain(gain);
}

void Synth::setOscEnvelope(int osc_id, double a, double d, double s, double r)
{
    oscillators[osc_id]->setEnvelopeParameters(a, d, s, r);
}

void Synth::setOscOffset(int osc_id, double offset)
{
    oscillators[osc_id]->setFrequencyOffset(offset);
}

//Set the frequency of the oscillator (the offset get applied in the setFrequency method)
void Synth::setFoundamentalFrequency(double freq)
{
    for (auto osc : oscillators) {
        osc->setFundamental(freq);
    }
}

void Synth::setAmplitude(float amp)
{
    DBG("Synth::setAmplitude: " + std::to_string(amp));
    for (auto osc : oscillators) {
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
    mainOsc.init(sampleRate, 440);

    for (auto osc : oscillators) {
        osc->init(sampleRate, 440);
    }

    outputGain = 0.5;
}

//Process the sound for all the samples in buffer
void Synth::process(float*& channelDataL, float*& channelDataR, int samples)
{


    for (int i = 0; i < samples; ++i) {
        auto synthChannelData = outputGain * (mainOsc.getBlockSineWave() + secondaryOsc[0].getBlockSineWave() + secondaryOsc[1].getBlockSineWave() + secondaryOsc[2].getBlockSineWave());
        channelDataL[i] = channelDataL[i] + synthChannelData;
        channelDataR[i] = channelDataR[i] + synthChannelData;
    }
}

//Set values of the played note
void Synth::startNote()
{
    for (auto osc : oscillators) {
        osc->play();
    }
}

void Synth::stopNote()
{
    for (auto osc : oscillators) {
        osc->stop();
    }
}
