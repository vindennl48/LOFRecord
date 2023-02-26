/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>

juce::String LOFRecordAudioProcessor::m_songNameGlobal = "default";
bool LOFRecordAudioProcessor::m_isRecordingGlobal = false;
juce::int64 LOFRecordAudioProcessor::m_timeGlobal = 0;
std::vector<LOFRecordAudioProcessor*> LOFRecordAudioProcessor::m_processors;

//==============================================================================
LOFRecordAudioProcessor::LOFRecordAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor (
        BusesProperties()
        #if ! JucePlugin_IsMidiEffect
            #if ! JucePlugin_IsSynth
                .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
            #endif
            .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
        #endif
    ),
    m_params (
        *this, nullptr,
        "Parameters",
        createParameterLayout()
    ),
    m_recorder()
#endif
{
    // ----------------- mitch stuff -----------------
    // m_params.state = juce::ValueTree("MyAudioProcessor");
    // Add the directory valuetree child node to the state tree
    m_params.state.addChild(juce::ValueTree("directory"), -1, nullptr);
    m_params.state.addChild(juce::ValueTree("trackName"), -1, nullptr);
    m_params.state.addChild(juce::ValueTree("songName"), -1, nullptr);
    // ----------------- mitch stuff -----------------

    // add this new instance to m_processors
    m_processors.push_back(this);
}

LOFRecordAudioProcessor::~LOFRecordAudioProcessor()
{
}

// ----------------- mitch stuff -----------------
// Create the parameter layout
juce::AudioProcessorValueTreeState::ParameterLayout LOFRecordAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "gain", 1 }, "Gain", 0.0f, 1.0f, 0.5f));
    layout.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID { "startRecordingOnLaunch", 1 }, "Start Recording On Launch", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID { "syncWithOtherInstances", 1 }, "Sync With Other Instances", false));
    return layout;
}

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
    if (m_isRecording) m_recorder.writeBufferToWav(buffer);

    // switch on recording if synced with other instances
    if (getSyncWithOtherInstances()) {
        if (m_isRecordingGlobal) {
            startRecording();
        } else {
            stopRecording();
        }
    }
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

// Save the state of the plugin
void LOFRecordAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // Write the state of the AudioProcessorValueTreeState to a memory stream
    juce::MemoryOutputStream stream(destData, true);
    m_params.state.writeToStream(stream);
}

// Load the state of the plugin
void LOFRecordAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // Read the state from the data and replace the AudioProcessorValueTreeState state
    auto tree = juce::ValueTree::readFromData(data, size_t(sizeInBytes));
    if (tree.isValid()) {
        m_params.replaceState (tree);
        m_directory              = m_params.state.getProperty("directory").toString();
        m_gain                   = m_params.state.getProperty("gain");
        m_startRecordingOnLaunch = m_params.state.getProperty("startRecordingOnLaunch");
        m_syncWithOtherInstances = m_params.state.getProperty("syncWithOtherInstances");
        m_trackName              = m_params.state.getProperty("trackName").toString();
        m_songName               = m_params.state.getProperty("songName").toString();

        // if synced with other instances, copy song name to global song name
        if (getSyncWithOtherInstances()) {
            m_songNameGlobal = m_songName;
        }

        // start recording on launch if the user has selected that option
        if (m_startRecordingOnLaunch && m_firstLaunch) {
            startRecording();
        }
        m_firstLaunch = false;
    }
}

void LOFRecordAudioProcessor::startRecording()
{
    if (isRecording()) return;
    if (getSyncWithOtherInstances()) m_isRecordingGlobal = true;

    // create filepath
    juce::String filename = createFilename();
    juce::String filepath = m_directory + "/" + filename;
    m_recorder.startRecording(filepath);
    isRecording(true);
}

void LOFRecordAudioProcessor::stopRecording()
{
    if (!isRecording()) return;
    if (getSyncWithOtherInstances()) m_isRecordingGlobal = false;

    m_recorder.stopRecording();
    isRecording(false);
}

// create the filename from the directory and track name
juce::String LOFRecordAudioProcessor::createFilename()
{
    // format is going to be date-time-songname-trackname-count.wav

    // get current date as yymmdd
    juce::String date = juce::Time::getCurrentTime().formatted("%y%m%d");

    // get current time of day in ms starting from midnight
    juce::int64 time;
    if (m_syncWithOtherInstances) {
        time = m_timeGlobal;
    } else {
        time = juce::Time::getCurrentTime().toMilliseconds() % 86400000;
    }

    // join date, time, song name, track name
    juce::String filename = date + "-" + juce::String(time) + "-" + getSongName() + "-" + getTrackName() + "-";

    // get the number of files in the directory starting with filename
    juce::File directory = juce::File(getDirectory());
    // create filename search string that removes time from the middle
    juce::String search = date + "-*" + "-" + getSongName() + "-" + getTrackName() + "-*";
    // count all files in directory that start with search string
    juce::Array<juce::File> files = directory.findChildFiles(juce::File::TypesOfFileToFind::findFiles, true, search);
    // set a variable 'count' to the number of files found
    int count = files.size();

    // join filename and count with 3 digits and .wav, pad with zeros if needed
    filename = filename + juce::String(count).paddedLeft('0', 3) + ".wav";

    return filename;
}
