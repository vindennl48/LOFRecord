/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>


//==============================================================================
LOFRecordAudioProcessor::LOFRecordAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), m_params (*this, nullptr, "Parameters", createParameterLayout()),
                       m_recorder()
#endif
{
    // ----------------- mitch stuff -----------------
    // m_params.state = juce::ValueTree("MyAudioProcessor");
    // Add the directory valuetree child node to the state tree
    m_params.state.addChild(juce::ValueTree("directory"), -1, nullptr);
    m_params.state.addChild(juce::ValueTree("trackName"), -1, nullptr);
    // ----------------- mitch stuff -----------------
}

LOFRecordAudioProcessor::~LOFRecordAudioProcessor()
{
}

// ----------------- mitch stuff -----------------
// Create the parameter layout
juce::AudioProcessorValueTreeState::ParameterLayout LOFRecordAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    // layout.add(std::make_unique<juce::AudioParameterFloat>("gain", "Gain", 0.0f, 1.0f, 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "gain", 1 }, "Gain", 0.0f, 1.0f, 0.5f));
    layout.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID { "startRecordingOnLaunch", 1 }, "Start Recording On Launch", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID { "syncWithOtherInstances", 1 }, "Sync With Other Instances", false));
    return layout;
}

// Get the directory
const juce::String& LOFRecordAudioProcessor::getDirectory() const
{
    // return m_params.state.getChildWithName("directory").getProperty("value").toString();
    return m_directory;
}

// Set the directory
void LOFRecordAudioProcessor::setDirectory(const juce::String& path)
{
/*     // get current date as yymmdd
    juce::String date = juce::Time::getCurrentTime().formatted("%y%m%d");

    // strip filename from path
    juce::String filename = path.fromLastOccurrenceOf("/", false, false);
    // add date to beginning of filename
    filename = date + "_" + filename;
    // add filename to directory
    m_directory = path.upToLastOccurrenceOf("/", false, false) + "/" + filename; */

    // m_directory = path;
    // m_params.state.getChildWithName("directory").setProperty("value", m_directory, nullptr);
    m_params.state.setProperty("directory", path, nullptr);
    // m_debug = m_params.state.getProperty("directory").toString();
}

// Get the gain
float LOFRecordAudioProcessor::getGain() const
{
    return m_gain;
}

// Set the gain
void LOFRecordAudioProcessor::setGain(float gain)
{
    m_gain = gain;
    m_params.state.getChildWithName("gain").setProperty("value", m_gain, nullptr);
}

// Set the startrecordingonlaunch
void LOFRecordAudioProcessor::setStartRecordingOnLaunch(bool startRecordingOnLaunch)
{
    m_startRecordingOnLaunch = startRecordingOnLaunch;
    m_params.state.setProperty("startRecordingOnLaunch", m_startRecordingOnLaunch, nullptr);
}
// Get the startrecordingonlaunch
bool LOFRecordAudioProcessor::getStartRecordingOnLaunch() const
{
    return m_startRecordingOnLaunch;
}

// Set the syncwithotherinstances
void LOFRecordAudioProcessor::setSyncWithOtherInstances(bool syncWithOtherInstances)
{
    m_syncWithOtherInstances = syncWithOtherInstances;
    m_params.state.setProperty("syncWithOtherInstances", m_syncWithOtherInstances, nullptr);
}
// Get the syncwithotherinstances
bool LOFRecordAudioProcessor::getSyncWithOtherInstances() const
{
    return m_syncWithOtherInstances;
}

// Set m_trackName
void LOFRecordAudioProcessor::setTrackName(const juce::String& trackName)
{
    m_trackName = trackName;
    m_params.state.setProperty("trackName", m_trackName, nullptr);
}

// Get m_trackName
const juce::String& LOFRecordAudioProcessor::getTrackName() const
{
    return m_trackName;
}

// isRecording()
bool LOFRecordAudioProcessor::isRecording() const
{
    if (m_syncWithOtherInstances) {
        return m_isRecordingGlobal;
    }
    return m_isRecording;
}
void LOFRecordAudioProcessor::isRecording(bool setRecording)
{
    if (m_syncWithOtherInstances) {
        m_isRecordingGlobal = setRecording;
        m_isRecording = false;
    } else {
        m_isRecording = setRecording;
    }
}

// startRecording()
void LOFRecordAudioProcessor::startRecording()
{
    isRecording(true);
}

// stopRecording()
void LOFRecordAudioProcessor::stopRecording()
{
    isRecording(false);
}
// ----------------- mitch stuff -----------------

//==============================================================================
const juce::String LOFRecordAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LOFRecordAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LOFRecordAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LOFRecordAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LOFRecordAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LOFRecordAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LOFRecordAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LOFRecordAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LOFRecordAudioProcessor::getProgramName (int index)
{
    return {};
}

void LOFRecordAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void LOFRecordAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void LOFRecordAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LOFRecordAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
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

void LOFRecordAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // ----------------- mitch stuff -----------------
    //m_recorder.writeBufferToWav(buffer);
    // ----------------- mitch stuff -----------------

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool LOFRecordAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LOFRecordAudioProcessor::createEditor()
{
    return new LOFRecordAudioProcessorEditor (*this);
}

//==============================================================================
void LOFRecordAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // Write the state of the AudioProcessorValueTreeState to a memory stream
    juce::MemoryOutputStream stream(destData, true);
    m_params.state.writeToStream(stream);
}

void LOFRecordAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // Read the state from the data and replace the AudioProcessorValueTreeState state
    auto tree = juce::ValueTree::readFromData(data, size_t(sizeInBytes));
    if (tree.isValid()) {
        m_params.replaceState (tree);
        m_directory = m_params.state.getProperty("directory").toString();
        m_gain = m_params.state.getProperty("gain");
        m_startRecordingOnLaunch = m_params.state.getProperty("startRecordingOnLaunch");
        m_syncWithOtherInstances = m_params.state.getProperty("syncWithOtherInstances");
        m_trackName = m_params.state.getProperty("trackName").toString();
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LOFRecordAudioProcessor();
}

bool LOFRecordAudioProcessor::m_isRecordingGlobal = false;
