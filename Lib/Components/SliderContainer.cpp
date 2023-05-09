/*
  ==============================================================================

    SliderContainer.cpp
    Created: 31 Mar 2023 9:36:21pm
    Author:  Scott Cohen

  ==============================================================================
*/

#include "SliderContainer.h"


/**/
SliderContainer::SliderContainer(bool stopAtEnd) : stopAtEnd(stopAtEnd)
{
    
    
    mSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(mSlider);
    addAndMakeVisible(mLabel);
    
    

}

/**/
void SliderContainer::setParameterToControl(juce::AudioProcessorValueTreeState& inVTS, const juce::String& inParamID)
{
    parameterID = inParamID;
    mLabel.setText(parameterID, juce::dontSendNotification);
    mAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(inVTS, parameterID, mSlider));
    
    mSlider.setRotaryParameters(juce::MathConstants<float>::pi * 1.2f, juce::MathConstants<float>::pi * 2.8f, stopAtEnd);
    
}

 
/**/
void SliderContainer::resized()
{
    
    auto bounds = getLocalBounds();
    int knobSize = mLookAndFeel.getKnobSize();

    mSlider.setBounds(bounds.removeFromTop(getHeight() * .8f));
    mSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, knobSize, mSlider.getHeight() * 0.03f);

    mLabel.setBounds(bounds);
    mLabel.setFont(Font(14.0f));
    mLabel.setColour(Label::textColourId, Colours::black);


}

void SliderContainer::setSliderStyle(juce::Slider::SliderStyle style) {
    mSlider.setSliderStyle(style);
}


const juce::String &SliderContainer::getParameterID() const {
    return parameterID;
}

juce::Slider &SliderContainer::getSlider() {
    return mSlider;
}




//

