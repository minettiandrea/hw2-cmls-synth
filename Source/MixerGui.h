/*
  ==============================================================================

    MixerGui.h
    Created: 17 May 2020 3:03:41pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <string.h>
using namespace std;

//==============================================================================
/*
*/
class MixerGui    : public Component, private Slider::Listener
{
public:
    MixerGui();
    ~MixerGui();

    void paint (Graphics&) override;
    void resized() override;

    //==================CUSTOM METHODS=======================   
    void setProcessor(AddsynthAudioProcessor* p);

private:
    AddsynthAudioProcessor* processor;

    Slider oscGain[4];
    Label oscGainLabel[4];
 
    void sliderValueChanged(Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MixerGui)
};