/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MixerGui.h"
#include "EnvelopeGui.h"
#include "OffsetGui.h"
#include "OutputGui.h"
#include "CustomLookAndFeel.h"
#include <string.h>
#include <memory>
using namespace std;

//==============================================================================
/**
*/
class AddsynthAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    AddsynthAudioProcessorEditor (AddsynthAudioProcessor&);
    ~AddsynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AddsynthAudioProcessor& processor;

    MixerGui mixer;
    EnvelopeGui envelope[4];
    OffsetGui offsets;
    OutputGui output;

    Label mixerLabel;
    Label envelopeLabel;
    Label offsetsLabel;
    Label outputLabel;
    
    CustomLookAndFeel* customLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AddsynthAudioProcessorEditor)
};