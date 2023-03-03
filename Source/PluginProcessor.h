/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
// #include "AudioRecorder2.h"
#include "WavSave.h"

//==============================================================================

class LOFRecordAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    LOFRecordAudioProcessor();
    ~LOFRecordAudioProcessor() override;

    // GET SET
    //==============================================================================
    const juce::String& getDirectory() const;
    void setDirectory(const juce::String& path);

    float getGain() const;
    void setGain(float gain);

    bool getStartRecordingOnLaunch() const;
    void setStartRecordingOnLaunch(bool startRecordingOnLaunch);

    bool getSyncWithOtherInstances() const;
    void setSyncWithOtherInstances(bool syncWithOtherInstances);

    const juce::String& getTrackName() const;
    void setTrackName(const juce::String& trackName);

    const juce::String& getSongName();
    void setSongName(const juce::String& songName);

    bool isRecording();
    void isRecording(bool setRecording);
    //==============================================================================

    void startRecording();
    void stopRecording();

    // should be used with front-end record button
    void Record(bool shouldRecord);

    // to save the state of the plugin
    juce::AudioProcessorValueTreeState m_params;

    // STATIC
    static bool m_isRecordingGlobal;
    static juce::int64 m_timeGlobal;

private:
    juce::String createFilename();

    // AudioRecorder2 m_recorder;  // handles writing audio to disk
    WavSave m_recorder;  // handles writing audio to disk
    juce::String m_directory = juce::File::getSpecialLocation(juce::File::userDesktopDirectory).getFullPathName();
    juce::String m_trackName = "default";
    juce::String m_songName = "default";

    float m_gain = 0;  // not used
    bool m_isRecording = false;
    bool m_startRecordingOnLaunch = false;
    bool m_syncWithOtherInstances = false;
    bool m_firstLaunch = true;

    juce::String m_debug = "debug";
    
    // STATIC
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    static juce::String m_songNameGlobal;
    // ----------------- mitch stuff -----------------

public:
    // UNUSED
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    //==============================================================================

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LOFRecordAudioProcessor)
};
