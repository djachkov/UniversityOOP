/*
  ==============================================================================

    PlayersComponent.h
    Created: 2 Sep 2022 2:56:29pm
    Author:  dmitrii.diachkov

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PlayersComponent  : public juce::Component
{
public:
    PlayersComponent();
    ~PlayersComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayersComponent)
};
