
#pragma once

#include <JuceHeader.h>

// class to listen to the transport in the daw

class TransportListener : public juce::AudioProcessorListener
{
public:
    TransportListener()
    {
        // Register this class as a listener to the currently playing AudioProcessor
        if (auto* processor = juce::AudioProcessor::getCurrentlyPlayingAudioProcessor())
            processor->addChangeListener(this);
    }
    
    void audioProcessorChanged (juce::AudioProcessor *processor, const ChangeDetails &details) override
    {
        juce::AudioPlayHead* playHead = processor->getPlayHead();
        if (playHead != nullptr)
        {
            juce::AudioPlayHead::CurrentPositionInfo positionInfo;
            playHead->getCurrentPosition (positionInfo);
            isPlaying = positionInfo.isPlaying;
        }
    }
    
    bool getIsPlaying() const
    {
        return isPlaying;
    }
    
private:
    bool isPlaying = false;
};
