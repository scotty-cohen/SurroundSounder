/*
  ==============================================================================

    LookAndFeel.h
    Created: 2 Apr 2023 9:59:41pm
    Author:  Scott Cohen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <juce_graphics/juce_graphics.h>

class MyLookAndFeel : public juce::LookAndFeel_V4, public juce::MouseListener {

public:

    MyLookAndFeel() : knobColor(Colour(100, 100, 100)) {
        setColour(juce::PopupMenu::backgroundColourId, juce::Colour(194, 220, 226).darker(0.1f));
    }

    int getKnobSize() const
    {
        return mKnobSize;
    }
    
    
 void drawRotarySlider (Graphics& g, int x, int y, int width, int height,
                                              float sliderPosProportional,
                                              float rotaryStartAngle,
                                              float rotaryEndAngle,
                                              Slider&) override;

    void drawComboBox(Graphics &g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW,
                      int buttonH, ComboBox &box) override;

    void drawComboBoxTextWhenNothingSelected(Graphics &g, ComboBox &box, Label &label) override;

    void drawPopupMenuItem(juce::Graphics &g, const juce::Rectangle<int> &area,
                           const bool isSeparator, const bool isActive,
                           const bool isHighlighted, const bool isTicked,
                           const bool hasSubMenu, const juce::String &text,
                           const juce::String &shortcutKeyText,
                           const juce::Drawable *icon, const juce::Colour *const textColourToUse) override;

    void drawLinearSlider(Graphics &g, int x, int y, int width, int height,
                          float sliderPos, float minSliderPos, float maxSliderPos,
                          const Slider::SliderStyle style, Slider &slider) override;


    void mouseDown(const MouseEvent &event) override;

    void mouseUp(const MouseEvent &event) override;


private:

    int mKnobSize = 0;

    Colour knobColor;

    DropShadowEffect dropShadowEffect;


};
