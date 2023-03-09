
#include "NewTable.h"
#include "DataStore.h"
#include "CustomComponents.h"
#include "TextBox.h"
#include "ToggleButton.h"
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
  return DataStore::getInstance()->size();
}

void NewTable::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) {
  if (id == DataStore::getInstance()->getIDFromPos(rowNumber)) {
    g.fillAll(juce::Colours::lightblue);
  }
}

void NewTable::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) {
  g.setColour(juce::Colours::black);
  g.setFont(14.0f);

  switch (columnId) {
    case currentColumn:
      if (id == DataStore::getInstance()->getIDFromPos(rowNumber)) {
        g.drawText(">>", 0, 0, width, height, juce::Justification::centred, true);
      }
      break;
  };

  // auto track = DataStore::getInstance()->getTrack(rowNumber);
  // switch (columnId) {
    // case trackColumn:
      // g.drawText(track->getName(), 2, 0, width - 4, height, Justification::centredLeft, true);
      // break;
    // case groupColumn:
      // g.drawText(track->getGroup(), 2, 0, width - 4, height, Justification::centredLeft, true);
      // break;
    // case directoryColumn:
      // g.drawText(track->getDirectory(), 2, 0, width - 4, height, Justification::centredLeft, true);
      // break;
    // case recordOnLaunchColumn:
      // g.drawText(track->getRecordOnLaunch() ? "Yes" : "No", 2, 0, width - 4, height, Justification::centredLeft, true);
      // break;
    // case recordOnPlayColumn:
      // g.drawText(track->getRecordOnPlay() ? "Yes" : "No", 2, 0, width - 4, height, Justification::centredLeft, true);
      // break;
  // }
}

juce::Component* NewTable::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, juce::Component* existingComponentToUpdate) {
  // printToConsole(S("----> ") + S("rowNumber: ") + S(rowNumber) + S(", DS Size: ") + S(DataStore::getInstance()->size()));
  if (rowNumber >= DataStore::getInstance()->size()) return nullptr;
  int rowID = DataStore::getInstance()->getIDFromPos(rowNumber);
  if (rowID == -1) return nullptr;

  switch (columnId) {
    case trackColumn:
      if (existingComponentToUpdate == nullptr) {
        // return new TrackNameTextField(rowID, "trackName-" + juce::String(rowID));
        return new TextBox("trackName-" + juce::String(rowID), rowID, "trackName");
      }
      break;

    case groupColumn:
      if (existingComponentToUpdate == nullptr) {
        // return new GroupNameTextField(rowID, "groupName-" + juce::String(rowID));
        return new TextBox("groupName-" + juce::String(rowID), rowID, "groupName");
      }
      break;

    case directoryColumn:
      if (existingComponentToUpdate == nullptr) {
        return new DirectoryButton(rowID, "directory-" + juce::String(rowID));
      }
      break;

    case recordColumn:
      if (existingComponentToUpdate == nullptr) {
        // return new RecordButton(rowID, "record-" + juce::String(rowID));
        return new ToggleButton("record-" + juce::String(rowID), rowID, "isRecording");
      }
      break;

    case recordOnLaunchColumn:
      if (existingComponentToUpdate == nullptr) {
        // return new RecordOnLaunchButton(rowID, "recordOnLaunch-" + juce::String(rowID));
        return new ToggleButton("record2-" + juce::String(rowID), rowID, "isRecording");
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
