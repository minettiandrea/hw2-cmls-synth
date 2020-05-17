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
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    //Passing a reference to the processor at each component (except for the envelopes for which is done below)
    mixer.setProcessor(&processor);
    output.setProcessor(&processor);
    offsets.setProcessor(&processor);

    
    setSize(925, 600);

    //Set all the labels text and center them
    mixerLabel.setText("MIXER", dontSendNotification);
    mixerLabel.setJustificationType(Justification(36));
    envelopeLabel.setText("ENVELOPES", dontSendNotification);
    envelopeLabel.setJustificationType(Justification(36));
    offsetsLabel.setText("OFFSETS", dontSendNotification);
    offsetsLabel.setJustificationType(Justification(36));
    outputLabel.setText("OUTPUT", dontSendNotification);
    outputLabel.setJustificationType(Justification(36));

    //Make all components and labels visible
    addAndMakeVisible(mixer);
    for (auto& env : envelope) {
        addAndMakeVisible(env);
        //Done here in order to have a single loop
        env.setProcessor(&processor);
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
}

//==============================================================================
void AddsynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void AddsynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

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
        envelope[i].setId(i);
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