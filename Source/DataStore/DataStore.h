
#pragma once

#include <JuceHeader.h>

struct Inst {
  int id = 0;

  juce::String trackName = "default";

  Inst(int id);
};

class DStore {
public:
  // getters and setters
  int addInst() noexcept;
  void removeInst(int id) noexcept;

  juce::String getTrackName(int id) const noexcept;
  void setTrackName(int id, const juce::String& name) noexcept;

  JUCE_DECLARE_SINGLETON(DStore, true);
private:
  DStore() = default;

  // data members
  int nextID = 0;
  juce::Array<Inst> insts;
};
