/*
  ==============================================================================

    Player.h
    Created: 4 Sep 2022 3:34:14pm
    Author:  djachkov

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
enum PlaybackStatus
{
    Waiting,
    Ready,
    Stopped,
    Playing,
};
class Player  : public AudioSource
{
public:
    Player(AudioFormatManager& _formatManager);
    ~Player() override;

    void loadTrack(File audioFile);
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    void timerCallback();

    void controlPlayback();
    void start();
    void stop();

    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSecs);
    void setPositionRelative(double pos);

    double getPositionRelative();
    PlaybackStatus getStatus();
    AudioTransportSource* getTransportSource();
    String getFileName();
    URL getURL();

private:
    AudioFormatManager& formatManager;
    File currentFile;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    ResamplingAudioSource resampleSource{ &transportSource, false, 2 };
    PlaybackStatus status;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Player)
};
