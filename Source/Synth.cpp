/*
  ==============================================================================

    Synth.cpp
    Created: 12 May 2020 2:24:20pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#include "Synth.h"

Oscillator Synth::getMasterOsc()
{
	return masterOsc;
}

Oscillator* Synth::getSlaveOsc()
{
    return slaveOsc;
}

//Initialize all oscillators with standard values and setting the sample rate
void Synth::initialize(double sr)
{
    masterOsc.setAmplitude(0);
    masterOsc.setFrequency(440);
    masterOsc.setPhase(0);
    masterOsc.setSampleRate(sr);

    for (int i = 0; i < 3; i++) {
        slaveOsc[i].setAmplitude(0);
        slaveOsc[i].setFrequency(440);
        slaveOsc[i].setPhase(0);
        slaveOsc[i].setSampleRate(sr);
    }

}

//Process the sound for all the samples in buffer
void Synth::process(AudioBuffer<float>& buffer)
{
    float* channelDataL = buffer.getWritePointer(0);
    float* channelDataR = buffer.getWritePointer(1);

    for (int i = 0; i < buffer.getNumSamples(); ++i) {
        channelDataL[i] = masterOsc.getBlockSineWave();     //to play the slave oscillators just add their getBlockSineWave() return arguments
        channelDataR[i] = channelDataL[i];
    }
}

//Set values of the played note
void Synth::startNote(double freq)
{
    masterOsc.setAmplitude(1);
    masterOsc.setFrequency(freq);
    //set the frequency for the slave oscillators and amplitude to 1

}

void Synth::stopNote()
{
    masterOsc.setAmplitude(0);
    //same for slave oscillators
}
