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

class DirectoryButton : public juce::TextButton
{
public:
  int id = 0;

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

class RecordButton : public juce::TextButton
{
public:
  int id = 0;

  RecordButton(int newID, const juce::String& name)
    : id(newID),
      juce::TextButton(name)
  {
    setButtonText("Record");
    setListener();
  }

  void setListener() {
    // Need to add in some things to sync instances and shizz
    onClick = [&] {
      DataStore::getInstance()->setIsRecording(id, !DataStore::getInstance()->getIsRecording(id));
    };
  }

  void paintButton (juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override {
    auto& lf = getLookAndFeel();

    if (DataStore::getInstance()->getIsRecording(id)) {
      lf.drawButtonBackground (
        g,
        *this,
        // findColour (getToggleState() ? buttonOnColourId : buttonColourId),
        juce::Colours::red,
        shouldDrawButtonAsHighlighted,
        shouldDrawButtonAsDown
      );
      lf.drawButtonText (g, *this, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
      setButtonText("IS RECORDING");
    } else {
      lf.drawButtonBackground (
        g,
        *this,
        findColour (getToggleState() ? buttonOnColourId : buttonColourId),
        shouldDrawButtonAsHighlighted,
        shouldDrawButtonAsDown
      );
      lf.drawButtonText (g, *this, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
      setButtonText("Record");
    }
  }
};

class RecordOnLaunchButton : public juce::TextButton
{
public:
  int id = 0;

  RecordOnLaunchButton(int newID, const juce::String& name)
    : id(newID),
      juce::TextButton(name)
  {
    setButtonText(DataStore::getInstance()->getRecordOnLaunch(id) ? "ON" : "off");
    setListener();
  }

  void setListener() {
    onClick = [&] {
      DataStore::getInstance()->setRecordOnLaunch(id, !DataStore::getInstance()->getRecordOnLaunch(id));
    };
  }

  void paintButton (juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override {
    auto& lf = getLookAndFeel();

    if (DataStore::getInstance()->getRecordOnLaunch(id)) {
      lf.drawButtonBackground (
        g,
        *this,
        // findColour (getToggleState() ? buttonOnColourId : buttonColourId),
        juce::Colours::green,
        shouldDrawButtonAsHighlighted,
        shouldDrawButtonAsDown
      );
      lf.drawButtonText (g, *this, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
      setButtonText("ON");
    } else {
      lf.drawButtonBackground (
        g,
        *this,
        findColour (getToggleState() ? buttonOnColourId : buttonColourId),
        // juce::Colours::grey,
        shouldDrawButtonAsHighlighted,
        shouldDrawButtonAsDown
      );
      lf.drawButtonText (g, *this, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
      setButtonText("off");
    }
  }
};
