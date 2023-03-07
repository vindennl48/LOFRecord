
#pragma once

#include <JuceHeader.h>

class NewTable : public juce::Component,
                 public juce::TableListBoxModel
{
public:
  int id = 0;
  juce::TableListBox table;

  NewTable(int newID);

  void resized() override;

private:

  enum {
    currentColumn = 1,
    trackColumn,
    groupColumn,
    directoryColumn,
    recordColumn,
    recordOnLaunchColumn,
    recordOnPlayColumn
  };

  int getNumRows() override;
  void paintRowBackground (juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
  void paintCell (juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
  juce::Component* refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, juce::Component* existingComponentToUpdate) override;
};
