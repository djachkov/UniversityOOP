/*
  ==============================================================================

    Player.cpp
    Created: 4 Sep 2022 3:34:14pm
    Author:  djachkov

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Player.h"

//==============================================================================
Player::Player(AudioFormatManager& _formatManager)
    : formatManager(_formatManager)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

Player::~Player()
{
}
void Player::loadTrack(File audioFile)
{
    DBG("Loading track");
    currentFile = audioFile;
    auto* reader = formatManager.createReaderFor(URL{ currentFile }.createInputStream(false));
    if (reader != nullptr) // good file!
    {
        DBG("Good file");
        std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader,
            true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
        status = Ready;
        
    }
}
void Player::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}
void Player::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    resampleSource.getNextAudioBlock(bufferToFill);

}
void Player::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

void Player::start()
{
    transportSource.start();
    status = Playing;
}
void Player::stop()
{
    transportSource.stop();
    status = Stopped;
}
PlaybackStatus Player::getStatus()
{
    return status;
}
void Player::setGain(double gain)
{
    if (gain < 0 || gain > 1.0)
    {
        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1" << std::endl;
    }
    else {
        transportSource.setGain(gain);
    }

}
void Player::setSpeed(double ratio)
{
    if (ratio < 0 || ratio > 100.0)
    {
        std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 100" << std::endl;
    }
    else {
        resampleSource.setResamplingRatio(ratio);
    }
}
void Player::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}

void Player::setPositionRelative(double pos)
{
    if (pos < 0 || pos > 1.0)
    {
        std::cout << "DJAudioPlayer::setPositionRelative pos should be between 0 and 1" << std::endl;
    }
    else {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}

String Player::getFileName()
{
    return currentFile.getFileName();
}
URL Player::getURL()
{
    return URL{ currentFile };
}
AudioTransportSource* Player::getTransportSource()
{
    return &transportSource ;
}
double Player::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}