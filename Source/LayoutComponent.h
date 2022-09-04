/*
  ==============================================================================

    LayoutComponent.h
    Created: 2 Sep 2022 2:27:40pm
    Author:  dmitrii.diachkov

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LibraryComponent.h"
#include "PlayersComponent.h"
#include "ControlsComponent.h"
#include "Player.h"
//==============================================================================
/*
*/
class LayoutComponent  : public juce::Component
{
public:
    LayoutComponent(
        Player* _player1,
        Player* _player2,
        AudioFormatManager& formatManagerToUse,
        AudioThumbnailCache& cacheToUse);
    ~LayoutComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Player* player1;
    Player* player2;
    AudioFormatManager&formatManager;
    AudioThumbnailCache& cache;
    LibraryComponent library{ player1, player2, formatManager };
    PlayersComponent players{ player1, player2, formatManager, cache};
    ControlsComponent controls{ player1, player2 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LayoutComponent)
};
