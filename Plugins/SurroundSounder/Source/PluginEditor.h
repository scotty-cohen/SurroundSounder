/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SliderContainer.h"
#include "MyLookAndFeel.h"
#include "NumBussesComboBox.h"

//==============================================================================
/**
*/
class Week3SineGeneratorAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                public juce::Timer
{
public:
    Week3SineGeneratorAudioProcessorEditor (Week3SineGeneratorAudioProcessor&);
    ~Week3SineGeneratorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;
    
    void setNumBuses(int numBuses);

private:
    
    
    MyLookAndFeel mLookAndFeel;
    
    
    //Slider Container
    juce::OwnedArray<SliderContainer> mSliderContainers;
    
    //Flexbox for Delay Params
    juce::FlexBox mFlexbox;
    
    
    Week3SineGeneratorAudioProcessor& audioProcessor;
    
    //Grab the pan knob out of the flexbox
    int mPanKnobIndex = -1;
    
    //Add Combobox for numbusses
    NumBussesComboBox mNumBussesComboBox;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week3SineGeneratorAudioProcessorEditor)
};
