/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class AddsynthAudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener
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

    Slider outputGain;
    Label outputGainLabel;
    Slider oscGains[4];
    Label oscGainsLabels[4];

    void sliderValueChanged(Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AddsynthAudioProcessorEditor)
};
