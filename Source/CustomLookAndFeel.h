/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 19 May 2020 9:42:19pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class CustomLookAndFeel : public LookAndFeel_V4 
{
public:
    CustomLookAndFeel();
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override;

private:
    Point<float> point;
};