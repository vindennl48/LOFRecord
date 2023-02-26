/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

std::vector<LOFRecordAudioProcessorEditor*> LOFRecordAudioProcessorEditor::m_editors;

//==============================================================================
LOFRecordAudioProcessorEditor::LOFRecordAudioProcessorEditor (LOFRecordAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // add this instance to list of m_editors
    m_editors.push_back(this);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 500);  // change back to 500 to remove debug
    
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

LOFRecordAudioProcessorEditor::~LOFRecordAudioProcessorEditor()
{
}

//==============================================================================
void LOFRecordAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
    g.setFont (24.0f);

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
}

/* void LOFRecordAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (24.0f);

    // ----------------- mitch stuff -----------------
    // drawFittedText for a title
    g.drawFittedText ("Recording Plugin!", getLocalBounds(), juce::Justification::centredTop, 1);

    // variable to adjust vertical spacing
    int y = 50;

    // add the textbox with 20px of padding that adjusts to the center on resize
    filepathTextBox.setBounds(20, y, getWidth() - 40, 30);
    filepathTextBox.setText(audioProcessor.getFilepath());
    addAndMakeVisible(filepathTextBox);

    y += 30 + 10;

    // show the save button
    saveButton.setBounds(20, y, getWidth() - 40, 30);
    addAndMakeVisible(saveButton);

    // when the save button is clicked, save the wav file
    saveButton.onClick = [this] {
        // open the file chooser
        if (fileChooser.browseForFileToSave(true))
        {
            // get the file
            juce::File file = fileChooser.getResult();
            // save the wav file
            audioProcessor.setFilepath(file.getFullPathName());
            // update debug textbox with the filepath
            debugTextBox.setText(audioProcessor.getFilepath());
        }
    };

    y += 30 + 10;

    // add the recording label and justify it to the center
    recordingLabel.setBounds(20, y, getWidth() - 40, 50);
    recordingLabel.setJustificationType(juce::Justification::centred);
    recordingLabel.setFont(20.0f);
    addAndMakeVisible(recordingLabel);
    // if isRecording is true, set the text to "recording" and flash the text
    if (audioProcessor.isRecording)
    {
        recordingLabel.setText("RECORDING!", juce::dontSendNotification);
        recordingLabel.setColour(juce::Label::textColourId, juce::Colours::red);
    }
    else
    {
        recordingLabel.setText("Not Recording..", juce::dontSendNotification);
        recordingLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    }

    // add the recording button and justify it to the center
    y += 50 + 10;
    recordingButton.setBounds(20, y, getWidth() - 40, 30);
    addAndMakeVisible(recordingButton);
    // when clicked, toggle isRecording and update the button text
    recordingButton.onClick = [this] {
        audioProcessor.isRecording = !audioProcessor.isRecording;
        if (audioProcessor.isRecording)
        {
            recordingButton.setButtonText("Stop Recording");
            audioProcessor.m_recorder.startRecording(audioProcessor.m_filepath);
        }
        else
        {
            recordingButton.setButtonText("Start Recording");
            audioProcessor.m_recorder.stopRecording();
        }
    };
} */

void LOFRecordAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
