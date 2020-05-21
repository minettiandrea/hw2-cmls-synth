/*
  ==============================================================================

    OutputGui.h
    Created: 17 May 2020 3:32:28pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "State.h"

//==============================================================================
/*
*/
class OutputGui    : public Component, private Slider::Listener
{
public:
    OutputGui(State* state);
    ~OutputGui();

    void paint (Graphics&) override;
    void resized() override;

private:
    State* state;

    Slider gain;

    void sliderValueChanged(Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OutputGui)
};
