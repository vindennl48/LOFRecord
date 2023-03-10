
#pragma once

#include <JuceHeader.h>
#include "DataStore.h"
#include "Debug.h"

class SetPathButton
  : public juce::TextButton,
    public juce::Button::Listener
{
public:
  int id = 0;
  juce::ValueTree state;
  juce::String    parameterID = "default";

  /**
   * @brief Construct a new Text button object
   * @param newOnText the text to display when the button is on
   * @param newOffText the text to display when the button is off
   * @param juceName the name of the button
   * @param newID the id of the plugin instance
   * @param newParameterID the id of the parameter to update
   * @param newOnColour the colour to display when the button is on
   */
  SetPathButton(
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

    setButtonText("Directory");
  }

  // when clicked
  void buttonClicked (Button* b) override {
    juce::FileChooser chooser(
      "Select a directory to save to...",
      DS->getString(id, parameterID),
      "*"
    );
    chooser.browseForDirectory();
    if (chooser.getResult().exists()) {
      DS->setString(id, parameterID, chooser.getResult().getFullPathName());
    }
  }
};
