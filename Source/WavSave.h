#pragma once

#include <JuceHeader.h>

#define NUM_BLOCKS 64

class WavSave : public juce::Thread {
public:

  WavSave(int numChannels, int sampleRate, int bufferSize)
    : juce::Thread("WavSave"),
      fifo(bufferSize * NUM_BLOCKS),
      buffer(numChannels, bufferSize * NUM_BLOCKS),
      numChannels(numChannels),
      sampleRate(sampleRate),
      bitDepth(16),
      bufferSize(bufferSize)
  {}

  void startRecording(const juce::String& filePath) {
    // check if thread is running
    if (isThreadRunning()) return;

    this->filePath = filePath;

    fifo.reset();
    startThread();
  }
  void stopRecording() {
    // exit thread
    signalThreadShouldExit();
  }

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

  void run() override {
    juce::WavAudioFormat wavFormat;
    
    auto writer = wavFormat.createWriterFor(
      new juce::FileOutputStream(
        juce::File::getSpecialLocation(juce::File::userDesktopDirectory)
        .getChildFile(filePath)
      ),
      sampleRate, numChannels, bitDepth, {}, 0
    );

    if (writer != nullptr) {
      juce::AudioBuffer<float> samples(numChannels, bufferSize);

      while (!threadShouldExit()) {
        if (fifo.getNumReady() >= samples.getNumSamples()) {
          get(samples);
          writer->writeFromAudioSampleBuffer(samples, numChannels, samples.getNumSamples());
        }
        else {
          juce::Thread::sleep(1);
        }
      }
      writer->flush();
    }
  }

  juce::AbstractFifo       fifo;
  juce::AudioBuffer<float> buffer;
  juce::String             filePath;
  int numChannels;
  int sampleRate;
  int bitDepth;
  int bufferSize;
};
