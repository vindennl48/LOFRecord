
#pragma once

#include <JuceHeader.h>
#include "DataStore.h"
#include "Debug.h"

class ToggleButton
  : public juce::TextButton,
    public juce::Button::Listener,
    public juce::ValueTree::Listener
{
public:
  int id = 0;
  juce::ValueTree state;
  juce::String    parameterID = "default";
  juce::String    onText      = "ON";
  juce::String    offText     = "off";
  juce::Colour    onColour    = juce::Colours::green;

  /**
   * @brief Construct a new Text button object
   * @param newOnText the text to display when the button is on
   * @param newOffText the text to display when the button is off
   * @param juceName the name of the button
   * @param newID the id of the plugin instance
   * @param newParameterID the id of the parameter to update
   * @param newOnColour the colour to display when the button is on
   */
  ToggleButton(
      juce::String newOnText,
      juce::String newOffText,
      juce::String juceName,
      int          newID,
      juce::String newParameterID,
      juce::Colour newOnColour = juce::Colours::green
  )
    : juce::TextButton(juceName),
      id(newID),
      parameterID(newParameterID),
      onText(newOnText),
      offText(newOffText),
      onColour(newOnColour)
  {
    // when text button changes
    addListener(this);

    // for when value tree state changes
    // Need to keep our 'state' var in scope, once it goes out of scope
    // the listener will be destroyed
    state = DS->getTreeState(id).state;
    state.addListener(this);

    // set initial value
    setToggleState(DS->getBool(id, parameterID), juce::dontSendNotification);
  }

  // when text button changes, update the value tree state
  void buttonClicked (Button* b) override {
    DS->setBool(id, parameterID, !b->getToggleState(), true);
  }

  // when value tree state changes, update the text button
  void valueTreePropertyChanged (
    juce::ValueTree& treeWhosePropertyHasChanged,
    const juce::Identifier& property
  ) override {
    if (property.toString() == parameterID) {
      setToggleState(
        (bool)treeWhosePropertyHasChanged.getProperty(property),
        juce::dontSendNotification
      );
    }
  }

  void paintButton (juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override {
    auto& lf = getLookAndFeel();

    if (getToggleState()) {
      lf.drawButtonBackground (
        g,
        *this,
        onColour, // from constructor
        shouldDrawButtonAsHighlighted,
        shouldDrawButtonAsDown
      );
      setButtonText(onText);
    } else {
      lf.drawButtonBackground (
        g,
        *this,
        findColour (getToggleState() ? buttonOnColourId : buttonColourId),
        shouldDrawButtonAsHighlighted,
        shouldDrawButtonAsDown
      );
      setButtonText(offText);
    }
    lf.drawButtonText (g, *this, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
  }
};

class RecordButton
  : public juce::TextButton,
    public juce::Button::Listener,
    public juce::ValueTree::Listener
{
public:
  int id = 0;
  juce::ValueTree state;
  juce::String    parameterID = "default";
  juce::String    onText      = "RECORDING";
  juce::String    offText     = "record";
  juce::Colour    onColour    = juce::Colours::red;

  /**
   * @brief Construct a new Text button object
   * @param newOnText the text to display when the button is on
   * @param newOffText the text to display when the button is off
   * @param juceName the name of the button
   * @param newID the id of the plugin instance
   * @param newParameterID the id of the parameter to update
   * @param newOnColour the colour to display when the button is on
   */
  RecordButton(
      juce::String juceName,
      int          newID,
      juce::String newParameterID
  )
    : juce::TextButton(juceName),
      id(newID),
      parameterID(newParameterID)
  {
    // when text button changes
    addListener(this);

    // for when value tree state changes
    // Need to keep our 'state' var in scope, once it goes out of scope
    // the listener will be destroyed
    state = DS->getTreeState(id).state;
    state.addListener(this);

    // set initial value
    setToggleState(DS->getBool(id, parameterID), juce::dontSendNotification);
  }

  // when text button changes, update the value tree state
  void buttonClicked (Button* b) override {
    DS->setAllRecord(id, !b->getToggleState());
    // DS->setBool(id, parameterID, !b->getToggleState());
  }

  // when value tree state changes, update the text button
  void valueTreePropertyChanged (
    juce::ValueTree& treeWhosePropertyHasChanged,
    const juce::Identifier& property
  ) override {
    if (property.toString() == parameterID) {
      setToggleState(
        (bool)treeWhosePropertyHasChanged.getProperty(property),
        juce::dontSendNotification
      );
    }
  }

  void paintButton (juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override {
    auto& lf = getLookAndFeel();

    if (getToggleState()) {
      lf.drawButtonBackground (
        g,
        *this,
        onColour, // from constructor
        shouldDrawButtonAsHighlighted,
        shouldDrawButtonAsDown
      );
      setButtonText(onText);
    } else {
      lf.drawButtonBackground (
        g,
        *this,
        findColour (getToggleState() ? buttonOnColourId : buttonColourId),
        shouldDrawButtonAsHighlighted,
        shouldDrawButtonAsDown
      );
      setButtonText(offText);
    }
    lf.drawButtonText (g, *this, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
  }
};
