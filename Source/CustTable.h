
#pragma once

#include <JuceHeader.h>
#include "Debug.h"
#include "DataStore/DataStore.h"

class CustRow {
public:
  int id = 0;

  juce::TextEditor trackName;

  CustRow(int id)
    : id(id),
      trackName("trackName")
  {
    int x = 0; int y = 20+(40*id);

    trackName.setBounds(x, y, 150, 30);
    trackName.setText(DataStore::getInstance()->getTrackName(id), false);
    trackName.onTextChange = [&] {
      DataStore::getInstance()->setTrackName(id, trackName.getText()); 
    };
    x += trackName.getWidth();
  }

//  void update() {
//    trackName->setText(DataStore::getInstance()->getTrackName(id), false);
//  }

  int size() { return 1; } // Number of variables

  juce::Component* getComponent(int index) {
    switch (index) {
      case 0:  return &trackName;
      default: return nullptr;
    };
  }

private:
};

class CustTable {
public:
  juce::Array<CustRow*> rows;

  CustTable() {
    int dsSize = DataStore::getInstance()->size();
    for (int i = 0; i < dsSize; i++) {
      rows.add(new CustRow(i));
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
private:
};
