/*
  ==============================================================================

    ControlsComponent.h
    Created: 2 Sep 2022 2:33:17pm
    Author:  dmitrii.diachkov

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ControlsComponent  : public juce::Component
{
public:
    ControlsComponent();
    ~ControlsComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsComponent)
};
