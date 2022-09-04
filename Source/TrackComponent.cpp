/*
  ==============================================================================

    TrackComponent.cpp
    Created: 3 Sep 2022 8:53:40am
    Author:  djachkov

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TrackComponent.h"

//==============================================================================
TrackComponent::TrackComponent(
    Player* _player1,
    Player* _player2,
    File& _track,
    AudioFormatManager& _formatManager
) : player1(_player1),
    player2(_player2),
    track(_track),
    fm(_formatManager)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    auto reader = fm.createReaderFor(track);
    double length = reader->lengthInSamples / reader->sampleRate;

    addAndMakeVisible(trackName);
    addAndMakeVisible(trackLength);
    addAndMakeVisible(addToPlaylist1);
    addAndMakeVisible(addToPlaylist2);
    addToPlaylist1.onClick = [this]{ addTrackToPlayer(player1); };
    addToPlaylist2.onClick = [this]{ addTrackToPlayer(player2); };
    trackName.setText(track.getFileName(), dontSendNotification);
    trackLength.setText(std::to_string(length), dontSendNotification);


}

TrackComponent::~TrackComponent()
{
}
void TrackComponent::addTrackToPlayer(Player* player)
{
    DBG("Push to player");
    player->loadTrack(track);
}
void TrackComponent::paint(juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(juce::Colours::mediumvioletred);

}

void TrackComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto area = getLocalBounds();
    auto row = area.getHeight() / 2;
    auto btnArea = area.removeFromRight(80);
    addToPlaylist2.setBounds(btnArea.removeFromRight(40));
    addToPlaylist1.setBounds(btnArea.removeFromRight(40));
    trackLength.setBounds(area.removeFromBottom(row));
    trackName.setBounds(area.removeFromBottom(row));

}
