/*
  ==============================================================================

    Synth.cpp
    Created: 12 May 2020 2:24:20pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#include "Synth.h"

Oscillator* Synth::getMainOsc()
{
	return &mainOsc;
}

Oscillator* Synth::getSecondaryOsc()
{
    return secondaryOsc;
}

double Synth::getOutputGain()
{
	return outputGain;
}

void Synth::setOutputGain(double gainValue)
{
    outputGain = gainValue;
}

//Initialize all oscillators: 
//Frequency: main oscillator with 440 and the secondaries with multiple integers of 440
//Gain: 1
//Envelope: 0.1, 0.1, 1, 0.2
//Output Gain: 0.5
void Synth::initialize(double sampleRate)
{
    mainOsc.init(sampleRate, 440);

    for (int i = 0; i < 3; i++) {
        secondaryOsc[i].init(sampleRate, (i + 2) * 440);
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
void Synth::startNote(double freq)
{
    mainOsc.play(freq);
    for (int i = 0; i < 3; i++) {
        secondaryOsc[i].play(double(i + 2) * freq);
    }
}

void Synth::stopNote()
{
    mainOsc.stop();
    for (int i = 0; i < 3; i++) {
        secondaryOsc[i].stop();
    }}
