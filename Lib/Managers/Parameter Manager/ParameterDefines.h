/*
  ==============================================================================
    ParameterDefines.h
    Created: 6 Mar 2023 5:07:21pm
    Author:  Scott Cohen
  ==============================================================================
*/

#pragma once

enum AppParameterID {
    Pan = 0,
    Size,
    Mix,
    Time,
    Feedback,
    Lowpass,
    Highpass,
    SignalSpread,
    BusCount,
    TotalNumberParameters,

};

static juce::Array<juce::String> ParameterIDStrings{
        "Pan",
        "Size",
        "Mix",
        "Time",
        "Feedback",
        "Lowpass",
        "Highpass",
        "Signal Spread",
        "Bus Count"
};

static juce::Array<float> ParameterMinimum{
        0.f,
        0.f,
        0.f,
        .1f,
        0.f,
        20.f,
        20.f,
        0.f,
        1.f
};

static juce::Array<float> ParameterMaximum{
        1.f,
        10.f,
        1.f,
        1.f,
        .95f,
        22000.f,
        22000.f,
        10.f,
        8.f
};

static juce::Array<float> ParameterDefault{
        .5f,
        0.f,
        .5f,
        .5f,
        .5f,
        22000.f,
        20.f,
        0.f,
        2.f
};
