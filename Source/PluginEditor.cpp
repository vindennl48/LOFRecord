
#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "DataStore.h"

LOFRecordAudioProcessorEditor::LOFRecordAudioProcessorEditor (LOFRecordAudioProcessor& p)
  : AudioProcessorEditor (&p),
    audioProcessor (p),
    table(p.id)
{
  // this will run every time the plugin window opens
  setSize(798, 400);

  addAndMakeVisible(table);
}


LOFRecordAudioProcessorEditor::~LOFRecordAudioProcessorEditor() {}

void LOFRecordAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
    g.setFont (24.0f);
}

void LOFRecordAudioProcessorEditor::resized() {
  table.setBounds(getLocalBounds());
}
