
#pragma once

#include <JuceHeader.h>

struct Inst {
  int id = 0;

  juce::String trackName = "default";
  juce::String groupName = "default";
  juce::String directory = juce::File::getSpecialLocation(juce::File::userDesktopDirectory).getFullPathName();
  bool isRecording       = false;
  bool recordOnLaunch    = false;
  bool recordOnPlay      = false;

  juce::AudioProcessorValueTreeState& t;

  Inst(int id, juce::AudioProcessorValueTreeState& t);
};

class DataStore {
public:
  // getters and setters
  int addInst(juce::AudioProcessorValueTreeState& t) noexcept;
  void removeInst(int id) noexcept;
  int size() const noexcept;

  juce::String getTrackName(int id) const noexcept;
  void setTrackName(int id, const juce::String& name) noexcept;

  juce::String getGroupName(int id) const noexcept;
  void setGroupName(int id, const juce::String& name) noexcept;

  juce::String getDirectory(int id) const noexcept;
  void setDirectory(int id, const juce::String& name) noexcept;

  bool getRecordOnLaunch(int id) const noexcept;
  void setRecordOnLaunch(int id, bool b) noexcept;

  bool getRecordOnPlay(int id) const noexcept;
  void setRecordOnPlay(int id, bool b) noexcept;

  bool getIsRecording(int id) const noexcept;
  void setIsRecording(int id, bool b) noexcept;

  /**
   * Set all of the instance variables to the tree state.
   * Make sure to update this function when adding variables.
   * */
  void saveState(int id, juce::AudioProcessorValueTreeState& t) noexcept;
  void loadState(int id, juce::AudioProcessorValueTreeState& t) noexcept;

  JUCE_DECLARE_SINGLETON(DataStore, true);
private:
  // data members
  int nextID = 0;
  juce::Array<Inst> insts;

  DataStore() = default;
};
