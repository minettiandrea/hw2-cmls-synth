/*
  ==============================================================================

    MixerGui.h
    Created: 17 May 2020 3:03:41pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <string.h>
#include "State.h"
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
    void init(MixerState* state);


private:
    MixerState* state;

    Slider oscGain[4];
    Label oscGainLabel[4];
 
    void sliderValueChanged(Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MixerGui)
};