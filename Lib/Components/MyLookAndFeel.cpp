/*
  ==============================================================================

    LookAndFeel.cpp
    Created: 2 Apr 2023 9:59:41pm
    Author:  Scott Cohen

  ==============================================================================
*/

#include "MyLookAndFeel.h"


void MyLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int width, int height,
                                             float sliderPos,
                                             float rotaryStartAngle,
                                             float rotaryEndAngle,
                                             Slider& slider)
{
    int knob_size = jmin(width, height);


    mKnobSize = knob_size;

    Rectangle<float> container_bounds{(float) x, (float) y, (float) width, (float) height};
    Rectangle<float> knob_bounds{container_bounds.getCentreX() - knob_size / 2,
                                 container_bounds.getCentreY() - knob_size / 2,
                                 (float) knob_size,
                                 (float) knob_size};
    Point<float> center = knob_bounds.getCentre();

    auto toAngle = rotaryStartAngle + (sliderPos + .048f) * (MathConstants<float>::twoPi / 2);

    // Create an Image object for the knob and its shadow
    Image knobImage(Image::PixelFormat::ARGB, width, height, true);
    // Create a new Graphics object for the knob image
    Graphics knobGraphics(knobImage);
    knobGraphics.setColour(Colour(100, 100, 100));
    knobGraphics.fillEllipse(knob_bounds);

    // Apply the drop shadow effect to the knob image
    dropShadowEffect.applyEffect(knobImage, g, .3f, 1.0f);


    //Draw the basic knob
    g.setColour(knobColor);;
    g.fillEllipse(knob_bounds);
    g.setColour(Colour(255, 255, 255));
    g.fillEllipse(knob_bounds.reduced(knob_size * .01, knob_size * .01));
    g.setColour(knobColor);;
    g.fillEllipse(knob_bounds.reduced(knob_size * .08, knob_size * .08));

    // Draw the filled arc
    Path filledArc;
    float arcWidth = knob_size * 0.08f;
    float outerRadius = (knob_size / 2.0f) - arcWidth;
    float innerRadius = outerRadius - arcWidth;
    float startAngle = rotaryStartAngle;
    float endAngle = toAngle;
    float angleOffset = MathConstants<float>::pi / 2;

    filledArc.addCentredArc(knob_bounds.getCentreX(), knob_bounds.getCentreY(),
                            outerRadius, outerRadius,
                            0.0f, startAngle * 2 + angleOffset + .35, endAngle * 2 + angleOffset, true);
    filledArc.addCentredArc(knob_bounds.getCentreX(), knob_bounds.getCentreY(),
                            innerRadius, innerRadius,
                            0.0f, endAngle * 2 + angleOffset, startAngle * 2 + angleOffset + .35, false);
    filledArc.closeSubPath();

    g.setColour(Colours::orange); // Set the color of the filled arc
    g.fillPath(filledArc);


    auto knobCenter = knob_bounds.getCentre();
    auto thumbRadius = knob_size;
    auto thumbRadius2 = knob_size * .5;
    auto rectBounds = knob_bounds.withSizeKeepingCentre(knob_size * 0.6, knob_size * 0.5);
    auto rectCenter = rectBounds.getCentre();
    auto rectAngle = toAngle;


        // Rotate the graphics context around the center of the knob
        g.addTransform (AffineTransform::rotation (toAngle, knobCenter.x, knobCenter.y));

        
        // Draw line
        g.setColour (Colours::black);
        for (int i = 0; i < 1; i++) {
            g.drawLine(rectCenter.getX(), rectCenter.getY(),
                       rectCenter.getX() + (thumbRadius * 0.5) * std::cos(rectAngle),
                       rectCenter.getY() + (thumbRadius * 0.5) * std::sin(rectAngle),
                       knob_size * 0.075);


        }

    // Draw line
    g.setColour(knobColor);;
    g.strokePath(Path().createPathWithRoundedCorners(4), PathStrokeType(10.0));
    for (int i = 0; i < 1; i++) {
        g.drawLine(rectCenter.getX(), rectCenter.getY(),
                   rectCenter.getX() + (thumbRadius2 * 0.5) * std::cos(rectAngle),
                   rectCenter.getY() + (thumbRadius2 * 0.5) * std::sin(rectAngle),
                   knob_size * 0.1);

    }

    // Draw the center circle
    auto centerSize = knob_size * 0.1f;
    auto centerBounds = Rectangle<float>(center.x - centerSize / 2.0f,
                                         center.y - centerSize / 2.0f,
                                         centerSize,
                                         centerSize);
    g.setColour(knobColor);;
    g.fillEllipse(centerBounds);


}

void MyLookAndFeel::drawComboBox(Graphics& g, int width, int height, bool isButtonDown,
                                int buttonX, int buttonY, int buttonW, int buttonH,
                                ComboBox& box)
{
    // Set the ComboBox background and text colors in the LookAndFeel_V4
        setColour(ComboBox::backgroundColourId, Colour(145, 179, 187));
        setColour(ComboBox::textColourId, Colours::black);

        // Call the base class method to draw the button and frame
        LookAndFeel_V4::drawComboBox(g, width, height, isButtonDown,
                                    buttonX, buttonY, buttonW, buttonH, box);
        
        float cornerSize = 5.0f; // Set the corner rounding size
    
        if (!box.isPopupActive())
        {
            g.setColour(juce::Colour(0, 0, 139)); // Dark blue
            g.drawRoundedRectangle(0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height), cornerSize, 2.0f); // Draw the stroke with rounded corners
        }
}

void MyLookAndFeel::drawComboBoxTextWhenNothingSelected(Graphics& g, ComboBox& box, Label& label)
{
    // Set the text color to light blue
    g.setColour(Colour(173, 216, 230));
    g.drawText(label.getText(), label.getBounds(), Justification::centred);
}

void MyLookAndFeel::drawPopupMenuItem (juce::Graphics& g, const juce::Rectangle<int>& area,
                         const bool isSeparator, const bool isActive,
                         const bool isHighlighted, const bool isTicked,
                         const bool hasSubMenu, const juce::String& text,
                         const juce::String& shortcutKeyText,
                         const juce::Drawable* icon, const juce::Colour* const textColourToUse)
{
    juce::Colour textColour;

    if (isHighlighted)
        textColour = juce::Colour(173, 216, 230); // Light blue when hovered
    else
        textColour = juce::Colours::black; // White text when not hovered

    auto &defaultLookAndFeel = static_cast<LookAndFeel_V4 &>(LookAndFeel::getDefaultLookAndFeel());
    defaultLookAndFeel.drawPopupMenuItem(g, area, isSeparator, isActive, isHighlighted, isTicked, hasSubMenu,
                                         text, shortcutKeyText, icon, &textColour);
}

void MyLookAndFeel::mouseDown(const MouseEvent &event) {
    knobColor = Colour(150, 150, 150);
    if (auto *slider = dynamic_cast<Slider *>(event.eventComponent))
        slider->repaint();
}

void MyLookAndFeel::mouseUp(const MouseEvent &event) {
    knobColor = Colour(100, 100, 100);
    if (auto *slider = dynamic_cast<Slider *>(event.eventComponent))
        slider->repaint();
}

