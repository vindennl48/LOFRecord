

#include "PluginProcessor.h"
// #include "PluginEditor.h"
// #include <juce_core/juce_core.h>
// #include <juce_events/juce_events.h>


// Get the directory
const juce::String& LOFRecordAudioProcessor::getDirectory() const
{
    return m_directory;
}

// Set the directory
void LOFRecordAudioProcessor::setDirectory(const juce::String& path)
{
    // check to make sure path is a valid directory
    juce::File directory = juce::File(path);
    if (!directory.isDirectory())
    {
        return;
    }

    m_directory = path;
    // m_params.state.setProperty("directory", path, nullptr);
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
    // m_params.state.getChildWithName("gain").setProperty("value", m_gain, nullptr);
}

// Get the startrecordingonlaunch
bool LOFRecordAudioProcessor::getStartRecordingOnLaunch() const
{
    return m_startRecordingOnLaunch;
}

// Set the startrecordingonlaunch
void LOFRecordAudioProcessor::setStartRecordingOnLaunch(bool startRecordingOnLaunch)
{
    m_startRecordingOnLaunch = startRecordingOnLaunch;
    // m_params.state.setProperty("startRecordingOnLaunch", m_startRecordingOnLaunch, nullptr);
}

// Get the syncwithotherinstances
bool LOFRecordAudioProcessor::getSyncWithOtherInstances() const
{
    return m_syncWithOtherInstances;
}

// Set the syncwithotherinstances
void LOFRecordAudioProcessor::setSyncWithOtherInstances(bool syncWithOtherInstances)
{
    m_syncWithOtherInstances = syncWithOtherInstances;
    // m_params.state.setProperty("syncWithOtherInstances", m_syncWithOtherInstances, nullptr);
}

// Get m_trackName
const juce::String& LOFRecordAudioProcessor::getTrackName() const
{
    return m_trackName;
}

// Set m_trackName
void LOFRecordAudioProcessor::setTrackName(const juce::String& trackName)
{
    // set trackName to lowercase and replace all special characters with underscores
    m_trackName = trackName.toLowerCase().replaceCharacters(" !@#$%^&*(){}[]|\\:;\"'<>,.?/~`", "_____________________________");
    // m_trackName = trackName;
    // m_params.state.setProperty("trackName", m_trackName, nullptr);
}

// get song name
const juce::String& LOFRecordAudioProcessor::getSongName()
{
    if (getSyncWithOtherInstances()) {
        m_songName = m_songNameGlobal;
    }
    return m_songName;
}

// set song name
void LOFRecordAudioProcessor::setSongName(const juce::String& songName) {
    m_songName = songName.toLowerCase().replaceCharacters(" !@#$%^&*(){}[]|\\:;\"'<>,.?/~`", "_____________________________");
    // m_params.state.setProperty("songName", m_songName, nullptr);

    if (getSyncWithOtherInstances()) {
        m_songNameGlobal = m_songName;
    }
}

// isRecording()
bool LOFRecordAudioProcessor::isRecording()
{
    return m_isRecording;
}
void LOFRecordAudioProcessor::isRecording(bool setRecording)
{
    m_isRecording = setRecording;
}
