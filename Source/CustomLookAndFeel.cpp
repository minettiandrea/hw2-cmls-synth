/*
  ==============================================================================

    CustomLookAndFeel.cpp
    Created: 19 May 2020 9:42:19pm
    Author:  Gabriele Stucchi

  ==============================================================================
*/

#include "CustomLookAndFeel.h"

CustomLookAndFeel::CustomLookAndFeel()
{
    //Set sliders colors
    setColour(Slider::thumbColourId, Colours::white.darker(0.1));
    setColour(Slider::backgroundColourId, Colours::black.brighter(0.5));
    setColour(Slider::trackColourId, Colours::black.brighter(0.1));

    //Set buttons colors
    setColour(TextButton::buttonColourId, Colours::black.brighter(0.1));
    setColour(TextButton::buttonOnColourId, Colours::black.brighter(0.5));

}

void CustomLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    auto radius = jmin(width / 2, height / 2) - 10.0f;
    auto diameter = radius * 2.0f;
    auto centreX = x + width * 0.5f;
    auto centreY = y + height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    //Draw the dial
    g.setColour(Colours::black.brighter(0.1));
    g.fillEllipse(rx, ry, diameter, diameter);


    // Draw the outline of dial
    g.setColour(Colours::black.brighter(0.3));
    g.drawEllipse(rx, ry, diameter, diameter, 0.5f);

    //Draw the pointer
    g.setColour(Colours::white.darker(0.1));
    auto pointerLength = radius * 0.75f;
    auto pointerThickness = 2.0f;
    point.setXY(centreX, centreY - (radius/2 + radius/6));
    point.applyTransform(AffineTransform::rotation(angle, centreX, centreY));
    g.fillEllipse(point.x - radius/6, point.y - radius/6, radius / 3, radius / 3);
}