/*
  ==============================================================================

    PlayerGUI.h
    Created: 4 Sep 2022 10:57:39am
    Author:  djachkov

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Player.h"
#include "WaveformDisplay.h"

//==============================================================================
/*
*/
class PlayerGUI  : public juce::Component,
                   public Button::Listener,
                   public Timer
{
public:
    PlayerGUI(
            Player* _player,
            AudioFormatManager& formatManagerToUse,
            AudioThumbnailCache& cacheToUse);
    ~PlayerGUI() override;

    void buttonClicked(Button*) override;
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;
    void controlPlayback();

private:
    ArrowButton playButton{ "Play", 90.0f, Colours::green };
    TextButton stopButton{ "Stop" };

    WaveformDisplay waveformDisplay;

    Player* player;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayerGUI)
};
