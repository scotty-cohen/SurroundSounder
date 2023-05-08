/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Delay.h"
#include "ParameterManager.h"
#include "Panning.h"
#include "NumBussesComboBox.h"
#include "ProcessorInterface.h"


//==============================================================================
/**
*/
class SurroundSounderAudioProcessor : public juce::AudioProcessor,
                                      public ProcessorInterface
#if JucePlugin_Enable_ARA
    , public juce::AudioProcessorARAExtension
#endif
{
public:
    //==============================================================================
    SurroundSounderAudioProcessor();

    ~SurroundSounderAudioProcessor() override;

    //==============================================================================
    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midi) override;

    /* */
    void setGain(float inGain);

    /* */
    float getGain();

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;

    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations

    bool isBusesLayoutSupported(const BusesLayout &layouts) const override;

#endif

    /**
     * Processor Interface Overrides
     */

    ParameterManager *getParameterManager() override;

    AudioProcessor *getAudioProcessor() override;

    //==============================================================================
    juce::AudioProcessorEditor *createEditor() override;

    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;

    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;


private:
    
    std::unique_ptr<Panning> mPanning;
        
    std::array<Delay, MAX_NUM_BUSES> mDelayL;
    std::array<Delay, MAX_NUM_BUSES> mDelayR;
    
    std::unique_ptr<ParameterManager> mParameterManager;
    
    int mNumBuses = 0;

    juce::SmoothedValue<float> mSmoothPanValue;
    juce::SmoothedValue<float> mSmoothSizeValue;
    

    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SurroundSounderAudioProcessor)
};
