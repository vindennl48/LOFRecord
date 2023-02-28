/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "TabInstance.h"


//==============================================================================
LOFRecordAudioProcessorEditor::LOFRecordAudioProcessorEditor (LOFRecordAudioProcessor& p)
    :   AudioProcessorEditor (&p),
        audioProcessor (p),
        tabbedComponent(juce::TabbedButtonBar::TabsAtTop),
        tabInstance()
{
    setSize(800, 400);
    
    auto bg_color = getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId);
    tabbedComponent.setBounds(getLocalBounds());
    tabbedComponent.addTab("Instances", bg_color, &tabInstance, true);
    tabbedComponent.addTab("Recorded",  bg_color, new Component(), true);
    tabbedComponent.addTab("Editor",    bg_color, new Component(), true);
    addAndMakeVisible(tabbedComponent);
}

/*
LOFRecordAudioProcessorEditor::LOFRecordAudioProcessorEditor (LOFRecordAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 500);
    
    // variable to adjust vertical spacing
    int y = 10;

    titleLabel.setJustificationType(juce::Justification::centred);
    titleLabel.setFont(30.0f);
    titleLabel.setBounds(20, y, getWidth() - 40, 30);

    y += 30 + 10;
    songNameLabel.setBounds(20, y, getWidth() - 40, 30);
    y += 30 + 10;
    songNameTextBox.setBounds(20, y, getWidth() - 40, 30);
    songNameTextBox.setText(audioProcessor.getSongName(), false);
    songNameTextBox.setTextToShowWhenEmpty("default", juce::Colours::grey);
    songNameTextBox.onTextChange = [&] {
        audioProcessor.setSongName(songNameTextBox.getText());
    };

    y += 30 + 10;
    directoryLabel.setBounds(20, y, getWidth() - 40, 30);
    y += 30 + 10;
    directoryTextBox.setBounds(20, y, getWidth() - 40, 30);
    // set directoryTextBox to audioProcessor.getDirectory()
    directoryTextBox.setText(audioProcessor.getDirectory(), false);
    directoryTextBox.setTextToShowWhenEmpty("/Users/<USER>/Desktop", juce::Colours::grey);
    directoryTextBox.onTextChange = [&] {
        audioProcessor.setDirectory(directoryTextBox.getText());
    };

    y += 30 + 10;
    directoryButton.setBounds(20, y, getWidth() - 40, 30);
    directoryButton.onClick = [&] {
        directoryChooser.browseForDirectory();
        if (directoryChooser.getResult().exists()) {
            directoryTextBox.setText(directoryChooser.getResult().getFullPathName(), false);
            audioProcessor.setDirectory(directoryChooser.getResult().getFullPathName());
        }
    };

    y += 30 + 10;
    trackNameLabel.setBounds(20, y, getWidth() - 40, 30);
    y += 30 + 10;
    trackNameTextBox.setBounds(20, y, getWidth() - 40, 30);
    trackNameTextBox.setText(audioProcessor.getTrackName(), false);
    trackNameTextBox.setTextToShowWhenEmpty("default", juce::Colours::grey);
    trackNameTextBox.onTextChange = [&] {
        audioProcessor.setTrackName(trackNameTextBox.getText());
    };

    y += 30 + 10;
    recordingStatusLabel.setJustificationType(juce::Justification::centred);
    recordingStatusLabel.setFont(20.0f);
    recordingStatusLabel.setBounds(20, y, getWidth() - 40, 30);

    y += 30 + 10;
    recordingButton.setBounds(20, y, getWidth() - 40, 30);
    recordingButton.onClick = [&] {
        if (audioProcessor.isRecording()) {
            audioProcessor.stopRecording();
        } else {
            if (audioProcessor.getSyncWithOtherInstances()) {
                // set m_timeGlobal
                audioProcessor.m_timeGlobal = juce::Time::getCurrentTime().toMilliseconds() % 86400000;
            }
            audioProcessor.startRecording();
        }
    };

    y += 30 + 10;
    startRecordingOnLaunchButton.setBounds(20, y, getWidth() - 40, 30);
    startRecordingOnLaunchButton.setToggleState(audioProcessor.getStartRecordingOnLaunch(), juce::dontSendNotification);
    startRecordingOnLaunchButton.onClick = [&] {
        audioProcessor.setStartRecordingOnLaunch(startRecordingOnLaunchButton.getToggleState());
    };

    y += 30 + 10;
    syncWithOtherInstancesButton.setBounds(20, y, getWidth() - 40, 30);
    syncWithOtherInstancesButton.setToggleState(audioProcessor.getSyncWithOtherInstances(), juce::dontSendNotification);
    syncWithOtherInstancesButton.onClick = [&] {
        audioProcessor.setSyncWithOtherInstances(syncWithOtherInstancesButton.getToggleState());
        songNameTextBox.setText(audioProcessor.getSongName(), false); // update songNameTextBox
    };

    // y += 30 + 10;
    // debugTextBox.setBounds(20, y, getWidth() - 40, 30);
    // y += 30 + 10;
    // debugTextBox2.setBounds(20, y, getWidth() - 40, 30);

    addAndMakeVisible(titleLabel);
    addAndMakeVisible(songNameLabel);
    addAndMakeVisible(songNameTextBox);
    addAndMakeVisible(directoryLabel);
    addAndMakeVisible(directoryTextBox);
    addAndMakeVisible(directoryButton);
    addAndMakeVisible(trackNameLabel);
    addAndMakeVisible(trackNameTextBox);
    addAndMakeVisible(recordingStatusLabel);
    addAndMakeVisible(recordingButton);
    addAndMakeVisible(startRecordingOnLaunchButton);
    addAndMakeVisible(syncWithOtherInstancesButton);

    // addAndMakeVisible(debugTextBox);
    // addAndMakeVisible(debugTextBox2);
}
*/

