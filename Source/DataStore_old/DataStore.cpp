#include "DataStore.h"

//=TREE=========================================================================
juce::AudioProcessorValueTreeState::ParameterLayout
Tree::createParameterLayout() {
  juce::AudioProcessorValueTreeState::ParameterLayout layout;
  // Add int / float / bool save states

  layout.add(
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "gain", 1 }, "Gain", 0.0f, 1.0f, 0.5f)
  );

  layout.add(
    std::make_unique<juce::AudioParameterBool>(juce::ParameterID { "recordOnLaunch", 1 }, "Start Recording On Launch", false)
  );

  layout.add(
    std::make_unique<juce::AudioParameterBool>(juce::ParameterID { "recordOnPlay", 1 }, "Start Recording On Play", false)
  );

  return layout;
}
//=TREE=========================================================================


//=VERSION======================================================================
int Version::gid = 0;

Version::Version(juce::AudioProcessor& p) : tree(p) {
  showMessageBox("Created Version gid: " + juce::String(gid));
  id = gid++;
}

Version::~Version() {
  showMessageBox("Version Deleted gid: " + juce::String(gid));
  gid--;
}
//=VERSION======================================================================


//=DATASTORE====================================================================
juce::Array<Version*> DataStore::versions;
//=DATASTORE====================================================================
