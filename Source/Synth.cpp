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

double Synth::getOutputGain()
{
	return outputGain;
}

void Synth::setOutputGain(double gainValue)
{
    outputGain = gainValue;
}

//Initialize all oscillators with frequency 440 and gain 1 and setting the sample rate.
//Set the main output volume at 0.5
void Synth::initialize(double sampleRate)
{
    mainOsc.stop();
    mainOsc.setFrequency(440);
    mainOsc.setPhase(0);
    mainOsc.setSampleRate(sampleRate);
    mainOsc.setGain(1);

    for (int i = 0; i < 3; i++) {
        secondaryOsc[i].stop();
        secondaryOsc[i].setFrequency(440);
        secondaryOsc[i].setPhase(0);
        secondaryOsc[i].setSampleRate(sampleRate);
        secondaryOsc[i].setGain(1);
    }

    outputGain = 0.5;
}

//Process the sound for all the samples in buffer
void Synth::process(AudioBuffer<float>& buffer)
{
    float* channelDataL = buffer.getWritePointer(0);
    float* channelDataR = buffer.getWritePointer(1);

    for (int i = 0; i < buffer.getNumSamples(); ++i) {
        channelDataL[i] = outputGain*(mainOsc.getBlockSineWave());     //to play the secondary oscillators just add their getBlockSineWave() return arguments
        channelDataR[i] = channelDataL[i];
    }
}

//Set values of the played note
void Synth::startNote(double freq)
{
    mainOsc.play();
    mainOsc.setFrequency(freq);
    //set the frequency for the secondary oscillators and call play()

}

void Synth::stopNote()
{
    mainOsc.stop();
    //same for secondary oscillators
}
