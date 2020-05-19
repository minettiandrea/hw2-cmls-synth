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
        freeOffset[i].setRange(0, 1000, 0.0001);
        freeOffset[i].setValue(0);
        freeOffset[i].setSliderStyle(Slider::Rotary);
        freeOffset[i].setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
        
        harmonicOffset[i].setRange(0, 10, 1);
        harmonicOffset[i].setValue(0);
        harmonicOffset[i].setSliderStyle(Slider::Rotary);
        harmonicOffset[i].setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

        //Add the listener
        freeOffset[i].addListener(this);
        harmonicOffset[i].addListener(this);
        
        //Name the label, center it and attach it to the corresponding slider
        freeOffsetLabel[i].setText("OSC " + to_string(i + 2), dontSendNotification);
        freeOffsetLabel[i].setJustificationType(Justification(36));
        freeOffsetLabel[i].attachToComponent(&freeOffset[i], false);
        
        harmonicOffsetLabel[i].setText("OSC " + to_string(i + 2), dontSendNotification);
        harmonicOffsetLabel[i].setJustificationType(Justification(36));       //center the label
        harmonicOffsetLabel[i].attachToComponent(&harmonicOffset[i], false);

        //Make slider and label visible
        addAndMakeVisible(freeOffset[i]);
        addAndMakeVisible(freeOffsetLabel[i]);
        
        addAndMakeVisible(harmonicOffset[i]);
        addAndMakeVisible(harmonicOffsetLabel[i]);
        
        //Hide the HARMONIC offset slider (default view is on FREE)
        harmonicOffset[i].setVisible(false);
        harmonicOffsetLabel[i].setVisible(false);
    }
    
    for (auto& button : offsetType) {
        //Make the buttons toggle, add them to the same radio group and link the onClick function
        button.setClickingTogglesState(true);
        button.setRadioGroupId(1, dontSendNotification);
        button.onClick = [this] {changeView();};
        addAndMakeVisible(button);
    }

    offsetType[0].setButtonText("FREE");
    offsetType[1].setButtonText("HARMONIC");

    //Set the FREE button as default
    offsetType[0].setToggleState(true, dontSendNotification);

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
    
    //Create 2 FlexBox layout (one for FREE configuration and one for HARMONIC configuration)
    FlexBox freeLayout;
    FlexBox harmonicLayout;

    freeLayout.flexDirection = FlexBox::Direction::column;
    freeLayout.justifyContent = FlexBox::JustifyContent::center;
    freeLayout.alignContent = FlexBox::AlignContent::center;

    harmonicLayout.flexDirection = FlexBox::Direction::column;
    harmonicLayout.justifyContent = FlexBox::JustifyContent::center;
    harmonicLayout.alignContent = FlexBox::AlignContent::center;

    //Add the sliders to the respective layout
    for (auto& element : freeOffset) {
        freeLayout.items.add(FlexItem(element).withMargin(FlexItem::Margin(40, 0, 30, 0)).withFlex(1, 1));
    }
    
    for (auto& element : harmonicOffset) {
        harmonicLayout.items.add(FlexItem(element).withMargin(FlexItem::Margin(40, 0, 30, 0)).withFlex(1, 1));
    }
    
    //Add the buttons to both layouts
    for (auto& button : offsetType) {
        freeLayout.items.add(FlexItem(button).withMargin(FlexItem::Margin(0, 0, 15, 0)).withMaxHeight(30).withWidth(100).withFlex(1, 1));
    }

    for (auto& button : offsetType) {
        harmonicLayout.items.add(FlexItem(button).withMargin(FlexItem::Margin(0, 0, 15, 0)).withMaxHeight(30).withWidth(100).withFlex(1, 1));
    }

    //Perform both layouts (they will be visible one at a time)
    freeLayout.performLayout(getBounds().toFloat());
    harmonicLayout.performLayout(getBounds().toFloat());

}

//Define the behaviour when a slider value in the mixer change
void OffsetGui::sliderValueChanged(Slider* slider)
{
    for (int i = 0; i < 3; i++) {
        if (slider == &freeOffset[i]) {
            for (auto& synth : processor->getSynths()) {
                synth->setOscOffset(i + 1, freeOffset[i].getValue());
            }
        }
        else if (slider == &harmonicOffset[i]) {
            for (auto& synth : processor->getSynths()) {
                synth->setOscOffset(i + 1, harmonicOffset[i].getValue()*synth->getFundamentalFrequency());
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

void OffsetGui::changeView()
{    
    for (int i = 0; i < 3; i++) {
        if (offsetType[0].getToggleState()) {
            //Set the offset view to FREE
            harmonicOffset[i].setVisible(false);
            harmonicOffsetLabel[i].setVisible(false);

            freeOffset[i].setVisible(true);
            freeOffsetLabel[i].setVisible(true);

            //Set the oscillators offsets
            for (auto& synth : processor->getSynths()) {
                synth->setOscOffset(i + 1, freeOffset[i].getValue());
            }
        }
        else if (offsetType[1].getToggleState()) {
            //set the offset view to HARMONIC
            freeOffset[i].setVisible(false);
            freeOffsetLabel[i].setVisible(false);

            harmonicOffset[i].setVisible(true);
            harmonicOffsetLabel[i].setVisible(true);

            //Set the oscillators offsets
            for (auto& synth : processor->getSynths()) {
                synth->setOscOffset(i + 1, harmonicOffset[i].getValue() * synth->getFundamentalFrequency());
            }
        }
    }

}

