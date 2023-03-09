
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
  juce::String parameterID = "default";
  juce::ValueTree state;

  /**
   * @brief Construct a new Text button object
   * @param newID the id of the plugin instance
   * @param newParameterID the id of the parameter to update
   */
  ToggleButton(juce::String name, int newID, juce::String newParameterID)
    : juce::TextButton(name),
      id(newID),
      parameterID(newParameterID)
  {
    // when text button changes
    addListener(this);

    // set text on button
    setButtonText(name);

    // for when value tree state changes
    // Need to keep our 'state' var in scope, once it goes out of scope
    // the listener will be destroyed
    state = DataStore::getInstance()->getTreeState(id).state;
    state.addListener(this);

    // set initial value
    setToggleState(
      DataStore::getInstance()->getTreeState(id)
        .state.getProperty(parameterID),
      juce::dontSendNotification
    );
  }

  // when text button changes, update the value tree state
  void buttonClicked (Button* b) override {
    // printToConsole(S("----> ToggleButton::buttonClicked"));
    DataStore::getInstance()->getTreeState(id)
      .state.setProperty(parameterID, !b->getToggleState(), nullptr);
  }

  // when value tree state changes, update the text button
  void valueTreePropertyChanged (
    juce::ValueTree& treeWhosePropertyHasChanged,
    const juce::Identifier& property
  ) override {
    if (property.toString() == parameterID) {
      // printToConsole(S("----> ToggleButton::valueTreePropertyChanged"));
      setToggleState(
        treeWhosePropertyHasChanged.getProperty(property),
        juce::dontSendNotification
      );
    }
  }

  void paintButton (juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override {
    auto& lf = getLookAndFeel();

    if (getToggleState()) {
      // printToConsole(S("----> ToggleButton::paintButton getToggleState returned True"));
      lf.drawButtonBackground (
        g,
        *this,
        // findColour (getToggleState() ? buttonOnColourId : buttonColourId),
        juce::Colours::green,
        shouldDrawButtonAsHighlighted,
        shouldDrawButtonAsDown
      );
      lf.drawButtonText (g, *this, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
      // setButtonText("IS RECORDING");
    } else {
      // printToConsole(S("----> ToggleButton::paintButton getToggleState returned False"));
      lf.drawButtonBackground (
        g,
        *this,
        findColour (getToggleState() ? buttonOnColourId : buttonColourId),
        shouldDrawButtonAsHighlighted,
        shouldDrawButtonAsDown
      );
    }
    lf.drawButtonText (g, *this, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
  }
};
