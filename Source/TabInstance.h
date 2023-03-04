#pragma once

#include <JuceHeader.h>
// #include "PluginEditor.h"
#include "PluginProcessor.h"

using namespace juce;

class TableComponent  : public Component,
                        private TableListBoxModel
{
public:
  LOFRecordAudioProcessor& audioProcessor;

  TableComponent (LOFRecordAudioProcessor& p);
  void resized() override;

private:
  TableListBox table;

  enum {
      trackColumn = 1,
      groupColumn,
      recordingColumn,
      startOnLaunchColumn,
      startOnPlayColumn
  };

  int getNumRows() override;

  void paintRowBackground (Graphics&, int, int, int, bool) override;
  void paintCell (Graphics&, int, int, int, int, bool)     override;

  Component* refreshComponentForCell (
    int rowNumber,
    int columnId,
    bool,
    Component* existingComponentToUpdate
  ) override;
};



class TabInstance : public juce::Component {
public:
  LOFRecordAudioProcessor& audioProcessor;

  TabInstance(LOFRecordAudioProcessor& p) noexcept(false);

  void paint(juce::Graphics& g) override;
  void resized() override;

private:
  TableComponent table;
};
