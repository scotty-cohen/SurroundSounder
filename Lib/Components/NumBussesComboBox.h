/*
  ==============================================================================

    NumBussesComboBox.h
    Created: 2 May 2023 11:55:51am
    Author:  Scott Cohen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ProcessorInterface.h"

class NumBussesComboBox : public juce::Component {
public:
    NumBussesComboBox(ProcessorInterface *inInterface);

    ~NumBussesComboBox() override;

    void resized() override;

private:
    std::unique_ptr<juce::ComboBox> comboBox;

    std::unique_ptr<ComboBoxParameterAttachment> mAttachment;

    ProcessorInterface *mProcessorInterface;
};
