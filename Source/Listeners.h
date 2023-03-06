
#pragma once

#include <JuceHeader.h>

class Listeners : public juce::AudioProcessorValueTreeState::Listener {
public:
    Listeners(int newID, juce::AudioProcessorValueTreeState& vts);
    ~Listeners();

    void parameterChanged(const juce::String& parameterID, float newValue) override;

private:
    int id = 0;
    juce::AudioProcessorValueTreeState& valueTreeState;
};
