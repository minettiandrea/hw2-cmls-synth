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
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
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
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

}

void OutputGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    //Insert all the elements in a FlexBox in order to have them displayed more ordered
    FlexBox container;

    container.flexDirection = FlexBox::Direction::column;
    container.justifyContent = FlexBox::JustifyContent::center;

    container.items.add(FlexItem(gain).withMargin(FlexItem::Margin(50, 0, 50, 0)).withFlex(1, 1));

    container.performLayout(getBounds().toFloat());

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
