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
    setSize(500, 135);
}

void EnvelopeGui::init(int id, EnvelopeState* state)
{

    this->state = state;


    paramLabel[0].setText("A", dontSendNotification);
    paramLabel[1].setText("D", dontSendNotification);
    paramLabel[2].setText("S", dontSendNotification);
    paramLabel[3].setText("R", dontSendNotification);

    for (int i = 0; i < 4; i++) {
        //Set all the slider properties
        envParam[i].setRange(0.001, 3, 0.001);
        envParam[i].setValue(0.1);
        envParam[i].setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
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
    envParam[2].setRange(0, 1, 0.001);
    envParam[2].setValue(1);

    //Set the osc ID
    oscIdLabel.setText(to_string(id + 1), dontSendNotification);
    oscIdLabel.setFont(Font(20.0f, Font::bold));
    oscIdLabel.setJustificationType(Justification(36));
    addAndMakeVisible(oscIdLabel);

}

EnvelopeGui::~EnvelopeGui()
{
}

void EnvelopeGui::paint (Graphics& g)
{
    //Set background color
    g.fillAll(Colours::black.brighter(0.2));

    //Draw the outline
    g.setColour(Colours::black.brighter(0.1));
    g.drawRect (getLocalBounds(), 1.5); 
    
}

void EnvelopeGui::resized()
{
    //Define the layout
    FlexBox layout;

    layout.flexDirection = FlexBox::Direction::row;
    layout.justifyContent = FlexBox::JustifyContent::center;

    layout.items.add(FlexItem(oscIdLabel).withMargin(FlexItem::Margin(30, 0, 20, 0)).withFlex(1, 1));
    for (auto& element : envParam) {
        layout.items.add(FlexItem(element).withMargin(FlexItem::Margin(40, 0, 20, 0)).withFlex(1, 1));
    }

    layout.performLayout(getBounds().toFloat());

}

//Define the behaviour when a slider value in the envelope change
void EnvelopeGui::sliderValueChanged(Slider* slider)
{
    
    this->state->setAttack(envParam[0].getValue());
    this->state->setDecay(envParam[1].getValue());
    this->state->setSustain(envParam[2].getValue());
    this->state->setRelease(envParam[3].getValue());


}

