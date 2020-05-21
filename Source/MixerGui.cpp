/*
  ==============================================================================

    MixerGui.cpp
    Created: 17 May 2020 3:03:41pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#include "MixerGui.h"



//==============================================================================
MixerGui::MixerGui(MixerState* state)
{

    this->state = state;

    setSize(125, 540);

    for (int i = 0; i < 4; i++) {
        //Set all the slider properties
        oscGain[i].setRange(0, 1, 0.0001);
        oscGain[i].setValue(1);
        oscGain[i].setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
        oscGain[i].setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

        //Add the listener
        oscGain[i].addListener(this);

        //Name the label, set the font, center it and attach it to the corresponding slider
        oscGainLabel[i].setText("OSC " + to_string(i+1), dontSendNotification);
        oscGainLabel[i].setFont(Font(16.0f));
        oscGainLabel[i].setJustificationType(Justification(36));
        oscGainLabel[i].attachToComponent(&oscGain[i], false);

        //Make slider and label visible
        addAndMakeVisible(oscGain[i]);
        addAndMakeVisible(oscGainLabel[i]);
    }

}

MixerGui::~MixerGui()
{
}

void MixerGui::paint (Graphics& g)
{
    //Set background color
    g.fillAll(Colours::black.brighter(0.2));

    //Draw the outline
    g.setColour(Colours::black.brighter(0.1));
    g.drawRect (getLocalBounds(), 1.5);
}

void MixerGui::resized()
{
    //Define the layout
    FlexBox layout;

    layout.flexDirection = FlexBox::Direction::column;
    layout.justifyContent = FlexBox::JustifyContent::center;

    for (auto& element : oscGain) {
        layout.items.add(FlexItem(element).withMargin(FlexItem::Margin(40, 0, 20, 0)).withFlex(1, 1));
    }

    layout.performLayout(getBounds().toFloat());

}

//Define the behaviour when a slider value in the mixer change
void MixerGui::sliderValueChanged(Slider* slider)
{
    for (int i = 0; i < 4; i++) {
        if (slider == &oscGain[i]){
                state->set(i,oscGain[i].getValue());
        }
    }

}


