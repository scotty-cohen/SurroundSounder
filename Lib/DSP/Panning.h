/*
  ==============================================================================

    Panning.h
    Created: 1 Apr 2023 7:04:12pm
    Author:  Scott Cohen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "NumBussesComboBox.h"

static const size_t MAX_NUM_BUSES = 8;

class Panning {
public:
    
    Panning(juce::AudioProcessor* inAudioProcessor);
    ~Panning();
    
    /* */
    void panAudioBuffer(juce::AudioBuffer<float>& buffer, float panPosition, int numBuses);
    
    void setSmoothedPanValue(float smoothedPanValue);

private:
    
    /* */
    void updateBusBuffers(juce::AudioBuffer<float>& buffer, int numBuses);
    
    juce::AudioProcessor* mAudioProcessor;
    
    std::array<juce::AudioBuffer<float>, MAX_NUM_BUSES> mBusBuffers;
    
    float mSmoothedPanValue;
};
