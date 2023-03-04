
#include "TabInstance.h"

TableComponent::TableComponent (LOFRecordAudioProcessor& p)
  : audioProcessor(p)
{
  addAndMakeVisible (table);

  table.setModel (this);
  table.setClickingTogglesRowSelection (false);
  table.setHeader ([&]
  {
    auto header = std::make_unique<TableHeaderComponent>();
    header->addColumn ("Track",           trackColumn,         120, 30, -1, TableHeaderComponent::notSortable);
    header->addColumn ("Group",           groupColumn,         120, 30, -1, TableHeaderComponent::notSortable);
    header->addColumn ("Recording",       recordingColumn,     120, 30, -1, TableHeaderComponent::notSortable);
    header->addColumn ("Start on Launch", startOnLaunchColumn, 120, 30, -1, TableHeaderComponent::notSortable);
    header->addColumn ("Start on Play",   startOnPlayColumn,   120, 30, -1, TableHeaderComponent::notSortable);
    return header;
  }());
}

void TableComponent::resized() { table.setBounds (getLocalBounds()); }

int TableComponent::getNumRows() { return (int) 10; }

void TableComponent::paintRowBackground (Graphics&, int, int, int, bool) {}
void TableComponent::paintCell (Graphics&, int, int, int, int, bool)     {}

Component* TableComponent::refreshComponentForCell (
  int rowNumber,
  int columnId,
  bool,
  Component* existingComponentToUpdate)
{
  delete existingComponentToUpdate;

  return new Label ({}, [&]
  {
    switch (columnId)
    {
      case trackColumn:         return String("track");
      case groupColumn:         return String("group");
      case recordingColumn:     return String("is recording");
      case startOnLaunchColumn: return String("yes");
      case startOnPlayColumn:   return String("no");
      default: break;
    }

    jassertfalse;
    return String();
  }());
}


TabInstance::TabInstance(LOFRecordAudioProcessor& p)
  : table(p),
    audioProcessor(p)
{
  addAndMakeVisible(table);
}

void TabInstance::paint(juce::Graphics& g) {
  g.fillAll (getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
  // g.fillAll(juce::Colours::black);
  g.setColour (juce::Colours::white);
  g.setFont (24.0f);
}

/**
* Set size, position, and font of comopnents
*/
void TabInstance::resized() {
  table.setBounds(getLocalBounds());
}