LOFRecordAudioProcessorEditor::~LOFRecordAudioProcessorEditor()
{
}

//==============================================================================
void LOFRecordAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
    g.setFont (24.0f);
/*
    // trackNameTextBox.setText(audioProcessor.m_debug, false);

    songNameTextBox.setText(audioProcessor.getSongName(), false);
    trackNameTextBox.setText(audioProcessor.getTrackName(), false);

    if (audioProcessor.isRecording())
    {
        recordingStatusLabel.setText("RECORDING!", juce::dontSendNotification);
        recordingStatusLabel.setColour(juce::Label::textColourId, juce::Colours::red);

        recordingButton.setButtonText("Stop Recording");

        // disable checkboxes
        startRecordingOnLaunchButton.setEnabled(false);
        syncWithOtherInstancesButton.setEnabled(false);

        // disable textboxes
        songNameTextBox.setEnabled(false);
        directoryTextBox.setEnabled(false);
        trackNameTextBox.setEnabled(false);

        // disable directoryButton
        directoryButton.setEnabled(false);
    }
    else
    {
        recordingStatusLabel.setText("Not Recording..", juce::dontSendNotification);
        recordingStatusLabel.setColour(juce::Label::textColourId, juce::Colours::black);

        recordingButton.setButtonText("Start Recording");

        // enable checkboxes
        startRecordingOnLaunchButton.setEnabled(true);
        syncWithOtherInstancesButton.setEnabled(true);

        // enable textboxes
        songNameTextBox.setEnabled(true);
        directoryTextBox.setEnabled(true);
        trackNameTextBox.setEnabled(true);

        // enable directoryButton
        directoryButton.setEnabled(true);
    }

    // debugTextBox.setText(audioProcessor.m_params.state.getProperty("songName").toString(), false);
    // debugTextBox2.setText(audioProcessor.m_params.state.getProperty("songNameGlobal").toString(), false);

*/
}

void LOFRecordAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
