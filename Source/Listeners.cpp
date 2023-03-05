
#include "Listeners.h"
#include "DataStore.h"
#include "Debug.h"

Listeners::Listeners(int id, juce::AudioProcessorValueTreeState& vts)
    : valueTreeState(vts),
      id(0)
{
  valueTreeState.addParameterListener("isRecording", this);
  valueTreeState.addParameterListener("recordOnLaunch", this);
  valueTreeState.addParameterListener("recordOnPlay", this);
}

Listeners::~Listeners() {
  valueTreeState.removeParameterListener("isRecording", this);
  valueTreeState.removeParameterListener("recordOnLaunch", this);
  valueTreeState.removeParameterListener("recordOnPlay", this);
}

void Listeners::parameterChanged(const juce::String& parameterID, float newValue) {
  // showMessageBox("parameterChanged: " + parameterID + ", " + juce::String(newValue));

  if (parameterID == "isRecording") {
    DataStore::getInstance()->setIsRecording(id, (bool)newValue);
  }

  if (parameterID == "recordOnLaunch") {
    DataStore::getInstance()->setRecordOnLaunch(id, (bool)newValue);
  }

  if (parameterID == "recordOnPlay") {
    DataStore::getInstance()->setRecordOnPlay(id, (bool)newValue);
  }
}
