/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"


//==============================================================================
AddsynthAudioProcessorEditor::AddsynthAudioProcessorEditor (AddsynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    //Passing a reference to the processor at each component (except for the envelopes for which is done below)
    mixer.init(p.getState()->getMixer());
    for (int i = 0; i < 4; i++) {
        envelope[i].init(i,p.getState()->getEnvelope(i));
    }
    offsets.init(p.getState()->getOffset());
    output.init(p.getState());

    
    setSize(925, 600);
    
    //Setting the custom look and feel
    customLookAndFeel = new CustomLookAndFeel();
    setLookAndFeel(customLookAndFeel);

    //Set all the labels text and font and center them
    mixerLabel.setText("MIXER", dontSendNotification);
    mixerLabel.setFont(Font(22.0f, Font::bold));
    mixerLabel.setJustificationType(Justification(36));
    envelopeLabel.setText("ENVELOPES", dontSendNotification);
    envelopeLabel.setFont(Font(20.0f, Font::bold));
    envelopeLabel.setJustificationType(Justification(36));
    offsetsLabel.setText("OFFSETS", dontSendNotification);
    offsetsLabel.setFont(Font(20.0f, Font::bold));
    offsetsLabel.setJustificationType(Justification(36));
    outputLabel.setText("OUTPUT", dontSendNotification);
    outputLabel.setFont(Font(20.0f, Font::bold));
    outputLabel.setJustificationType(Justification(36));

    //Make all components and labels visible
    addAndMakeVisible(mixer);
    for (auto& env : envelope) {
        addAndMakeVisible(env);
    }
    addAndMakeVisible(offsets);
    addAndMakeVisible(output);
    addAndMakeVisible(mixerLabel);
    addAndMakeVisible(envelopeLabel);
    addAndMakeVisible(offsetsLabel);
    addAndMakeVisible(outputLabel);
}

AddsynthAudioProcessorEditor::~AddsynthAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
    delete customLookAndFeel;
}

//==============================================================================
void AddsynthAudioProcessorEditor::paint (Graphics& g)
{
    // Set background color
    g.fillAll(Colours::black.brighter(0.4));
}

void AddsynthAudioProcessorEditor::resized()
{
    //Set a 10px global margin
    int margin = 10;
    auto area = getLocalBounds().reduced(margin);

    //Add the Mixer section to the left
    auto mixerSection = area.removeFromLeft(mixer.getWidth());
    mixerLabel.setBounds(mixerSection.removeFromTop(30));
    mixer.setBounds(mixerSection.removeFromBottom(mixer.getHeight()));

    //Set a margin between Mixer and Envelopes sections
    area.removeFromLeft(10);

    //Add the Envelopes section right to the Mixer one (also setting the osc ID while adding them)
    auto envelopeSection = area.removeFromLeft(envelope[0].getWidth());
    envelopeLabel.setBounds(envelopeSection.removeFromTop(30));
    for (int i = 3; i >= 0; i--) {
        envelope[i].setBounds(envelopeSection.removeFromBottom(envelope[i].getHeight()));
    }

    //Set a margin between Envelopes and Offsets sections
    area.removeFromLeft(10);

    //Add the Offsets section right to the Envelopes one
    auto offsetsSection = area.removeFromLeft(offsets.getWidth());
    offsetsLabel.setBounds(offsetsSection.removeFromTop(30));
    offsets.setBounds(offsetsSection.removeFromBottom(offsets.getHeight()));

    //Set a margin between Offsets and Output sections
    area.removeFromLeft(10);

    //Add the Output section right to the Offsets one
    auto outputSection = area.removeFromLeft(output.getWidth());
    outputLabel.setBounds(outputSection.removeFromTop(30));
    output.setBounds(outputSection.removeFromBottom(output.getHeight()));
}