/*
  ==============================================================================

    OffsetGui.cpp
    Created: 17 May 2020 3:28:18pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#include "OffsetGui.h"

//==============================================================================
OffsetGui::OffsetGui()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    setSize(150, 540);

    for (int i = 0; i < 3; i++) {
        //Set all the sliders properties
        oscOffset[i].setRange(0, 1000, 0.0001);
        oscOffset[i].setValue(0);
        oscOffset[i].setSliderStyle(Slider::Rotary);
        oscOffset[i].setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

        //Add the listener
        oscOffset[i].addListener(this);
        
        //Name the label, center it and attach it to the corresponding slider
        oscOffsetLabel[i].setText("OSC " + to_string(i + 2), dontSendNotification);
        oscOffsetLabel[i].setJustificationType(Justification(36));
        oscOffsetLabel[i].attachToComponent(&oscOffset[i], false);

        //Make slider and label visible
        addAndMakeVisible(oscOffset[i]);
        addAndMakeVisible(oscOffsetLabel[i]);
    }

}

OffsetGui::~OffsetGui()
{
}

void OffsetGui::paint (Graphics& g)
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

void OffsetGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    //Insert all the elements in a FlexBox in order to have them displayed more ordered
    FlexBox container;

    container.flexDirection = FlexBox::Direction::column;
    container.justifyContent = FlexBox::JustifyContent::center;

    for (auto& element : oscOffset) {
        container.items.add(FlexItem(element).withMargin(FlexItem::Margin(50, 0, 30, 0)).withFlex(1, 1));
    }

    container.performLayout(getBounds().toFloat());

}

//Define the behaviour when a slider value in the mixer change
void OffsetGui::sliderValueChanged(Slider* slider)
{
    for (int i = 0; i < 3; i++) {
        if (slider == &oscOffset[i]) {
            for (auto& synth : processor->getSynths()) {
                synth->setOscOffset(i + 1, oscOffset[i].getValue());
            }
        }
    }

}

//=============================CUSTOM METHODS===========================

//Set the reference to the processor in order to perform the operations
void OffsetGui::setProcessor(AddsynthAudioProcessor* p)
{
    processor = p;
}
