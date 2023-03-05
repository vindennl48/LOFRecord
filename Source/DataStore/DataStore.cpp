
#include "Singleton.h"

Inst::Inst(int id) : id(id) {}

JUCE_IMPLEMENT_SINGLETON(DStore);

int DStore::addInst() noexcept {
  insts.add(Inst(nextID));
  return nextID++;
}

void DStore::removeInst(int id) noexcept {
  // remove inst that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id) {
      insts.remove(i);
      break;
    }
  }
}

juce::String DStore::getTrackName(int id) const noexcept {
  // return track name that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id) {
      return insts.getReference(i).trackName;
    }
  }
  return "####";
}

void DStore::setTrackName(int id, const juce::String& name) noexcept {
  // set track name that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id) {
      insts.getReference(i).trackName = name;
      break;
    }
  }
}
