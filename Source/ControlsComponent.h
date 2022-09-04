/*
  ==============================================================================

    ControlsComponent.h
    Created: 2 Sep 2022 2:33:17pm
    Author:  dmitrii.diachkov

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Player.h"

//==============================================================================
/*
*/
class ControlsComponent  : public juce::Component,
                           public Slider::Listener
{
public:
    ControlsComponent(Player* _player1, Player* _player2);
    ~ControlsComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider) override;

private:
    Player* player1;
    Player* player2;

    Slider volSlider1;
    Slider speedSlider1;
    
    Slider volSlider2;
    Slider speedSlider2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsComponent)
};
