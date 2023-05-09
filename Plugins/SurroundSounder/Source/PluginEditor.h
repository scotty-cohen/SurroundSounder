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
#include "ProcessorInterface.h"

//==============================================================================
/**
*/
class SurroundSounderAudioProcessorEditor : public juce::AudioProcessorEditor,
                                            public juce::Timer {
public:
    SurroundSounderAudioProcessorEditor(SurroundSounderAudioProcessor &p);

    ~SurroundSounderAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics &) override;

    void resized() override;

    void timerCallback() override;

private:


    MyLookAndFeel mLookAndFeel;
    
    
    //Slider Container
    juce::OwnedArray<SliderContainer> mSliderContainers;

    //Flexbox for Delay Params
    juce::FlexBox mFlexbox;


    //Grab the pan knob out of the flexbox
    int mPanKnobIndex = -1;
    int mSignalSpreadIndex = -1;

    //Add Combobox for numbusses
    std::unique_ptr<NumBussesComboBox> mNumBussesComboBox;
    std::unique_ptr<ComboBoxParameterAttachment> mBoxAttachment;

    SurroundSounderAudioProcessor &audioProcessor;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SurroundSounderAudioProcessorEditor)
};
