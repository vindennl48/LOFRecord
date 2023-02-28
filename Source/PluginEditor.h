/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class LOFRecordAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LOFRecordAudioProcessorEditor (LOFRecordAudioProcessor&);
    ~LOFRecordAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LOFRecordAudioProcessor& audioProcessor;
    juce::TabbedComponent tabbedComponent;

/*
    // ----------------- mitch stuff -----------------
    // ignore everything above this line
    // create a title label
    juce::Label titleLabel {"titleLabel", "LOF Recorder!"};

    // create a label for the song name
    juce::Label songNameLabel {"songNameLabel", "Song Name"};
    // create a text editor for the song name
    juce::TextEditor songNameTextBox {"songName"};

    // create a label for the directory
    juce::Label directoryLabel {"directoryLabel", "Directory"};
    // create a text editor for the directory to save audio to
    juce::TextEditor directoryTextBox {"directory"};
    // create a file chooser for the directory to save audio to
    juce::FileChooser directoryChooser {"Choose the directory to save audio to", juce::File::getSpecialLocation(juce::File::userDesktopDirectory), "*"};
    // create a button to open the file chooser
    juce::TextButton directoryButton {"Choose Directory"};

    // create a label for the track name
    juce::Label trackNameLabel {"trackNameLabel", "Track Name"};
    // create a text editor for the track name
    juce::TextEditor trackNameTextBox {"trackName"};

    // create a recording status label
    juce::Label recordingStatusLabel {"recordingStatusLabel", "Not Recording.."};
    // create a recording button
    juce::TextButton recordingButton {"Start Recording"};
    
    // create a toggle button for Start Recording On Launch
    juce::ToggleButton startRecordingOnLaunchButton {"Start Recording on Launch"};
    
    // create a toggle button for sync with other instances
    juce::ToggleButton syncWithOtherInstancesButton {"Sync with Other Instances"};
*/
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LOFRecordAudioProcessorEditor)
};
