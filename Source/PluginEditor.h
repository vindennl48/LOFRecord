
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "NewTable.h"

class LOFRecordAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LOFRecordAudioProcessor& audioProcessor;
    NewTable table;
    
    LOFRecordAudioProcessorEditor (LOFRecordAudioProcessor&);
    ~LOFRecordAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LOFRecordAudioProcessorEditor)
};
