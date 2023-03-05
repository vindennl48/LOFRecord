
#pragma once

#include <JuceHeader.h>
#include "Debug.h"
#include "DataStore/DataStore.h"

class CustRow {
public:
  int       id = 0;
  DataStore ds;

  juce::TextEditor* trackName;

  CustRow(int id)
    : id(id)
  {
    int x = 0; int y = 20+(40*id);

    trackName = new juce::TextEditor("trackName");
    showMessageBox(ds[id].trackName());
    if (ds[id].trackName().isEmpty()) ds[id].trackName("default");
    showMessageBox(ds[id].trackName());
    trackName->setText(ds[id].trackName(), false);
    trackName->setBounds(x, y, 150, 30);
    trackName->onTextChange = [&] { ds[id].trackName(trackName->getText()); };
    x += trackName->getWidth();

    showMessageBox("Created Track Name: " + ds[id].trackName());
  }

  void update() {
    trackName->setText(ds[id].trackName(), false);
  }

  int size() { return 1; }

  juce::Component* getComponent(int index) {
    switch (index) {
      case 0:  return trackName;
      default: return nullptr;
    };
  }

private:
};

class CustTable {
public:
  juce::Array<CustRow> rows;
  DataStore            ds;

  CustTable() {
    for (int i = 0; i < ds.size(); i++) {
      rows.add(CustRow(i));
    }
  }

  void addAndMakeVisible(juce::Component& parent) {
    showMessageBox(
      "Rows Size: " + juce::String(rows.size()) + "\n"// +
      // "Row 0 Size: " + juce::String(rows[0].size()) + "\n"
    );
    // for (int i = 0; i < rows.size(); i++) {
      // for (int j = 0; j < rows[i].size(); j++) {
        // parent.addAndMakeVisible(rows[i].getComponent(j));
      // }
    // }
  }
private:
};
