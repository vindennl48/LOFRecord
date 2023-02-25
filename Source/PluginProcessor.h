/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AudioRecorder.h"

//==============================================================================
/**
*/
class LOFRecordAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    LOFRecordAudioProcessor();
    ~LOFRecordAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // ----------------- mitch stuff -----------------
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
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
    bool isRecording() const;
    void isRecording(bool setRecording);
    void startRecording();
    void stopRecording();

    juce::AudioProcessorValueTreeState m_params;

    // create filepath string with a default location of the desktop and a default filename of "test.wav"
    juce::String m_directory = juce::File::getSpecialLocation(juce::File::userDesktopDirectory).getFullPathName() + "/default.wav";
    juce::String m_trackName = "default";
    juce::String m_debug = "none";
    float m_gain = 0;
    bool m_isRecording = false;
    bool m_startRecordingOnLaunch = false;
    bool m_syncWithOtherInstances = false;
    AudioRecorder m_recorder;

    static bool m_isRecordingGlobal;
    // ----------------- mitch stuff -----------------

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LOFRecordAudioProcessor)
};
