/*
  ==============================================================================

    Panning.cpp
    Created: 1 Apr 2023 7:04:12pm
    Author:  Scott Cohen

  ==============================================================================
*/

#include "Panning.h"
#include <JuceHeader.h>

Panning::Panning(juce::AudioProcessor* inAudioProcessor)
{
    mAudioProcessor = inAudioProcessor;
}

Panning::~Panning() = default;

void Panning::panAudioBuffer(juce::AudioBuffer<float> &buffer, float panPosition, int numBuses, float spread) {


    //the width of a 'notch' in the slider
    // Calculate the notch overlap based on the spread value (0 to 1)
    float notchOverlap = spread * (1.0f / numBuses);

    // Calculate the width of a 'notch' in the slider
    auto notch = (1.0f / numBuses) + notchOverlap;

    // Calculate the home positions of each bus on the slider
    std::vector<float> homePositions(numBuses);
    for (int i = 0; i < numBuses; ++i) {
        homePositions[i] = (1.0f / numBuses) * i;
    }


    //normalized slider position (0 - 1)
    auto sliderPosition = panPosition;

    std::vector<double> levelsL(numBuses);
    std::vector<double> levelsR(numBuses);


    for (int i = 0; i < numBuses; ++i) {

        double wrapAroundSliderPosition = sliderPosition > homePositions[i] ? sliderPosition - 1 : sliderPosition;
        double distance = std::min(static_cast<double>(std::abs(homePositions[i] - sliderPosition)),
                                   static_cast<double>(std::abs(
                                           homePositions[i] - wrapAroundSliderPosition)));// Wrap-around effect;


        double levelL = juce::jlimit(0.0, 1.0, distance / notch);
        double levelR = juce::jlimit(0.0, 1.0, distance / notch);

        levelL = 1 - levelL;
        levelR = 1 - levelR;

        levelsL[i] = levelL;
        levelsR[i] = levelR;
    }

    for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
        auto left_sample = buffer.getSample(0, sample);
        auto right_sample = buffer.getSample(1, sample);


        for (int i = 0; i < numBuses; i++) {
            mBusBuffers[i].setSample(0, sample, (left_sample * levelsL[i]));
            mBusBuffers[i].setSample(1, sample, (right_sample * levelsR[i]));

        }

    }


}

void Panning::updateBusBuffers(juce::AudioBuffer<float>& buffer, int numBuses)
{
    // Create bus buffers with the same number of channels as the input buffer (assuming stereo)
    jassert(numBuses <= MAX_NUM_BUSES);
    
    for (int i = 0; i < numBuses; ++i) {
        mBusBuffers[i] = mAudioProcessor->getBusBuffer(buffer, false, i + 1);
    }
}
    
void Panning::setSmoothedPanValue(float smoothedPanValue)
{
    mSmoothedPanValue = smoothedPanValue;
}

void Panning::panDelayBuffer(juce::AudioBuffer<float> &buffer, float panPosition, int numBuses, float sizeAmount) {
    // Spread the wet signal across the buses

    DBG("Number of channels in buffer: " << buffer.getNumChannels());
    DBG("Number of buses: " << numBuses);

//    if (numBuses > buffer.getNumChannels()) {
//        DBG("Error: more buses than channels in the buffer.");
//        return;
//    }

    //the width of a 'notch' in the slider
    // Calculate the notch overlap based on the spread value (0 to 1)
    float notchOverlap = sizeAmount * (1.0f / numBuses);

    // Calculate the width of a 'notch' in the slider
    auto notch = (1.0f / numBuses) + notchOverlap;

    // Calculate the home positions of each bus on the slider
    std::vector<float> homePositions(numBuses);
    for (int i = 0; i < numBuses; ++i) {
        homePositions[i] = (1.0f / numBuses) * i;
    }


    //normalized slider position (0 - 1)
    auto sliderPosition = panPosition;

    std::vector<double> levelsL(numBuses);
    std::vector<double> levelsR(numBuses);


    for (int i = 0; i < numBuses; ++i) {

        double wrapAroundSliderPosition = sliderPosition > homePositions[i] ? sliderPosition - 1 : sliderPosition;
        double distance = std::min(static_cast<double>(std::abs(homePositions[i] - sliderPosition)),
                                   static_cast<double>(std::abs(
                                           homePositions[i] - wrapAroundSliderPosition)));// Wrap-around effect;


        double levelL = juce::jlimit(0.0, 1.0, distance / notch);
        double levelR = juce::jlimit(0.0, 1.0, distance / notch);

        levelL = 1 - levelL;
        levelR = 1 - levelR;

        levelsL[i] = levelL;
        levelsR[i] = levelR;
    }

    for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
        auto left_sample = buffer.getSample(0, sample);
        auto right_sample = buffer.getSample(1, sample);


        for (int i = 0; i < numBuses; i++) {
            mBusBuffers[i].setSample(0, sample, (left_sample * levelsL[i]));
            mBusBuffers[i].setSample(1, sample, (right_sample * levelsR[i]));

        }

    }

}