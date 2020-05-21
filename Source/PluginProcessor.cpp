/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/


#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <iostream>
using namespace std;

//==============================================================================
AddsynthAudioProcessor::AddsynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    for (auto& p : state.getParameters()) {
        addParameter(p);
    }
}

AddsynthAudioProcessor::~AddsynthAudioProcessor()
{
}

//==============================================================================
const String AddsynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AddsynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AddsynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AddsynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AddsynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AddsynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AddsynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AddsynthAudioProcessor::setCurrentProgram (int index)
{
}

const String AddsynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void AddsynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void AddsynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    notes.clear();
    this->sampleRate = sampleRate;
}

void AddsynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AddsynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void AddsynthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    
    //MIDI messages managment
    MidiMessage m;
    int time;
    for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);) {
        DBG(m.getDescription() + " Note:" +  to_string(m.getNoteNumber()));
        int note = m.getNoteNumber();
        if (m.isPitchWheel()) {
            for (auto& kv : notes) {
                kv.second->setFoundamentalFrequency(m.getMidiNoteInHertz(kv.first) + (double)m.getPitchWheelValue() / 16384.0);
            }
        } else if (m.isNoteOn()) {
            
            if (notes.count(note) == 0) {
                DBG("Create new synth for note: " + to_string(m.getNoteNumber()));
                notes[note] = std::make_unique<Synth>(&state);
                notes[note]->initialize(sampleRate);
            }
            notes[note]->setAmplitude(m.getFloatVelocity());
            notes[note]->setFoundamentalFrequency(m.getMidiNoteInHertz(m.getNoteNumber()));
            notes[note]->startNote();
        } else if (m.isNoteOff()) {
            notes[note]->stopNote();
        }
    }
    

    float* channelDataL = buffer.getWritePointer(0);
    float* channelDataR = buffer.getWritePointer(1);
    int samples = buffer.getNumSamples();
    for (int i = 0; i < buffer.getNumSamples(); ++i) {
        channelDataL[i] = 0;
        channelDataR[i] = 0;
    }

    //Process the sound
    for (auto& kv : notes) {
        kv.second->process(channelDataL, channelDataR, samples);
    }

    //synth.process(channelDataL, channelDataR, samples);
}

//==============================================================================
bool AddsynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* AddsynthAudioProcessor::createEditor()
{
    return new AddsynthAudioProcessorEditor (*this);
}

//==============================================================================
void AddsynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void AddsynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

State* AddsynthAudioProcessor::getState()
{
    return &state;
}



//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AddsynthAudioProcessor();
}




