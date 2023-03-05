
#pragma once

#include <JuceHeader.h>

class NewTable : public juce::Component,
                 public juce::TableListBoxModel
{
public:
  juce::TableListBox table;

  NewTable();

  void resized() override;

private:

  enum {
    trackColumn = 1,
    groupColumn,
    directoryColumn,
    recordOnLaunchColumn,
    recordOnPlayColumn
  };

  int getNumRows() override;
  void paintRowBackground (juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
  void paintCell (juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
  juce::Component* refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, juce::Component* existingComponentToUpdate) override;
};
