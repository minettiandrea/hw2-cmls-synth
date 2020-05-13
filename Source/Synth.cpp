/*
  ==============================================================================

    Synth.cpp
    Created: 12 May 2020 2:24:20pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#include "Synth.h"

Oscillator Synth::getMainOsc()
{
	return mainOsc;
}

Oscillator* Synth::getSecondaryOsc()
{
    return secondaryOsc;
}

//Initialize all oscillators with standard values and setting the sample rate
void Synth::initialize(double sr)
{
    mainOsc.setAmplitude(0);
    mainOsc.setFrequency(440);
    mainOsc.setPhase(0);
    mainOsc.setSampleRate(sr);

    for (int i = 0; i < 3; i++) {
        secondaryOsc[i].setAmplitude(0);
        secondaryOsc[i].setFrequency(440);
        secondaryOsc[i].setPhase(0);
        secondaryOsc[i].setSampleRate(sr);
    }

}

//Process the sound for all the samples in buffer
void Synth::process(AudioBuffer<float>& buffer)
{
    float* channelDataL = buffer.getWritePointer(0);
    float* channelDataR = buffer.getWritePointer(1);

    for (int i = 0; i < buffer.getNumSamples(); ++i) {
        channelDataL[i] = mainOsc.getBlockSineWave();     //to play the slave oscillators just add their getBlockSineWave() return arguments
        channelDataR[i] = channelDataL[i];
    }
}

//Set values of the played note
void Synth::startNote(double freq)
{
    mainOsc.setAmplitude(1);
    mainOsc.setFrequency(freq);
    //set the frequency for the slave oscillators and amplitude to 1

}

void Synth::stopNote()
{
    mainOsc.setAmplitude(0);
    //same for slave oscillators
}
