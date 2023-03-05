#pragma once

#include <JuceHeader.h>
#include "DataStore.h"

class TrackNameTextField : public juce::TextEditor
{
public:
  int id = 0;

  TrackNameTextField(int newID, const juce::String& name, const juce::String& text)
    : id(newID),
      juce::TextEditor(name)
  {
    setText(text, false);
    setListener();
  }

  TrackNameTextField(int newID, const juce::String& name)
    : id(newID),
      juce::TextEditor(name)
  {
    setListener();
  }

  void setListener() {
    onTextChange = [&] {
      DataStore::getInstance()->setTrackName(id, getText());
    };
  }

  void paint (juce::Graphics& g) override {
    getLookAndFeel().fillTextEditorBackground (g, getWidth(), getHeight(), *this);
    setText(DataStore::getInstance()->getTrackName(id));
  }
};
