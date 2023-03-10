#pragma once

#include <JuceHeader.h>
#include "DataStore.h"
#include "Debug.h"

#define NUM_BLOCKS 64

class WavSave : public juce::Thread {
  juce::AbstractFifo       fifo;
  juce::AudioBuffer<float> buffer;
  juce::String             filepath;
  int numChannels;
  int sampleRate;
  int bitDepth;
  int bufferSize;
  int id = 0;

public:
  WavSave(int newID)
    : juce::Thread("WavSave"),
      fifo(512),
      buffer(2, 512),
      numChannels(2),
      sampleRate(48000),
      bitDepth(16),
      bufferSize(512),
      id(newID)
  {}

  juce::String createFilename() {
    juce::String date      = juce::Time::getCurrentTime().formatted("%y%m%d");
    juce::int64  time      = DS->getTime(id);
    juce::String trackName = DS->getString(id, "trackName");
    juce::String groupName = DS->getString(id, "groupName");
    juce::String directory = DS->getString(id, "directory");

    juce::String filename = date + "-" + juce::String(time) + "-" + groupName + "-" + trackName + "-";

    // get the number of files in the directory starting with filename
    juce::File parent = juce::File(directory);
    // create filename search string that removes time from the middle
    juce::String search = date + "-*" + "-" + groupName + "-" + trackName + "-*";
    // count all files in directory that start with search string
    juce::Array<juce::File> files = parent.findChildFiles(juce::File::TypesOfFileToFind::findFiles, true, search);
    // set a variable 'count' to the number of files found
    int count = files.size();

    // join filename and count with 3 digits and .wav, pad with zeros if needed
    filename = filename + juce::String(count).paddedLeft('0', 3) + ".wav";

    return filename;
  }

  void startRecording(int newNumChannels, int newSampleRate, int newBufferSize) {
    // check if thread is running
    if (isThreadRunning()) return;

    numChannels = newNumChannels;
    sampleRate  = newSampleRate;
    bufferSize  = newBufferSize;

    juce::String parent   = DS->getString(id, "directory");
    juce::String filename = createFilename();

    filepath = parent + "/" + filename;

    printToConsole(S("----> Num Channels: ") + S(numChannels));
    printToConsole(S("----> Sample Rate:  ") + S(sampleRate));
    printToConsole(S("----> Buffer Size:  ") + S(bufferSize));
    printToConsole(S("----> File Path:    ") + S(filepath));

    buffer.setSize(numChannels, bufferSize * NUM_BLOCKS);
    buffer.clear();
    fifo.setTotalSize(bufferSize * NUM_BLOCKS);
    fifo.reset();
    startThread();
  }

  void stopRecording() {
    if (!isThreadRunning()) return;
    stopThread(1000);
  }

  /**
   * Make sure to check, ONLY run when thread is running.. we need to set the
   * buffer up first
   * */
  void add(juce::AudioBuffer<float>& samples) {
    int start1, size1, start2, size2;
    fifo.prepareToWrite(samples.getNumSamples(), start1, size1, start2, size2);
    if (size1 > 0) {
      for (int channel = 0; channel < samples.getNumChannels(); ++channel) {
        buffer.copyFrom(channel, start1, samples.getReadPointer(channel), size1);
      }
    }
    if (size2 > 0) {
      for (int channel = 0; channel < samples.getNumChannels(); ++channel) {
        buffer.copyFrom(channel, start2, samples.getReadPointer(channel, size1), size2);
      }
    }
    fifo.finishedWrite(size1 + size2);
  }

  /**
   * Actual Thread Function
   * */
  void run() override {
    juce::WavAudioFormat wavFormat;
    
    auto writer = wavFormat.createWriterFor(
      new juce::FileOutputStream(
        juce::File::getSpecialLocation(juce::File::userDesktopDirectory)
        .getChildFile(filepath)
      ),
      sampleRate, numChannels, bitDepth, {}, 0
    );

    if (writer != nullptr) {
      juce::AudioBuffer<float> samples(numChannels, bufferSize);

      while (!threadShouldExit()) {
        if (fifo.getNumReady() >= samples.getNumSamples()) {
          get(samples);
          writer->writeFromAudioSampleBuffer(samples, 0, samples.getNumSamples());
        }
        else {
          juce::Thread::sleep(1);
        }
      }
      writer->flush();
    }
  }

private:
  void get(juce::AudioBuffer<float>& samples) {
    int start1, size1, start2, size2;
    fifo.prepareToRead(samples.getNumSamples(), start1, size1, start2, size2);
      if (size1 > 0) {
        for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
          samples.copyFrom (channel, 0, buffer.getReadPointer (channel, start1), size1);
        }
      }
      if (size2 > 0) {
        for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
          samples.copyFrom (channel, size1, buffer.getReadPointer (channel, start2), size2);
        }
      }
    fifo.finishedRead(size1 + size2);
  }

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WavSave)
};
