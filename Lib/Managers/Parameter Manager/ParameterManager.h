/*
  ==============================================================================

    ParameterManager.h
    Created: 1 Apr 2023 3:39:54pm
    Author:  Scott Cohen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ParameterDefines.h"

class ParameterManager{
public:
    
    /* */
    ParameterManager(juce::AudioProcessor* inOwnerProcessor);
    
    
    /* */
    juce::AudioProcessorValueTreeState::ParameterLayout getParameterLayout();
    
    /* */
    juce::AudioProcessorValueTreeState& getTreeState();
    
    /* */
    
    float getCurrentParameterValue(AppParameterID inParameterID);
    
private:
     


    juce::Array<std::atomic<float>*> mParameterValues;
    juce::AudioProcessorValueTreeState mParameterState;
    
};
