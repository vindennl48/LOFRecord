
#pragma once

#include <JuceHeader.h>
#include "DataStore.h"
#include "Debug.h"

class TextBox
  : public juce::TextEditor,
    public juce::TextEditor::Listener,
    public juce::ValueTree::Listener
{
public:
  juce::ValueTree state;
  int             id          = 0;
  juce::String    parameterID = "default";
  bool            useFilter   = false;

  /**
   * @brief Construct a new Text Box object
   * @param newID the id of the plugin instance
   * @param newParameterID the id of the parameter to update
   */
  TextBox(juce::String name, int newID, juce::String newParameterID, bool useFilter=false)
    : juce::TextEditor(name),
      id(newID),
      parameterID(newParameterID),
      useFilter(useFilter)
  {
    // when text box changes
    addListener(this);

    // for when value tree state changes
    // Need to keep our 'state' var in scope, once it goes out of scope
    // the listener will be destroyed
    state = DS->getTreeState(id).state;
    state.addListener(this);

    // set initial text
    setText(DS->getString(id, parameterID), false);
  }

  // when text box changes, update the value tree state
  void textEditorTextChanged (TextEditor& te) override {
    DS->setString(id, parameterID, te.getText(), useFilter);
  }

  // when value tree state changes, update the text box
  void valueTreePropertyChanged (
    juce::ValueTree& treeWhosePropertyHasChanged,
    const juce::Identifier& property
  ) override {
    if (property.toString() == parameterID) {
      setText(treeWhosePropertyHasChanged.getProperty(property).toString());
    }
  }
};
