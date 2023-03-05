
#include "DataStore.h"
#include "Debug.h"

Inst::Inst(int id) : id(id) {}

JUCE_IMPLEMENT_SINGLETON(DataStore);

int DataStore::addInst() noexcept {
  printToConsole(S("----> ") + S("ADDING DATASTORE OBJ! ") + S(nextID));
  insts.add(Inst(nextID));
  return nextID++;
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

juce::String DataStore::getTrackName(int id) const noexcept {
  // return track name that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id) {
      return insts.getReference(i).trackName;
    }
  }
  printToConsole(S("----> ") + S("DataStore::getTrackName() - id not found: ") + S(id));
  throw std::runtime_error("DataStore::getTrackName() - id not found");
  // return "####";
}

void DataStore::setTrackName(int id, const juce::String& name) noexcept {
  // showMessageBox("Setting Track id: " + juce::String(id) + " and name: " + name);
  // set track name that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id) {
      insts.getReference(i).trackName = name;
      // showMessageBox("SET!");
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
  printToConsole(S("----> ") + S("DataStore::getGroupName() - id not found: ") + S(id));
  throw std::runtime_error("DataStore::getGroupName() - id not found");
  // return "####";
}

void DataStore::setGroupName(int id, const juce::String& name) noexcept {
  // set group name that matches id
  for (int i = 0; i < insts.size(); ++i) {
    if (insts.getReference(i).id == id) {
      insts.getReference(i).groupName = name;
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
  printToConsole(S("----> ") + S("DataStore::getDirectory() - id not found: ") + S(id));
  throw std::runtime_error("DataStore::getDirectory() - id not found");
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
    if (insts.getReference(i).id == id) {
      insts.getReference(i).recordOnLaunch = b;
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
    if (insts.getReference(i).id == id) {
      insts.getReference(i).recordOnPlay = b;
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
