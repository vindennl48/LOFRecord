
#pragma once

#include <JuceHeader.h>

struct Inst {
  int         id   = 0;
  juce::int64 time = 0; // used for filename creation

  juce::AudioProcessorValueTreeState& t;

  Inst(int id, juce::AudioProcessorValueTreeState& t);
};

class DataStore {
public:
  /**
   * Add and remove new plugin instances
   * */
  int addInst(juce::AudioProcessorValueTreeState& t) noexcept;
  void removeInst(int id) noexcept;

  /**
   * Get how many instances are in existence.
   * */
  int size() const noexcept;

  //============================================================================

  /**
   * Get and set string values in the value tree state.
   * */
  juce::String getString(int id, juce::String name) noexcept;
  void setString(int id, juce::String name, juce::String v,
    bool useFilter=false) noexcept;

  /**
   * Get and set bool values in the value tree state.
   * */
  bool getBool(int id, juce::String name) noexcept;
  void setBool(int id, juce::String name, bool v) noexcept;

  /**
   * Used specifically for custom components to add Listeners to the specific
   * value tree state.
   * */
  juce::AudioProcessorValueTreeState& getTreeState(int id) noexcept;

  /**
   * Used to get the id from the instance in the array at a specific position.
   * Need this for the custom table component.
   * */
  int getIDFromPos(int pos) const noexcept;

  /**
   * Used to get the time for the filename creation.
   * */
  juce::int64 getTime(int id) noexcept;
  void setTime(int id, juce::int64 t) noexcept;

  JUCE_DECLARE_SINGLETON(DataStore, true);
private:
  // data members
  int nextID = 0;
  juce::Array<Inst> insts;

  DataStore() = default;

  /**
   * Helper function to get the instance with given id
   * */
  Inst& getInstByID(int id) noexcept;
};

// Nice short-hand for this full monstrosity
#define DS DataStore::getInstance()

