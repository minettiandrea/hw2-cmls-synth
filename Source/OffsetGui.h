/*
  ==============================================================================

    OffsetGui.h
    Created: 17 May 2020 3:28:18pm
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
class OffsetGui    : public Component, private Slider::Listener
{
public:
    OffsetGui(OffsetState* state);
    ~OffsetGui();

    void paint (Graphics&) override;
    void resized() override;

    //==================CUSTOM METHODS=======================   
    void changeView();

private:
    OffsetState* state;

    Slider freeOffset[3], harmonicOffset[3];
    Label freeOffsetLabel[3], harmonicOffsetLabel[3];
    TextButton offsetType[2];

    void sliderValueChanged(Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OffsetGui)
};