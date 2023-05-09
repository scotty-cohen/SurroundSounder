/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
SurroundSounderAudioProcessorEditor::SurroundSounderAudioProcessorEditor(SurroundSounderAudioProcessor &p)
        : AudioProcessorEditor(&p), audioProcessor(p) {
    setLookAndFeel(&mLookAndFeel);


    auto tree_state = audioProcessor.getParameterManager()->getTreeState();

    for (int i = 0; i < audioProcessor.getParameters().size(); i++) {
        if (i == AppParameterID::BusCount) {
            continue;
        } else {
            bool stopAtEnd = (i != AppParameterID::Pan); // Set stopAtEnd to false only for the Pan knob
            mSliderContainers.add(new SliderContainer(stopAtEnd));
            mSliderContainers[i]->getSlider().addMouseListener(&mLookAndFeel, true);


            if (i == AppParameterID::Size) {
                float newMidPoint = 1.5; // Replace with the desired value at 80% point
                mSliderContainers[AppParameterID::Size]->getSlider().setSkewFactorFromMidPoint(newMidPoint);
                mSliderContainers[i]->getSlider().setSkewFactor(
                        0.00001); // Set the desired skew factor for the Size slider
            }

            mSliderContainers[i]->setParameterToControl(*tree_state, ParameterIDStrings[i]);
            addAndMakeVisible(mSliderContainers[i]);
        }
    }

    mSliderContainers[AppParameterID::SignalSpread]->setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    mNumBussesComboBox = std::make_unique<NumBussesComboBox>(&audioProcessor);
    addAndMakeVisible(mNumBussesComboBox.get());

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(800, 475);
}

SurroundSounderAudioProcessorEditor::~SurroundSounderAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void SurroundSounderAudioProcessorEditor::paint(juce::Graphics &g) {
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(Colour(194, 220, 226));
}

void SurroundSounderAudioProcessorEditor::resized() {

    // Remove the pan knob from the mSliderContainers array
    for (int i = 0; i < mSliderContainers.size(); ++i) {
        if (mSliderContainers[i]->getParameterID() == ParameterIDStrings[AppParameterID::Pan]) {
            mPanKnobIndex = i;
            break;
        }
    }

    {
        auto area = getLocalBounds();


        //Set Pan Knob position
        if (mPanKnobIndex >= 0) {
            auto panKnobBounds = area.removeFromLeft(250).removeFromBottom(400).withY(40).withX(
                    100); // Adjust the size and position of the pan knob
            mSliderContainers[mPanKnobIndex]->setBounds(panKnobBounds);
        }

        for (int i = 0; i < mSliderContainers.size(); ++i) {
            if (mSliderContainers[i]->getParameterID() == ParameterIDStrings[AppParameterID::SignalSpread]) {
                mSignalSpreadIndex = i;
                break;
            }
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
            if (i != mPanKnobIndex && i != mSignalSpreadIndex) {
                mFlexbox.items.add(
                        juce::FlexItem(*mSliderContainers[i]).withMinHeight(75.0f).withMinWidth(75.0f).withFlex(1));
            }
        }

        mFlexbox.performLayout(topRightArea.toFloat());

        // Set ComboBox position and width
        int comboBoxWidth = topRightArea.getWidth() - 175;
        int comboBoxHeight = 50; // Adjust the height as needed
        int comboBoxX = topRightArea.getX() + 180;
        int comboBoxY = topRightArea.getBottom() + 180; // 10 is the gap between the FlexBox and the ComboBox
        mNumBussesComboBox->setBounds(comboBoxX, comboBoxY, comboBoxWidth, comboBoxHeight);
    }

    //Set Linear slider position
    if (mSignalSpreadIndex >= 0) {
        int sliderWidth = 400; // Adjust this value for desired slider width
        int sliderHeight = 50; // Adjust this value for desired slider height
        int padding = 10; // Adjust this value for desired padding

        int x = getWidth() - sliderWidth - padding;
        int y = getHeight() - sliderHeight - padding;

        int offsetY = 75;
        y -= offsetY;

        mSliderContainers[mSignalSpreadIndex]->setBounds(x, y, sliderWidth, sliderHeight);
    }
}


void SurroundSounderAudioProcessorEditor::timerCallback() {

}

