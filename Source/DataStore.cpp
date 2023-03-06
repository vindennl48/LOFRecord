
#include "DataStore.h"
#include "Debug.h"

Inst::Inst(int id, juce::AudioProcessorValueTreeState& t) : id(id), t(t) {}

JUCE_IMPLEMENT_SINGLETON(DataStore);

int DataStore::addInst(juce::AudioProcessorValueTreeState& t) noexcept {
  // printToConsole(S("----> ") + S("ADDING DATASTORE OBJ! ") + S(nextID));
  insts.add(Inst(nextID, t));
  int result = nextID;
  nextID += 1;
  printToConsole(S("----> Adding ID ") + S(result) + S(" To Datastore!"));
  return result;
}

void DataStore::removeInst(int id) noexcept {
  // remove inst that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id) {
      insts.remove(i);
        printToConsole(S("----> Removing ID ") + S(id) + S(" From Datastore!"));
      break;
    }
  }
}

int DataStore::size() const noexcept {
  return insts.size();
}

juce::String DataStore::getTrackName(int id) const noexcept {
  // return track name that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id) {
      return insts.getReference(i).trackName;
    }
  }
  printToConsole(S("####> ERROR> ") + S("DataStore::getTrackName() - id not found: ") + S(id));
  jassertfalse;
  // throw std::runtime_error("DataStore::getTrackName() - id not found");
  // return "####";
}

void DataStore::setTrackName(int id, const juce::String& name) noexcept {
  // showMessageBox("Setting Track id: " + juce::String(id) + " and name: " + name);
  // set track name that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id) {
      insts.getReference(i).trackName =
        name.toLowerCase().replaceCharacters(" !@#$%^&*(){}[]|\\:;\"'<>,.?/~`", "_____________________________");
      break;
    }
  }
}

juce::String DataStore::getGroupName(int id) const noexcept {
  // return group name that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id) {
      return insts.getReference(i).groupName;
    }
  }
  printToConsole(S("####> ERROR> ") + S("DataStore::getGroupName() - id not found: ") + S(id));
  jassertfalse;
  // throw std::runtime_error("DataStore::getGroupName() - id not found");
  // return "####";
}

void DataStore::setGroupName(int id, const juce::String& name) noexcept {
  // set group name that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id) {
      insts.getReference(i).groupName =
        name.toLowerCase().replaceCharacters(" !@#$%^&*(){}[]|\\:;\"'<>,.?/~`", "_____________________________");
      break;
    }
  }
}

juce::String DataStore::getDirectory(int id) const noexcept {
  // return directory that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id) {
      return insts.getReference(i).directory;
    }
  }
  printToConsole(S("####> ERROR> ") + S("DataStore::getDirectory() - id not found: ") + S(id));
  jassertfalse;
  // throw std::runtime_error("DataStore::getDirectory() - id not found");
  // return "####";
}

void DataStore::setDirectory(int id, const juce::String& name) noexcept {
  // set directory that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id) {
      insts.getReference(i).directory = name;
      break;
    }
  }
}

bool DataStore::getRecordOnLaunch(int id) const noexcept {
  // return recordOnLaunch that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id) {
      return insts.getReference(i).recordOnLaunch;
    }
  }
  return false;
}

void DataStore::setRecordOnLaunch(int id, bool b) noexcept {
  // set recordOnLaunch that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id && insts.getReference(i).recordOnLaunch != b) {
      insts.getReference(i).recordOnLaunch = b;
      insts.getReference(i).t.getParameter("recordOnLaunch")->setValueNotifyingHost(b);
      break;
    }
  }
}

bool DataStore::getRecordOnPlay(int id) const noexcept {
  // return recordOnPlay that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id) {
      return insts.getReference(i).recordOnPlay;
    }
  }
  return false;
}

void DataStore::setRecordOnPlay(int id, bool b) noexcept {
  // set recordOnPlay that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id && insts.getReference(i).recordOnPlay != b) {
      insts.getReference(i).recordOnPlay = b;
      insts.getReference(i).t.getParameter("recordOnPlay")->setValueNotifyingHost(b);
      break;
    }
  }
}

bool DataStore::getIsRecording(int id) const noexcept {
  // return isRecording that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id) {
      return insts.getReference(i).isRecording;
    }
  }
  return false;
}

void DataStore::setIsRecording(int id, bool b) noexcept {
  // set isRecording that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id && insts.getReference(i).isRecording != b) {
      insts.getReference(i).isRecording = b;
      insts.getReference(i).t.getParameter("isRecording")->setValueNotifyingHost(b);
      break;
    }
  }
}

void DataStore::setAllRecording(int id, bool b) noexcept {
  juce::String groupName;
  juce::int64 time = getTime(id);

  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id) {
      groupName = insts.getReference(i).groupName;
      break;
    }
  }

  if (groupName.isEmpty())
    return; // if we cant find the instance

  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).groupName == groupName) {
      setTime(i, time); // set all time for the group
      setIsRecording(i, b);
    }
  }
}

int DataStore::getIDFromPos(int pos) const noexcept {
  if (pos < 0 || pos >= insts.size())
    return -1;
  return insts.getReference(pos).id;
}

juce::int64 DataStore::getTime(int id) noexcept {
  // return time that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id) {
      if (insts.getReference(i).time == 0 ) {
        return juce::Time::getCurrentTime().toMilliseconds() % 86400000;
      } else {
        juce::int64 result = insts.getReference(i).time;
        insts.getReference(i).time = 0;
        return result;
      }
    }
  }
  return 0;
}

void DataStore::setTime(int id, juce::int64 t) noexcept {
  // set time that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id && insts.getReference(i).time != t) {
      insts.getReference(i).time = t;
      break;
    }
  }
}

void DataStore::saveState(int id, juce::AudioProcessorValueTreeState& t) noexcept {
  t.state.setProperty( "trackName",      getTrackName(id),      nullptr );
  t.state.setProperty( "groupName",      getGroupName(id),      nullptr );
  t.state.setProperty( "directory",      getDirectory(id),      nullptr );
  t.state.setProperty( "recordOnLaunch", getRecordOnLaunch(id), nullptr );
  t.state.setProperty( "recordOnPlay",   getRecordOnPlay(id),   nullptr );
}

void DataStore::loadState(int id, juce::AudioProcessorValueTreeState& t) noexcept {
  setTrackName(      id, t.state.getProperty("trackName").toString() );
  setGroupName(      id, t.state.getProperty("groupName").toString() );
  setDirectory(      id, t.state.getProperty("directory").toString() );
  setRecordOnLaunch( id, t.state.getProperty("recordOnLaunch")       );
  setRecordOnPlay(   id, t.state.getProperty("recordOnPlay")         );
}
