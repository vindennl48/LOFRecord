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

class GroupNameTextField : public juce::TextEditor
{
public:
  int id = 0;

  GroupNameTextField(int newID, const juce::String& name, const juce::String& text)
    : id(newID),
      juce::TextEditor(name)
  {
    setText(text, false);
    setListener();
  }

  GroupNameTextField(int newID, const juce::String& name)
    : id(newID),
      juce::TextEditor(name)
  {
    setListener();
  }

  void setListener() {
    onTextChange = [&] {
      DataStore::getInstance()->setGroupName(id, getText());
    };
  }

  void paint (juce::Graphics& g) override {
    getLookAndFeel().fillTextEditorBackground (g, getWidth(), getHeight(), *this);
    setText(DataStore::getInstance()->getGroupName(id));
  }
};

/**
 * Textbox that modifies the directory variable. Can not be modified directly
 * but when clicked on, it will open up the dialog box to be able to choose the
 * directory path.
 * */
class DirectoryButton : public juce::TextButton
{
public:
  int id = 0;

  DirectoryButton(int newID, const juce::String& name, const juce::String& text)
    : id(newID),
      juce::TextButton(name)
  {
    setButtonText("Directory");
    setListener();
  }

  DirectoryButton(int newID, const juce::String& name)
    : id(newID),
      juce::TextButton(name)
  {
    setButtonText("Directory");
    setListener();
  }

  void setListener() {
    onClick = [&] {
      juce::FileChooser chooser(
        "Select a directory to save to...",
        DataStore::getInstance()->getDirectory(id),
        "*"
      );
      chooser.browseForDirectory();
      if (chooser.getResult().exists()) {
        DataStore::getInstance()->setDirectory(id, chooser.getResult().getFullPathName());
      }
    };
  }
};
