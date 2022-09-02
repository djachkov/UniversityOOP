/*
  ==============================================================================

    LayoutComponent.cpp
    Created: 2 Sep 2022 2:27:40pm
    Author:  dmitrii.diachkov

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LayoutComponent.h"

//==============================================================================
LayoutComponent::LayoutComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    library.setColour(juce::ResizableWindow::backgroundColourId, Colours::aqua);
    playlist.setColour(juce::ResizableWindow::backgroundColourId, Colours::brown);

    addAndMakeVisible(library);
    addAndMakeVisible(playlist);
    addAndMakeVisible(players);
    addAndMakeVisible(controls);

}

LayoutComponent::~LayoutComponent()
{
}

void LayoutComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("LayoutComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void LayoutComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto area = getLocalBounds();
    auto sideWidth = area.getWidth() / 5;
    auto controlsHeight = area.getHeight() / 5;
    library.setBounds(area.removeFromLeft(sideWidth));
    playlist.setBounds(area.removeFromRight(sideWidth));
    controls.setBounds(area.removeFromBottom(controlsHeight));
    players.setBounds(area.removeFromTop(area.getHeight()));
}
