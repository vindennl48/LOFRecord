
#pragma once

#include <JuceHeader.h>
#include "Debug.h"
#include "DataStore.h"

class CustRow {
public:
  int id = 0;

  juce::TextEditor   trackName;
  juce::TextEditor   groupName;
  juce::TextEditor   directory;
  juce::ToggleButton recordOnLaunch;
  juce::ToggleButton recordOnPlay;

  CustRow(int newID)
    : id(newID),
      trackName("trackName"),
      groupName("groupName")
  {
    int x = 0; int y = 40+(40*id);

    trackName.setBounds(x, y, 150, 30);
    trackName.setText(DataStore::getInstance()->getTrackName(id), false);
    trackName.onTextChange = [&] {
      DataStore::getInstance()->setTrackName(id, trackName.getText()); 
    };
    x += trackName.getWidth();

    groupName.setBounds(x, y, 150, 30);
    groupName.setText(DataStore::getInstance()->getGroupName(id), false);
    groupName.onTextChange = [&] {
      DataStore::getInstance()->setGroupName(id, groupName.getText()); 
    };
    x += groupName.getWidth();

    directory.setBounds(x, y, 150, 30);
    directory.setText(DataStore::getInstance()->getDirectory(id), false);
    directory.onTextChange = [&] {
      DataStore::getInstance()->setDirectory(id, directory.getText()); 
    };
    x += directory.getWidth();

    recordOnLaunch.setBounds(x, y, 150, 30);
    recordOnLaunch.setToggleState(DataStore::getInstance()->getRecordOnLaunch(id), false);
    recordOnLaunch.onClick = [&] {
      DataStore::getInstance()->setRecordOnLaunch(id, recordOnLaunch.getToggleState()); 
    };
    x += recordOnLaunch.getWidth();

    recordOnPlay.setBounds(x, y, 150, 30);
    recordOnPlay.setToggleState(DataStore::getInstance()->getRecordOnPlay(id), false);
    recordOnPlay.onClick = [&] {
      DataStore::getInstance()->setRecordOnPlay(id, recordOnPlay.getToggleState()); 
    };
    x += recordOnPlay.getWidth();
  }

  void update() {
    trackName.setText(             DataStore::getInstance()->getTrackName(id),      false );
    groupName.setText(             DataStore::getInstance()->getGroupName(id),      false );
    directory.setText(             DataStore::getInstance()->getDirectory(id),      false );
    recordOnLaunch.setToggleState( DataStore::getInstance()->getRecordOnLaunch(id), false );
    recordOnPlay.setToggleState(   DataStore::getInstance()->getRecordOnPlay(id),   false );
  }

  int size() { return 5; } // Number of variables

  juce::Component* getComponent(int index) {
    switch (index) {
      case 0:  return &trackName;
      case 1:  return &groupName;
      case 2:  return &directory;
      case 3:  return &recordOnLaunch;
      case 4:  return &recordOnPlay;
      default: return nullptr;
    };
  }

private:
};

class CustTable {
public:
  juce::Array<CustRow*> rows;

  CustTable() {
    for (int i = 0; i < DataStore::getInstance()->size(); i++) {
      CustRow* row = new CustRow(i);
      rows.add(row);
    }
  }

  void addAndMakeVisible(juce::Component& parent) {
    for (int i = 0; i < rows.size(); i++) {
      for (int j = 0; j < rows[i]->size(); j++) {
        if (rows[i]->getComponent(j) != nullptr)
          parent.addAndMakeVisible(rows[i]->getComponent(j));
      }
    }
  }

  void update() {
    for (int i = 0; i < rows.size(); i++) {
      rows[i]->update();
    }
  }
private:
};
