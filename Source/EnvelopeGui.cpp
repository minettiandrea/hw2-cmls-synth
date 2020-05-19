/*
  ==============================================================================

    EnvelopeGui.cpp
    Created: 17 May 2020 3:17:33pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#include "EnvelopeGui.h"

//==============================================================================
EnvelopeGui::EnvelopeGui()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    setSize(500, 135);

    paramLabel[0].setText("A", dontSendNotification);
    paramLabel[1].setText("D", dontSendNotification);
    paramLabel[2].setText("S", dontSendNotification);
    paramLabel[3].setText("R", dontSendNotification);

    for (int i = 0; i < 4; i++) {
        //Set all the slider properties
        envParam[i].setRange(0.01, 5, 0.01);
        envParam[i].setValue(0.1);
        envParam[i].setSliderStyle(Slider::Rotary);
        envParam[i].setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

        //Add the listener
        envParam[i].addListener(this);

        //Center the label and attach it to the corresponding slider
        paramLabel[i].setJustificationType(Justification(36));
        paramLabel[i].attachToComponent(&envParam[i], false);

        //Make slider and label visible
        addAndMakeVisible(envParam[i]);
        addAndMakeVisible(paramLabel[i]);
    }

    //Update the "Sustain" slider values
    envParam[2].setRange(0, 1, 0.01);
    envParam[2].setValue(1);

    //Set a default text for the osc ID. It will recieve the right ID from the PluginEditor
    oscIdLabel.setText("ID", dontSendNotification);
    oscIdLabel.setJustificationType(Justification(36));
    addAndMakeVisible(oscIdLabel);

}

EnvelopeGui::~EnvelopeGui()
{
}

void EnvelopeGui::paint (Graphics& g)
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

void EnvelopeGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    //Insert all the elements in a FlexBox in order to have them displayed more ordered
    FlexBox container;

    container.flexDirection = FlexBox::Direction::row;
    container.justifyContent = FlexBox::JustifyContent::center;

    container.items.add(FlexItem(oscIdLabel).withMargin(FlexItem::Margin(30, 0, 20, 0)).withFlex(1, 1));
    for (auto& element : envParam) {
        container.items.add(FlexItem(element).withMargin(FlexItem::Margin(40, 0, 20, 0)).withFlex(1, 1));
    }

    container.performLayout(getBounds().toFloat());

}

//Define the behaviour when a slider value in the envelope change
void EnvelopeGui::sliderValueChanged(Slider* slider)
{
    for (auto& synth : processor->getSynths()) {
        synth->setOscEnvelope(oscId, envParam[0].getValue(), envParam[1].getValue(), envParam[2].getValue(), envParam[3].getValue());
    }
}


//==========================CUSTOM METHODS================================

//Set the reference to the processor in order to perform the operations
void EnvelopeGui::setProcessor(AddsynthAudioProcessor* p)
{
    processor = p;
}

//Set the ID of the oscillator that the envelope is controlling
void EnvelopeGui::setId(int id)
{
    this->oscId = id;
    this->oscIdLabel.setText(to_string(id + 1), dontSendNotification);
}
