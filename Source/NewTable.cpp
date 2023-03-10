
#include "NewTable.h"
#include "DataStore.h"
#include "TextBox.h"
#include "ToggleButton.h"
#include "SetPathButton.h"
#include "Debug.h"

NewTable::NewTable(int newID) : id(newID)
{
  addAndMakeVisible(table);

  table.setModel(this);
  table.setClickingTogglesRowSelection(false);
  table.setHeader([&]
  {
    auto header = std::make_unique<juce::TableHeaderComponent>();
    header->addColumn( "This",      currentColumn,         30, 30, -1, juce::TableHeaderComponent::notSortable );
    header->addColumn( "Track",     trackColumn,          128, 30, -1, juce::TableHeaderComponent::notSortable );
    header->addColumn( "Group",     groupColumn,          128, 30, -1, juce::TableHeaderComponent::notSortable );
    header->addColumn( "Directory", directoryColumn,      128, 30, -1, juce::TableHeaderComponent::notSortable );
    header->addColumn( "Record",    recordColumn,         128, 30, -1, juce::TableHeaderComponent::notSortable );
    header->addColumn( "On Launch", recordOnLaunchColumn, 128, 30, -1, juce::TableHeaderComponent::notSortable );
    header->addColumn( "On Play",   recordOnPlayColumn,   128, 30, -1, juce::TableHeaderComponent::notSortable );
    return header;
  }());
}

void NewTable::resized() {
  table.setBounds(getLocalBounds());
}

int NewTable::getNumRows() {
  return DS->size();
}

void NewTable::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) {
  if (id == DS->getIDFromPos(rowNumber)) {
    g.fillAll(juce::Colours::lightblue);
  }
}

void NewTable::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) {
  g.setColour(juce::Colours::black);
  g.setFont(14.0f);

  switch (columnId) {
    case currentColumn:
      if (id == DS->getIDFromPos(rowNumber)) {
        g.drawText(">>", 0, 0, width, height, juce::Justification::centred, true);
      }
      break;
  };
}

juce::Component* NewTable::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, juce::Component* existingComponentToUpdate) {
  if (rowNumber >= DS->size()) return nullptr;
  int rowID = DS->getIDFromPos(rowNumber);
  if (rowID == -1) return nullptr;

  switch (columnId) {
    case trackColumn:
      if (existingComponentToUpdate == nullptr) {
        return new TextBox("trackName-" + juce::String(rowID), rowID, "trackName", true);
      }
      break;

    case groupColumn:
      if (existingComponentToUpdate == nullptr) {
        return new TextBox("groupName-" + juce::String(rowID), rowID, "groupName", true);
      }
      break;

    case directoryColumn:
      if (existingComponentToUpdate == nullptr) {
        return new SetPathButton("directory-" + juce::String(rowID), rowID, "directory");
      }
      break;

    case recordColumn:
      if (existingComponentToUpdate == nullptr) {
        return new RecordButton("isRecording-" + juce::String(rowID), rowID, "isRecording");
      }
      break;

    case recordOnLaunchColumn:
      if (existingComponentToUpdate == nullptr) {
        return new ToggleButton("ON", "off", "recordOnLaunch-" + juce::String(rowID),
          rowID, "recordOnLaunch", juce::Colours::green);
      }
      break;

    case currentColumn:
      delete existingComponentToUpdate;
      existingComponentToUpdate = nullptr;
      break;

    default:
      delete existingComponentToUpdate;
      existingComponentToUpdate = nullptr;
      return new juce::Label({}, "####");
  };
  return existingComponentToUpdate;
}
