
#include "NewTable.h"
#include "DataStore.h"
#include "CustomComponents.h"
#include "Debug.h"

NewTable::NewTable(int newID) : id(newID)
{
  addAndMakeVisible(table);

  table.setModel(this);
  table.setClickingTogglesRowSelection(false);
  table.setHeader([&]
  {
    auto header = std::make_unique<juce::TableHeaderComponent>();
    header->addColumn( "Track",     trackColumn,          133, 30, -1, juce::TableHeaderComponent::notSortable );
    header->addColumn( "Group",     groupColumn,          133, 30, -1, juce::TableHeaderComponent::notSortable );
    header->addColumn( "Directory", directoryColumn,      133, 30, -1, juce::TableHeaderComponent::notSortable );
    header->addColumn( "Record",    recordColumn,         133, 30, -1, juce::TableHeaderComponent::notSortable );
    header->addColumn( "On Launch", recordOnLaunchColumn, 133, 30, -1, juce::TableHeaderComponent::notSortable );
    header->addColumn( "On Play",   recordOnPlayColumn,   133, 30, -1, juce::TableHeaderComponent::notSortable );
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
  if (rowNumber == id) {
    g.fillAll(juce::Colours::lightblue);
  }
}

void NewTable::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) {
  // g.setColour(Colours::black);
  // g.setFont(14.0f);

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

  switch (columnId) {
    case trackColumn:
      if (existingComponentToUpdate == nullptr) {
        return new TrackNameTextField(rowNumber, "trackName-" + juce::String(rowNumber));
      }
      break;

    case groupColumn:
      if (existingComponentToUpdate == nullptr) {
        return new GroupNameTextField(rowNumber, "groupName-" + juce::String(rowNumber));
      }
      break;

    case directoryColumn:
      if (existingComponentToUpdate == nullptr) {
        return new DirectoryButton(rowNumber, "directory-" + juce::String(rowNumber));
      }
      break;

    case recordColumn:
      if (existingComponentToUpdate == nullptr) {
        return new RecordButton(rowNumber, "record-" + juce::String(rowNumber));
      }
      break;

    case recordOnLaunchColumn:
      if (existingComponentToUpdate == nullptr) {
        return new RecordOnLaunchButton(rowNumber, "recordOnLaunch-" + juce::String(rowNumber));
      }
      break;

    default:
      delete existingComponentToUpdate;
      existingComponentToUpdate = nullptr;
      return new juce::Label({}, "####");
  };
  return existingComponentToUpdate;
}
