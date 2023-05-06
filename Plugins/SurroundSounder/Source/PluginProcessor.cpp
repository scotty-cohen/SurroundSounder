/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
void SurroundSounderAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    mSmoothPanValue.reset(sampleRate, 0.01);
    mSmoothPanValue.setCurrentAndTargetValue(mParameterManager->getCurrentParameterValue(AppParameterID::Pan));


    for (auto &i: mDelayL) {
        i.initialize(sampleRate, samplesPerBlock);
    }

    for (auto &i: mDelayR) {
        i.initialize(sampleRate, samplesPerBlock);
    }
}


void SurroundSounderAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) {
    jassert(buffer.getNumChannels() == getTotalNumOutputChannels());

    mNumBuses = mParameterManager->getCurrentParameterValue(AppParameterID::BusCount);

    /* boiler plate stuff to not touch */
    juce::ScopedNoDenormals noDenormals;

    //clear the bus buffers so no screechy sounds
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    float pan = mParameterManager->getTreeState()->getParameterAsValue(
            ParameterIDStrings[AppParameterID::Pan]).getValue();

    mSmoothPanValue.setTargetValue(mParameterManager->getCurrentParameterValue(AppParameterID::Pan));
    mPanning->setSmoothedPanValue(mSmoothPanValue.getNextValue());

    mPanning->panAudioBuffer(buffer, pan, mNumBuses);

    for (int i = 0; i < mNumBuses; i++) {

        mDelayL[i].setParameters(mParameterManager->getCurrentParameterValue(AppParameterID::Time),
                                 mParameterManager->getCurrentParameterValue(AppParameterID::Feedback),
                                 mParameterManager->getCurrentParameterValue(AppParameterID::Mix),
                                 mParameterManager->getCurrentParameterValue(AppParameterID::Lowpass),
                                 mParameterManager->getCurrentParameterValue(AppParameterID::Highpass));

        mDelayR[i].setParameters(mParameterManager->getCurrentParameterValue(AppParameterID::Time),
                                 mParameterManager->getCurrentParameterValue(AppParameterID::Feedback),
                                 mParameterManager->getCurrentParameterValue(AppParameterID::Mix),
                                 mParameterManager->getCurrentParameterValue(AppParameterID::Lowpass),
                                 mParameterManager->getCurrentParameterValue(AppParameterID::Highpass));
        
        auto bus = getBusBuffer(buffer, false, i + 1);
        
        mDelayL[i].processBlock(bus.getWritePointer(0), bus.getNumSamples());
        mDelayR[i].processBlock(bus.getWritePointer(1), bus.getNumSamples());
        
    }
}

//==============================================================================
SurroundSounderAudioProcessor::SurroundSounderAudioProcessor() :
#ifndef JucePlugin_PreferredChannelConfigurations
        AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                               .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
                               .withOutput("Output", juce::AudioChannelSet::stereo(), true)

//This is where we add 4 extra output buses: "Name", Channel Config, Activated By Default
                               .withOutput("Bus #1", juce::AudioChannelSet::stereo(), true)
                               .withOutput("Bus #2", juce::AudioChannelSet::stereo(), true)
                               .withOutput("Bus #3", juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Bus #4",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Bus #5",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Bus #6",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Bus #7",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Bus #8",  juce::AudioChannelSet::stereo(), true)
#endif
                       )


{
    mParameterManager = std::make_unique<ParameterManager>(this);
    mPanning = std::make_unique<Panning>(this);
    mSmoothPanValue.reset(mParameterManager->getCurrentParameterValue(AppParameterID::Pan));

}

#endif
//{
//
//}


SurroundSounderAudioProcessor::~SurroundSounderAudioProcessor()
{
}


//==============================================================================
const juce::String SurroundSounderAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool SurroundSounderAudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool SurroundSounderAudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool SurroundSounderAudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double SurroundSounderAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int SurroundSounderAudioProcessor::getNumPrograms() {
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int SurroundSounderAudioProcessor::getCurrentProgram() {
    return 0;
}

void SurroundSounderAudioProcessor::setCurrentProgram(int index) {
}

const juce::String SurroundSounderAudioProcessor::getProgramName(int index) {
    return {};
}

void SurroundSounderAudioProcessor::changeProgramName(int index, const juce::String &newName) {
}

void SurroundSounderAudioProcessor::releaseResources() {
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations

bool SurroundSounderAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const {
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

//==============================================================================
bool SurroundSounderAudioProcessor::hasEditor() const {
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *SurroundSounderAudioProcessor::createEditor() {
    return new SurroundSounderAudioProcessorEditor(*this);
}

//==============================================================================
void SurroundSounderAudioProcessor::getStateInformation(juce::MemoryBlock &destData) {
    DBG ("Trying to save state");
    auto state = mParameterManager->getTreeState()->copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    DBG(xml->toString());
    copyXmlToBinary(*xml, destData);

}

void SurroundSounderAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {
    DBG ("Trying to load state");
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get()) {
        DBG(xmlState->toString());
        mParameterManager->getTreeState()->replaceState(juce::ValueTree::fromXml(*xmlState));
    }

}

ParameterManager *SurroundSounderAudioProcessor::getParameterManager() {
    return mParameterManager.get();
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SurroundSounderAudioProcessor();
}

AudioProcessor *SurroundSounderAudioProcessor::getAudioProcessor() {
    return this;
}
