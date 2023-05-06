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

class ProcessorInterface;

class ParameterManager {
public:

    /* */
    ParameterManager(ProcessorInterface *inAudioProcessor);

    ~ParameterManager();


    /* */
    juce::AudioProcessorValueTreeState::ParameterLayout getParameterLayout();

    /* */
    juce::AudioProcessorValueTreeState *getTreeState();

    /* */
    
    float getCurrentParameterValue(AppParameterID inParameterID);
    
private:

    ProcessorInterface *mProcessorInterface;

    std::unique_ptr<juce::AudioProcessorValueTreeState> mParameterState;
    
};
