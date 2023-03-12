
#include "DataStore.h"
#include "Debug.h"

Inst::Inst(int id, juce::AudioProcessorValueTreeState& t) : id(id), t(t) {}

JUCE_IMPLEMENT_SINGLETON(DataStore);

int DataStore::addInst(juce::AudioProcessorValueTreeState& t) noexcept {
  insts.add(Inst(nextID, t));
  int result = nextID;
  nextID += 1;
  return result;
}

void DataStore::removeInst(int id) noexcept {
  // remove inst that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id) {
      insts.remove(i);
      break;
    }
  }
}

int DataStore::size() const noexcept {
  return insts.size();
}

//==============================================================================

juce::String DataStore::getString(int id, juce::String name) noexcept {
  return getInstByID(id).t.state.getProperty(name).toString();
}

void DataStore::setString(
  int          id,
  juce::String name,
  juce::String v,
  bool         useFilter
) noexcept
{
  if (useFilter) {
    v = v.toLowerCase().replaceCharacters(
      " !@#$%^&*(){}[]|\\:;\"'<>,.?/~`", "_____________________________"
    );
  }
  getInstByID(id).t.state.setProperty(name, v, nullptr);
}

bool DataStore::getBool(int id, juce::String name) noexcept {
  return getInstByID(id).t.state.getProperty(name);
}

void DataStore::setBool(int id, juce::String name, bool v, bool sendAlert) noexcept {
  if (sendAlert) {
    getInstByID(id).t.getParameter(name)->setValueNotifyingHost(v);
  }
  getInstByID(id).t.state.setProperty(name, v, nullptr);
}

void DataStore::setAllRecord(int id, bool b) noexcept {
  juce::String groupName = getString(id, "groupName");
  juce::int64  time      = getTime(id);

  if (groupName.isEmpty())
    return; // if we cant find the instance

  for (int i = 0; i < insts.size(); ++i) {
    int thisID = getIDFromPos(i);
    if (getString(thisID, "groupName") == groupName) {
      if (isRecording(thisID) != b) {
        isRecording(thisID, b);
        setTime(thisID, time); // set all time for the group
        setBool(thisID, "recordReady", b, true);
      }
    }
  }
}

void DataStore::isRecording(int id, bool b) noexcept {
  getInstByID(id).isRecording = b;
}

bool DataStore::isRecording(int id) noexcept {
  return getInstByID(id).isRecording;
}

juce::AudioProcessorValueTreeState& DataStore::getTreeState(int id) noexcept {
  return getInstByID(id).t;
}

int DataStore::getIDFromPos(int pos) const noexcept {
  if (pos < 0 || pos >= insts.size()) {
    printToConsole(S("----> DataStore::getIDFromPos: invalid pos: ") + S(pos));
    return -1;
  }
  return insts.getReference(pos).id;
}

juce::int64 DataStore::getTime(int id) noexcept {
  auto& i = getInstByID(id);

  if (i.time == 0) {
    return juce::Time::getCurrentTime().toMilliseconds() % 86400000;
  } else {
    auto time = i.time;
    i.time = 0;
    return time;
  }

  return 0;
}

void DataStore::setTime(int id, juce::int64 t) noexcept {
  // set time that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id) {
      insts.getReference(i).time = t;
      break;
    }
  }
}

Inst& DataStore::getInstByID(int id) noexcept {
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id) {
      return insts.getReference(i);
    }
  }
  printToConsole(S("####> ERROR> ") + S("DataStore::getInst() - id not found: ") + S(id));
  jassertfalse;
}
