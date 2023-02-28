#pragma once

#include <JuceHeader.h>

class TabInstance : public juce::Component {
public:
  TabInstance() {
    titleLabel.setJustificationType(juce::Justification::centred);
    // titleLabel.setBounds(20, 60, getWidth() - 40, 30);
    addAndMakeVisible(titleLabel);
  }

  void paint(juce::Graphics& g) override {
    g.fillAll (getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    // g.fillAll(juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (24.0f);
  }

  void resized() override {
    titleLabel.setBounds(20, 60, getWidth() - 40, 30);
  }

private:
  juce::Label titleLabel {"tabInstanceTitle", "Instances!"};
};
