/*
  ==============================================================================

    PlayersComponent.h
    Created: 2 Sep 2022 2:56:29pm
    Author:  dmitrii.diachkov

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Player.h"
#include "PlayerGUI.h"
//==============================================================================
/*
*/
class PlayersComponent  : public juce::Component
{
public:
    PlayersComponent(
        Player* _player1, 
        Player* _player2, 
        AudioFormatManager& formatManagerToUse, 
        AudioThumbnailCache& cacheToUse
    );
    ~PlayersComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Player* player1;
    Player* player2;
    AudioFormatManager& formatManager;
    AudioThumbnailCache& thumbCache;
    PlayerGUI playerGUI1{ player1, formatManager, thumbCache };
    PlayerGUI playerGUI2{ player2, formatManager, thumbCache };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayersComponent)
};
