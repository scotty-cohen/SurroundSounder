/*
  ==============================================================================

    NumBussesComboBox.h
    Created: 2 May 2023 11:55:51am
    Author:  Scott Cohen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class NumBussesComboBox : public juce::Component
{
public:
    NumBussesComboBox();
    ~NumBussesComboBox();

    void resized() override;

    using NumBussesChangedCallback = std::function<void(int)>;
    void setNumBussesChangedCallback(std::function<void(int)> callback);

private:
    juce::ComboBox comboBox;
    
    std::function<void(int)> numBussesChangedCallback;

    void comboBoxChanged();
};
