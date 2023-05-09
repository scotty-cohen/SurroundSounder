/*
  ==============================================================================

    SliderContainer.h
    Created: 31 Mar 2023 9:36:21pm
    Author:  Scott Cohen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MyLookAndFeel.h"

class SliderContainer : public juce::Component {

public:

    /*/*/

    SliderContainer(bool stopAtEnd = true);

    /**/
    void setParameterToControl(juce::AudioProcessorValueTreeState &inVTS, const juce::String &inParamID);

    /***/
    void resized() override;

    void setSliderStyle(juce::Slider::SliderStyle style);


    const juce::String &getParameterID() const;


    juce::Slider &getSlider();


private:

    juce::Slider mSlider;
    juce::Label mLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mAttachment;

    MyLookAndFeel mLookAndFeel;

    bool stopAtEnd; // Add a new member variable
    
juce::String parameterID;
    
};
