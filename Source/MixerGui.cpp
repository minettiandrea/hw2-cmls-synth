/*
  ==============================================================================

    MixerGui.cpp
    Created: 17 May 2020 3:03:41pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#include "MixerGui.h"



//==============================================================================
MixerGui::MixerGui()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(125, 540);

    for (int i = 0; i < 4; i++) {
        //Set all the slider properties
        oscGain[i].setRange(0, 1, 0.0001);
        oscGain[i].setValue(1);
        oscGain[i].setSliderStyle(Slider::Rotary);
        oscGain[i].setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

        //Add the listener
        oscGain[i].addListener(this);

        //Name the label, center it and attach it to the corresponding slider
        oscGainLabel[i].setText("OSC " + to_string(i+1), dontSendNotification);
        oscGainLabel[i].setJustificationType(Justification(36));       //center the label
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
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

}

void MixerGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    FlexBox container;

    container.flexDirection = FlexBox::Direction::column;
    container.justifyContent = FlexBox::JustifyContent::center;

    for (auto& element : oscGain) {
        container.items.add(FlexItem(element).withMargin(FlexItem::Margin(40, 0, 20, 0)).withFlex(1, 1));
    }

    container.performLayout(getBounds().toFloat());

}

//Define the behaviour when a slider value in the mixer change
void MixerGui::sliderValueChanged(Slider* slider)
{
    for (int i = 0; i < 4; i++) {
        if (slider == &oscGain[i]){
            for (auto& synth : processor->getSynths()) {
                synth->setOscGain(i, oscGain[i].getValue());
            }
        }
    }

}

//=============================CUSTOM METHODS===========================

//Set the reference to the processor in order to perform the operations
void MixerGui::setProcessor(AddsynthAudioProcessor* p)
{
    processor = p;
}

