/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "DataStore.h"
#include "Debug.h"

//==============================================================================
LOFRecordAudioProcessor::LOFRecordAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor (
        BusesProperties()
        #if ! JucePlugin_IsMidiEffect
            #if ! JucePlugin_IsSynth
                .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
            #endif
            .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
        #endif
    ),
    m_params (
        *this, nullptr,
        "Parameters",
        createParameterLayout()
    )
#endif
{
  id = DS->addInst(m_params); // MUST BE FIRST

  m_params.state = juce::ValueTree("MyAudioProcessor");
  // Add the directory valuetree child node to the state tree
  m_params.state.addChild(juce::ValueTree("trackName"), -1, nullptr);
  m_params.state.addChild(juce::ValueTree("groupName"), -1, nullptr);
  m_params.state.addChild(juce::ValueTree("directory"), -1, nullptr);

  // lets add some defaults
  m_params.state.setProperty("trackName",      "default", nullptr);
  m_params.state.setProperty("groupName",      "default", nullptr);
  m_params.state.setProperty("directory",      "default", nullptr);
  m_params.state.setProperty("isRecording",    false,     nullptr);
  m_params.state.setProperty("recordOnLaunch", false,     nullptr);
  m_params.state.setProperty("recordOnPlay",   false,     nullptr);

  wavSave = new WavSave(id);
}

LOFRecordAudioProcessor::~LOFRecordAudioProcessor() {
  // delete listeners;
  DS->removeInst(id);
}

// ----------------- mitch stuff -----------------
// Create the parameter layout
juce::AudioProcessorValueTreeState::ParameterLayout LOFRecordAudioProcessor::createParameterLayout()
{
  juce::AudioProcessorValueTreeState::ParameterLayout layout;
  layout.add( std::make_unique<juce::AudioParameterBool>( juce::ParameterID { "isRecording",    1 }, "Record",                    false ) );
  layout.add( std::make_unique<juce::AudioParameterBool>( juce::ParameterID { "recordOnLaunch", 1 }, "Start Recording On Launch", false ) );
  layout.add( std::make_unique<juce::AudioParameterBool>( juce::ParameterID { "recordOnPlay",   1 }, "Start Recording On Play",   false ) );
  return layout;
}

// PRIVATE
//==============================================================================
void LOFRecordAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

//    if (DS->getIsRecording(id)) {
//      if (!isRecording) {
//        wavSave->startRecording(
//          buffer.getNumChannels(),
//          getSampleRate(),
//          buffer.getNumSamples()
//        );
//        isRecording = true;
//      } else {
//        // recording stuff goes here
//        wavSave->add(buffer);
//        // printToConsole(S("----> Recording! id: ") + S(id));
//      }
//    } else {
//      // reset
//      if (isRecording) {
//        isRecording = false;
//        wavSave->stopRecording();
//      }
//    }

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

// Save the state of the plugin
void LOFRecordAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
  // Write the state of the AudioProcessorValueTreeState to a memory stream
  juce::MemoryOutputStream stream(destData, true);
  m_params.state.writeToStream(stream);
}

// Load the state of the plugin
void LOFRecordAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
  // Read the state from the data and replace the AudioProcessorValueTreeState state
  auto tree = juce::ValueTree::readFromData(data, size_t(sizeInBytes));
  if (tree.isValid()) {
      m_params.replaceState(tree);

      // if start record is checked, lets start recording
      if (isFirstLaunch && DS->getBool(id, "recordOnLaunch")) {
        DS->setBool(id, "isRecording", true);
        isFirstLaunch = false;
      }
  }
}
