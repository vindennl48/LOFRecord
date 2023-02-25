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
    // wavFormat.registerBasicFormats();
}

AudioRecorder::~AudioRecorder()
{
}

void AudioRecorder::setSampleRate(double sampleRate)
{
    this->sampleRate = sampleRate;
}

void AudioRecorder::setNumChannels(int numChannels)
{
    this->numChannels = numChannels;
}

void AudioRecorder::startRecording(const juce::String& filepath)
{
    writer.reset(
        wavFormat.createWriterFor(
            new juce::FileOutputStream(
                juce::File::getSpecialLocation(juce::File::userDesktopDirectory)
                .getChildFile(filepath)),
            sampleRate, numChannels, 16, {}, 0)
    );
    isRecording = true;
}

// startRecording for mp3
// Not working yet..
void AudioRecorder::startRecordingMP3(const juce::String& filepath)
{
    // Create an instance of the MP3 format object
    juce::AudioFormat* format = formatManager.findFormatForFileExtension("mp3");

    if (format != nullptr)
    {
        writer.reset(format->createWriterFor(
            new juce::FileOutputStream(
                juce::File::getSpecialLocation(juce::File::userDesktopDirectory)
                .getChildFile(filepath)
            ),
            sampleRate, numChannels, 128000, {}, 0));
        isRecording = true;
    }
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
