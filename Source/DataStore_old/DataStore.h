
#pragma once

#include <JuceHeader.h>
#include "../Debug.h"

#define NUM_VERSIONS 4

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
  ~Version();

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
    if (tree.state.getProperty(name).toString().isEmpty())
      tree.state.setProperty(name, "default", nullptr);
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
  // Version* versions[NUM_VERSIONS] = { nullptr };
  static juce::Array<Version*> versions;

  int create(juce::AudioProcessor& p) {
    Version* v = new Version(p);
    versions.add(v);
    return v->id;
  }

  void remove(int id) {
    showMessageBox("Removing Version with id: " + juce::String(id));
    for (int i=0; i<versions.size(); i++) {
      if (versions[i] != nullptr && versions[i]->id == id) {
        delete versions[i];
        versions.remove(i);
        return;
      }
    }
  }

  int size() {
    return Version::gid;
  }

  Version& operator[](int id) {
    return get(id);
  }

  void destroyAll() {
    showMessageBox("Removing All!");
    for (int i=0; i<versions.size(); i++) {
      if (versions[i] != nullptr) {
        delete versions[i];
      }
      versions.remove(i);
    }

    // for (auto& i : versions) {
      // if (i != nullptr) {
        // delete i;
        // i = nullptr;
      // }
    // }
  }

private:
  Version& get(int id) {
    for (int i=0; i<versions.size(); i++) {
      if (versions[i] != nullptr && versions[i]->id == id) {
        return *versions[i];
      }
    }
    throw std::out_of_range("Version id out of range");

    // showMessageBox("Starting Function with id: " + juce::String(id) + ", Size: " + juce::String(size()));

    // if (id < 0 || id >= Version::gid) {
      // throw std::out_of_range("Version id out of range");
    // }

    // int i=0;
    // for (auto& v : versions) {
      // if (v != nullptr) showMessageBox(juce::String(i) + ": NON Null Found!, v->id: " + juce::String(v->id));
      // else showMessageBox(juce::String(i) + ": Null Found!");
      // i++;
    // }

    // for (auto& v : versions) {
      // if (v != nullptr) {
        // showMessageBox(
          // "NON Null Found!, v->id: " +
          // juce::String(v->id) + ", id: " +
          // juce::String(id)
        // );
        // if (v->id == id) {
          // showMessageBox("Returning!");
          // return *v;
        // }
      // }

      // // if (v != nullptr && v->id == id) {
        // // return *v;
      // // }
    // }
    
    // showMessageBox("id: " + juce::String(id) + ", Size: " + juce::String(size()));
    // throw std::out_of_range("Version id out of range");
  }
};


