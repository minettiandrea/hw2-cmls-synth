/*
  ==============================================================================

    EnvelopeGui.h
    Created: 17 May 2020 3:17:33pm
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
class EnvelopeGui    : public Component, private Slider::Listener
{
public:
    EnvelopeGui(int i, EnvelopeState* state);
    ~EnvelopeGui();

    void paint (Graphics&) override;
    void resized() override;
    

private:
    EnvelopeState* state;
    AddsynthAudioProcessor* processor;

    Label oscIdLabel;
    Slider envParam[4];
    Label paramLabel[4];

    void sliderValueChanged(Slider* slider) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeGui)
};
