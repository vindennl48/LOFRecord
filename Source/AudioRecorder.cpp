#include "AudioRecorder.h"
//#include <juce_audio_formats/juce_audio_formats.h>


AudioRecorder::AudioRecorder() : 
                sampleRate(48000.0),
                numChannels(2),
                writer(nullptr),
                // file(nullptr),
                isRecording(false)
{
    // Set up the WAV file format
    // formatManager.registerFormat(&wavFormat, true);
}

AudioRecorder::~AudioRecorder()
{
}

void AudioRecorder::startRecording(const juce::String& filePath)
{
    writer.reset(
        wavFormat.createWriterFor(
            new juce::FileOutputStream(
                juce::File::getSpecialLocation(juce::File::userDesktopDirectory)
                .getChildFile(filePath)),
            sampleRate, numChannels, 16, {}, 0)
    );

    // Open the WAV file for writing
/*     file = std::make_unique<juce::FileOutputStream>(
        juce::File::getSpecialLocation(juce::File::userDesktopDirectory)
        .getChildFile(filePath));

    if (writer != nullptr)
        writer.release();

    writer.reset(wavFormat.createWriterFor(file.get(), sampleRate, numChannels, 16, {}, 0)); */
    isRecording = true;
}

void AudioRecorder::stopRecording()
{
    if (!isRecording)
        return;

    isRecording = false;
    // Close the WAV file
    writer.reset();
}

void AudioRecorder::writeBufferToWav(const juce::AudioBuffer<float>& buffer)
{
    // Write the audio data to the WAV file
    if (isRecording && writer != nullptr)
    {
        writer->writeFromFloatArrays(buffer.getArrayOfReadPointers(), numChannels, buffer.getNumSamples());
    }
}
