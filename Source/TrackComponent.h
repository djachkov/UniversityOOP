/*
  ==============================================================================

    TrackComponent.h
    Created: 3 Sep 2022 8:53:40am
    Author:  djachkov

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Player.h"

//==============================================================================
/*
*/
class TrackComponent : public Component
{
public:
    TrackComponent(
        Player* _player1,
        Player* _player2,
        File& _track,
        AudioFormatManager& _formatManager);
    ~TrackComponent() override;

    void addTrackToPlayer(Player* player);
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    Player* player1;
    Player* player2;
    
    File track;
    TextButton addToPlaylist1{ "P1" };
    TextButton addToPlaylist2{ "P2" };
    Label trackLength;
    Label trackName;
    AudioFormatManager& fm;
};
