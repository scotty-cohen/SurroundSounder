/*
  ==============================================================================

    NumBussesComboBox.cpp
    Created: 2 May 2023 11:55:51am
    Author:  Scott Cohen

  ==============================================================================
*/

#include "NumBussesComboBox.h"
#include "ParameterManager.h"

NumBussesComboBox::NumBussesComboBox(ProcessorInterface *inInterface) : mProcessorInterface(inInterface) {
//
    comboBox = std::make_unique<ComboBox>();
    comboBox->addItem("1 Bus", 1);
    comboBox->addItem("2 Busses", 2);
    comboBox->addItem("3 Busses", 3);
    comboBox->addItem("4 Busses", 4);
    comboBox->addItem("5 Busses", 5);
    comboBox->addItem("6 Busses", 6);
    comboBox->addItem("7 Busses", 7);
    comboBox->addItem("8 Busses", 8);
    // Add more options if needed
    mAttachment.reset(new ComboBoxParameterAttachment(
            *mProcessorInterface->getParameterManager()->getTreeState()->getParameter("Bus Count"), *comboBox.get()));

    addAndMakeVisible(comboBox.get());
}

NumBussesComboBox::~NumBussesComboBox()
= default;

void NumBussesComboBox::resized()
{
    comboBox->setBounds(getLocalBounds());
}

