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
    EnvelopeGui();
    ~EnvelopeGui();

    void paint (Graphics&) override;
    void resized() override;
    void init(int i, EnvelopeState* state);
    

private:
    EnvelopeState* state;

    Label oscIdLabel;
    Slider envParam[4];
    Label paramLabel[4];

    void sliderValueChanged(Slider* slider) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeGui)
};
