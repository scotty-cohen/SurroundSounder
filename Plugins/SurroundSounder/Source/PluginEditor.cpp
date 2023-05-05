/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ParameterDefines.h"



//==============================================================================
Week3SineGeneratorAudioProcessorEditor::Week3SineGeneratorAudioProcessorEditor (Week3SineGeneratorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setLookAndFeel(&mLookAndFeel);
    
    auto& tree_state = audioProcessor.getParameterManager()->getTreeState();

    for (int i = 0; i < audioProcessor.getParameters().size(); i++) {
        bool stopAtEnd = (i != AppParameterID::Pan); // Set stopAtEnd to false only for the Pan knob
        mSliderContainers.add(new SliderContainer(stopAtEnd));
        mSliderContainers[i]->setParameterToControl(tree_state, ParameterIDStrings[i]);
        addAndMakeVisible(mSliderContainers[i]);
    }
    
    mNumBussesComboBox.setNumBussesChangedCallback([this](int selectedNumBusses) {
        static_cast<Week3SineGeneratorAudioProcessor*>(&this->processor)->setNumBuses(selectedNumBusses);
    });


    addAndMakeVisible(mNumBussesComboBox);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 475);
}

Week3SineGeneratorAudioProcessorEditor::~Week3SineGeneratorAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void Week3SineGeneratorAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colour(194,220,226));
}

void Week3SineGeneratorAudioProcessorEditor::resized()
{
    
    // Remove the pan knob from the mSliderContainers array
    for (int i = 0; i < mSliderContainers.size(); ++i)
    {
        if (mSliderContainers[i]->getParameterID() == ParameterIDStrings[AppParameterID::Pan])
        {
            mPanKnobIndex = i;
            break;
        }
    }
    
    {
        auto area = getLocalBounds();
        


        if (mPanKnobIndex >= 0)
        {
            auto panKnobBounds = area.removeFromLeft(250).removeFromBottom(400).withY(40).withX(100); // Adjust the size and position of the pan knob
            mSliderContainers[mPanKnobIndex]->setBounds(panKnobBounds);
        }

        // Place the other knobs in the top-right corner
        auto topRightArea = area.removeFromTop(100).removeFromRight(300);
        topRightArea.removeFromTop(50);
        topRightArea.reduce(10, 10);// Adjust the size of this area as needed

        // Add the other sliders to the mFlexbox
        mFlexbox.items.clear();
        mFlexbox.flexWrap = juce::FlexBox::Wrap::wrap;
        for (int i = 0; i < mSliderContainers.size(); ++i)
        {
            if (i != mPanKnobIndex)
            {
                mFlexbox.items.add(juce::FlexItem(*mSliderContainers[i]).withMinHeight(75.0f).withMinWidth(75.0f).withFlex(1));
            }
        }

        mFlexbox.performLayout(topRightArea.toFloat());
        
        // Set ComboBox position and width
            int comboBoxWidth = topRightArea.getWidth()-200;
            int comboBoxHeight = 50; // Adjust the height as needed
            int comboBoxX = topRightArea.getX()+180;
            int comboBoxY = topRightArea.getBottom()+180; // 10 is the gap between the FlexBox and the ComboBox
            mNumBussesComboBox.setBounds(comboBoxX, comboBoxY, comboBoxWidth, comboBoxHeight);
        }
}


void Week3SineGeneratorAudioProcessorEditor::timerCallback()
{
    
}