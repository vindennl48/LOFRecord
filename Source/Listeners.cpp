
#include "Listeners.h"
#include "DataStore.h"
#include "Debug.h"

Listeners::Listeners(int newID, juce::AudioProcessorValueTreeState& vts)
    : valueTreeState(vts),
      id(newID)
{
  valueTreeState.addParameterListener("recordReady",    this);
  valueTreeState.addParameterListener("recordOnLaunch", this);
  valueTreeState.addParameterListener("recordOnPlay",   this);
}

Listeners::~Listeners() {
  valueTreeState.removeParameterListener("recordReady",    this);
  valueTreeState.removeParameterListener("recordOnLaunch", this);
  valueTreeState.removeParameterListener("recordOnPlay",   this);
}

void Listeners::parameterChanged(const juce::String& parameterID, float newValue) {
  // showMessageBox("parameterChanged: " + parameterID + ", " + juce::String(newValue));

  if (parameterID == "recordReady") {
    DS->setAllRecord(id, (bool)newValue);
  }

  if (parameterID == "recordOnLaunch") {
    DS->setBool(id, "recordOnLaunch", (bool)newValue);
  }

  if (parameterID == "recordOnPlay") {
    DS->setBool(id, "recordOnPlay", (bool)newValue);
  }
}
