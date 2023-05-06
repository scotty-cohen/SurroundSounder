/*
  ==============================================================================

    ParameterManager.cpp
    Created: 1 Apr 2023 3:39:54pm
    Author:  Scott Cohen

  ==============================================================================
*/

#include "ParameterManager.h"
#include "ProcessorInterface.h"

ParameterManager::ParameterManager(ProcessorInterface *inAudioProcessor)
        : mProcessorInterface(inAudioProcessor) {
    mParameterState = std::make_unique<juce::AudioProcessorValueTreeState>(*mProcessorInterface->getAudioProcessor(),
                                                                           nullptr, juce::Identifier("ParameterState"),
                                                                           getParameterLayout());

}

ParameterManager::~ParameterManager() = default;


juce::AudioProcessorValueTreeState *ParameterManager::getTreeState() {
    return mParameterState.get();
}

/* */

juce::AudioProcessorValueTreeState::ParameterLayout ParameterManager::getParameterLayout() {
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    for (int i = 0; i < AppParameterID::TotalNumberParameters; i++) {
        
        layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(ParameterIDStrings[i], 1),
                                                               ParameterIDStrings[i],
                                                               ParameterMinimum[i],
                                                               ParameterMaximum[i],
                                                               ParameterDefault[i]));
        
    }
    
    return layout;
}

/* */

float ParameterManager::getCurrentParameterValue(AppParameterID inParameterID)
{
    return mParameterState->getRawParameterValue(ParameterIDStrings[inParameterID])->load();
}
