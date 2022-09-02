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
#include "PlaylistComponent.h"
#include "PlayersComponent.h"
#include "ControlsComponent.h"
//==============================================================================
/*
*/
class LayoutComponent  : public juce::Component
{
public:
    LayoutComponent();
    ~LayoutComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    LibraryComponent library;
    PlaylistComponent playlist;
    PlayersComponent players;
    ControlsComponent controls;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LayoutComponent)
};
