/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Listeners.h"
#include "WavSave.h"

//==============================================================================

class LOFRecordAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    int id = 0;                                  // instance ID
    juce::AudioProcessorValueTreeState m_params; // save settings
    Listeners* listeners;                        // link GUI with settings
    WavSave* wavSave;                            // save wav file
    bool isRecording = false;                    // less overhead to use this

    LOFRecordAudioProcessor();
    ~LOFRecordAudioProcessor() override;

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    // void startRecording();
    // void stopRecording();
    // bool isRecording() const;
    // void isRecording(bool isRecording);

    // // should be used with front-end record button
    // void Record(bool shouldRecord);

private:
    bool isFirstLaunch = true;  // only true on first launch

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // juce::String createFilename();

// UNUSED
//==============================================================================
public:
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

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
//==============================================================================

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LOFRecordAudioProcessor)
};
