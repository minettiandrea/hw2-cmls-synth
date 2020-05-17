/*
  ==============================================================================

    OutputGui.h
    Created: 17 May 2020 3:32:28pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class OutputGui    : public Component, private Slider::Listener
{
public:
    OutputGui();
    ~OutputGui();

    void paint (Graphics&) override;
    void resized() override;

    //==================CUSTOM METHODS=======================   
    void setProcessor(AddsynthAudioProcessor* p);

private:
    AddsynthAudioProcessor* processor;

    Slider gain;

    void sliderValueChanged(Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OutputGui)
};
