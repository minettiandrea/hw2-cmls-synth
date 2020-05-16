/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <string.h>
using namespace std;

//==============================================================================
AddsynthAudioProcessorEditor::AddsynthAudioProcessorEditor (AddsynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    outputGain.setRange(0, 1, 0.0001);
    outputGain.setValue(0.5);
    outputGain.setSkewFactorFromMidPoint(0.2);

    outputGainLabel.setText("GAIN", dontSendNotification);
    outputGainLabel.attachToComponent(&outputGain, true);

    for (int i = 0; i < 4; i++) {
        oscGains[i].setRange(0, 1, 0.0001);
        oscGains[i].setValue(0.5);
        oscGains[i].setSkewFactorFromMidPoint(0.2);
        oscGainsLabels[i].setText("OSC " + to_string(i) + " GAIN", dontSendNotification);
        oscGainsLabels[i].attachToComponent(&oscGains[i], true);
        oscGains[i].setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

        oscGains[i].addListener(this);
        addAndMakeVisible(oscGains[i]);
        addAndMakeVisible(oscGainsLabels[i]);
    }

    outputGain.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    outputGain.addListener(this);

    addAndMakeVisible(outputGain);
    addAndMakeVisible(outputGainLabel);
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
    auto sliderLeft = 120;

    outputGain.setBounds(sliderLeft, 20, getWidth() - sliderLeft - 10, 20);
    oscGains[0].setBounds(sliderLeft, 50, getWidth() - sliderLeft - 10, 20);
    for (int i = 1; i < 4; i++) {
        oscGains[i].setBounds(sliderLeft, oscGains[i - 1].getBounds().getY() + 30, getWidth() - sliderLeft - 10, 20);
    }
}

void AddsynthAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &outputGain) {
        for (auto& synth : processor.getSynths()) {
            synth->setOutputGain(outputGain.getValue());
        }
    }

    for (int i = 0; i < 4; i++) {
        if (slider == &oscGains[i]) {
            for (auto& synth : processor.getSynths()) {
                synth->setOscGain(i, oscGains[i].getValue());
            }
        }
    }
}