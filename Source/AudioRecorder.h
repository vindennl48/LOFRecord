
#pragma once

#include <juce_audio_formats/juce_audio_formats.h>

class AudioRecorder
{
public:
    AudioRecorder();
    ~AudioRecorder();
    void startRecording(const juce::String& filePath);
    void stopRecording();
    void writeBufferToWav(const juce::AudioBuffer<float>& buffer);

private:
    // juce::AudioFormatManager formatManager;
    juce::WavAudioFormat wavFormat;
    // std::unique_ptr<juce::FileOutputStream> file;
    std::unique_ptr<juce::AudioFormatWriter> writer;
    double sampleRate;
    int numChannels;
    bool isRecording;
};
