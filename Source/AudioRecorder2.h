#pragma once

#include <JuceHeader.h>

using namespace juce;

class AudioRecorder2  : public AudioIODeviceCallback
{
public:
    AudioRecorder2 ();

    ~AudioRecorder2() override;

    //==============================================================================
    void startRecording (const String& filePath);

    void stopRecording();

    bool isRecording() const;

    //==============================================================================
    void audioDeviceAboutToStart (AudioIODevice* device) override;

    void audioDeviceStopped() override;

    void audioDeviceIOCallbackWithContext (const float* const* inputChannelData, int numInputChannels,
                                           float* const* outputChannelData, int numOutputChannels,
                                           int numSamples, const AudioIODeviceCallbackContext& context) override;

private:
    TimeSliceThread backgroundThread { "Audio Recorder Thread" }; // the thread that will write our audio data to disk
    std::unique_ptr<AudioFormatWriter::ThreadedWriter> threadedWriter; // the FIFO used to buffer the incoming data
    double sampleRate = 0.0;
    int64 nextSampleNum = 0;

    CriticalSection writerLock;
    std::atomic<AudioFormatWriter::ThreadedWriter*> activeWriter { nullptr };
};