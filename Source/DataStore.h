#pragma once

#include <JuceHeader.h>

class Tree : public juce::AudioProcessorValueTreeState {
public:
  Tree(juce::AudioProcessor& p)
    : juce::AudioProcessorValueTreeState(p, nullptr, "params", createParameterLayout())
  {
    // Add String variable save states
    state.addChild(juce::ValueTree("directory"), -1, nullptr);
    state.addChild(juce::ValueTree("trackName"), -1, nullptr);
    state.addChild(juce::ValueTree("groupName"), -1, nullptr);
  }

  // DataStore.cpp
  static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
};

struct Version {
  static int gid;

  Tree tree;
  int  id = 0;

  Version(juce::AudioProcessor& p);

  //--Custom Save Vars---------------------- 
  //  These vars are persistent between plugin loads
  //---------------------------------------- 
  const juce::String& directory() { return _getString("directory"); }
  void directory(const juce::String& s) { _setString(s, "directory"); }

  const juce::String& trackName() { return _getString("trackName"); }
  void trackName(const juce::String& s) { _setString(s, "trackName"); }

  const juce::String& groupName() { return _getString("groupName"); }
  void groupName(const juce::String& s) { _setString(s, "groupName"); }

  const bool recordOnLaunch() { return _get<bool>("recordOnLaunch"); }
  void recordOnLaunch(bool s) { _set<bool>(s, "recordOnLaunch"); }

  const bool recordOnPlay() { return _get<bool>("recordOnPlay"); }
  void recordOnPlay(bool s) { _set<bool>(s, "recordOnPlay"); }

  // not used
  const bool gain() { return _get<float>("gain"); }
  void gain(bool s) { _set<float>(s, "gain"); }
  //--Custom Save Vars---------------------- 

  //--Custom DOES NOT save Vars---------------------- 
  //  These vars are not persistent between plugin loads
  //  and reset after the DAW closes
  //------------------------------------------------- 
  const bool isRecording() { return is_recording; }
  void isRecording(bool s) { is_recording = s; }
  //--Custom DOES NOT save Vars---------------------- 

  // Put inside AudioProcessor::setStateInformation
  void load(const void* data, int sizeInBytes) {
    auto newTree = juce::ValueTree::readFromData(data, size_t(sizeInBytes));
    if (newTree.isValid()) tree.replaceState(newTree);
  }

  // Put inside AudioProcessor::getStateInformation
  void save(juce::MemoryBlock& destData) {
    juce::MemoryOutputStream stream(destData, true);
    tree.state.writeToStream(stream);
  }

private:
  //--Custom DOES NOT save Vars---------------------- 
  bool is_recording = false;
  //--Custom DOES NOT save Vars---------------------- 

  const juce::String& _getString(const juce::Identifier& name) {
    return tree.state.getProperty(name).toString();
  }
  void _setString(const juce::String& s, const juce::Identifier& name) {
    tree.state.setProperty(name, s, nullptr);
  }
  template <typename T>
  T _get(const juce::Identifier& name) {
    return tree.state.getProperty(name);
  }
  template <typename T>
  void _set(const T& s, const juce::Identifier& name) {
    tree.state.getChildWithName(name).setProperty("value", s, nullptr);
  }
};

class DataStore {
public:
  Version* versions[24] = { nullptr };

  ~DataStore() {
    for (auto& i : versions) {
      if (i != nullptr) {
        delete i;
        i = nullptr;
      }
    }
  }

  int create(juce::AudioProcessor& p) {
    versions[Version::gid] = new Version(p);
    return Version::gid-1;
  }

  Version& operator[](int id) {
    // return *versions[id];
    return get(id);
  }

private:
  Version& get(int id) {
    return *versions[id];
  }
};


