#include "AudioRecorder2.h"

AudioRecorder2::AudioRecorder2 ()
    // : thumbnail (thumbnailToUpdate)
{
    backgroundThread.startThread();
}

AudioRecorder2::~AudioRecorder2()
{
    stopRecording();
}

    // writer.reset(
    //     wavFormat.createWriterFor(
    //         new juce::FileOutputStream(
    //             juce::File::getSpecialLocation(juce::File::userDesktopDirectory)
    //             .getChildFile(filepath)),
    //         sampleRate, numChannels, 16, {}, 0)
    // );

//==============================================================================
// void AudioRecorder2::startRecording (const File& file)
void AudioRecorder2::startRecording (const String& filepath)
{
    if (isRecording()) return;

    stopRecording();

    if (sampleRate > 0)
    {
        // // Create an OutputStream to write to our destination file...
        // file.deleteFile();

        auto file = juce::File::getSpecialLocation(juce::File::userDesktopDirectory).getChildFile(filepath);

        if (auto fileStream = std::unique_ptr<FileOutputStream> (file.createOutputStream()))
        {
            // Now create a WAV writer object that writes to our output stream...
            WavAudioFormat wavFormat;

            if (auto writer = wavFormat.createWriterFor (fileStream.get(), 48000, 1, 16, {}, 0))
            {
                fileStream.release(); // (passes responsibility for deleting the stream to the writer object that is now using it)

                // Now we'll create one of these helper objects which will act as a FIFO buffer, and will
                // write the data to disk on our background thread.
                threadedWriter.reset (new AudioFormatWriter::ThreadedWriter (writer, backgroundThread, 32768));

                // Reset our recording thumbnail
                // thumbnail.reset (writer->getNumChannels(), writer->getSampleRate());
                nextSampleNum = 0;

                // And now, swap over our active writer pointer so that the audio callback will start using it..
                const ScopedLock sl (writerLock);
                activeWriter = threadedWriter.get();
            }
        }
    }
}

void AudioRecorder2::stopRecording()
{
    // First, clear this pointer to stop the audio callback from using our writer object..
    {
        const ScopedLock sl (writerLock);
        activeWriter = nullptr;
    }

    // Now we can delete the writer object. It's done in this order because the deletion could
    // take a little time while remaining data gets flushed to disk, so it's best to avoid blocking
    // the audio callback while this happens.
    threadedWriter.reset();
}

bool AudioRecorder2::isRecording() const
{
    return activeWriter.load() != nullptr;
}

//==============================================================================
void AudioRecorder2::audioDeviceAboutToStart (AudioIODevice* device)
{
    sampleRate = device->getCurrentSampleRate();
}

void AudioRecorder2::audioDeviceStopped()
{
    sampleRate = 0;
}

void AudioRecorder2::audioDeviceIOCallbackWithContext (const float* const* inputChannelData, int numInputChannels,
                                        float* const* outputChannelData, int numOutputChannels,
                                        int numSamples, const AudioIODeviceCallbackContext& context)
{
    ignoreUnused (context);

    const ScopedLock sl (writerLock);

    if (activeWriter.load() != nullptr /*&& numInputChannels >= thumbnail.getNumChannels()*/)
    {
        // Write the inputChannelData as two channels to the activeWriter
        if (numInputChannels >= 2)
        {
            float** channelData = new float*[2];
            channelData[0] = const_cast<float*>(inputChannelData[0]);
            channelData[1] = const_cast<float*>(inputChannelData[1]);

            activeWriter.load()->write (channelData, numSamples);

            delete[] channelData;
        }

        nextSampleNum += numSamples;
    }

    // if (activeWriter.load() != nullptr /*&& numInputChannels >= thumbnail.getNumChannels()*/)
    // {
    //     activeWriter.load()->write (inputChannelData, numSamples);

    //     // // Create an AudioBuffer to wrap our incoming data, note that this does no allocations or copies, it simply references our input data
    //     // AudioBuffer<float> buffer (const_cast<float**> (inputChannelData), thumbnail.getNumChannels(), numSamples);
    //     // thumbnail.addBlock (nextSampleNum, buffer, 0, numSamples);
    //     nextSampleNum += numSamples;
    // }

    // We need to clear the output buffers, in case they're full of junk..
    for (int i = 0; i < numOutputChannels; ++i)
        if (outputChannelData[i] != nullptr)
            FloatVectorOperations::clear (outputChannelData[i], numSamples);
}