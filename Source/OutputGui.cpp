/*
  ==============================================================================

    OutputGui.cpp
    Created: 17 May 2020 3:32:28pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#include "OutputGui.h"

//==============================================================================
OutputGui::OutputGui()
{   
    setSize(100, 540);

    //Set the slider properties
    gain.setRange(0, 1, 0.0001);
    gain.setValue(0.5);
    gain.setSliderStyle(Slider::LinearVertical);
    gain.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

    //Add the listener
    gain.addListener(this);

    //Make the slider visible
    addAndMakeVisible(gain);

}

OutputGui::~OutputGui()
{
}

void OutputGui::paint (Graphics& g)
{
    //Set background color
    g.fillAll(Colours::black.brighter(0.2));

    //Draw the outline
    g.setColour(Colours::black.brighter(0.1));
    g.drawRect (getLocalBounds(), 1.5);

}

void OutputGui::resized()
{
    //Define the layout
    FlexBox layout;

    layout.flexDirection = FlexBox::Direction::column;
    layout.justifyContent = FlexBox::JustifyContent::center;

    layout.items.add(FlexItem(gain).withMargin(FlexItem::Margin(50, 0, 50, 0)).withFlex(1, 1));

    layout.performLayout(getBounds().toFloat());

}

//Define the behaviour when the slider value change
void OutputGui::sliderValueChanged(Slider* slider)
{
    for (auto& synth : processor->getSynths()) {
        synth->setOutputGain(gain.getValue());
    }
}

//==========================CUSTOM METHODS================================

//Set the reference to the processor in order to perform the operations
void OutputGui::setProcessor(AddsynthAudioProcessor* p)
{
    processor = p;
}
