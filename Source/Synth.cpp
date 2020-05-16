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

void Synth::setFoundamentalFrequency(double freq) // here goes the logic for the frequency offset
{
    mainOsc.setFrequency(freq);
    for (int i = 0; i < 3; i++) {
        secondaryOsc[i].setFrequency(double(i + 2) * freq);
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
void Synth::process(AudioBuffer<float>& buffer)
{
    float* channelDataL = buffer.getWritePointer(0);
    float* channelDataR = buffer.getWritePointer(1);

    for (int i = 0; i < buffer.getNumSamples(); ++i) {
        channelDataL[i] = outputGain*(mainOsc.getBlockSineWave() + secondaryOsc[0].getBlockSineWave() + secondaryOsc[1].getBlockSineWave() + secondaryOsc[2].getBlockSineWave());
        channelDataR[i] = channelDataL[i];
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
