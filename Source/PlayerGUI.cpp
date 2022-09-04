/*
  ==============================================================================

    PlayerGUI.cpp
    Created: 4 Sep 2022 10:57:39am
    Author:  djachkov

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlayerGUI.h"

//==============================================================================
PlayerGUI::PlayerGUI(Player* _player,
                    AudioFormatManager& formatManagerToUse,
                    AudioThumbnailCache& cacheToUse
                    ) : player(_player),
                        waveformDisplay(formatManagerToUse, cacheToUse)
{

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(waveformDisplay);
    stopButton.setEnabled(false);
    playButton.setEnabled(false);
    playButton.addListener(this);
    stopButton.addListener(this);
    startTimer(500);


}

PlayerGUI::~PlayerGUI()
{
}

void PlayerGUI::paint (juce::Graphics& g)
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
    String text;
    if (player->getStatus() > Waiting) {
        text = player->getFileName();
    }
    else {
        text = "Select file from library";
    }
    
    g.drawText (text, getLocalBounds(),
                juce::Justification::top, true);   // draw some placeholder text
}
void PlayerGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        player->start();
        waveformDisplay.loadURL(player -> getURL());
        waveformDisplay.setTransportSource(player->getTransportSource());
    }
    if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->setPosition(0.0);
        player->stop();

    }
}
void PlayerGUI::resized()
{
    auto area = getLocalBounds();
    auto buttonsArea = area.removeFromRight(100);
    auto playArea = buttonsArea.removeFromRight(50);
    auto stopArea = buttonsArea.removeFromRight(50);

    playButton.setBounds(playArea.getCentreX(), playArea.getCentreY(), 20, 20);
    stopButton.setBounds(stopArea.getCentreX(), stopArea.getCentreY(), 40, 20);
    waveformDisplay.setBounds(area.removeFromLeft(area.getWidth()));

}
void PlayerGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(
        player->getPositionRelative());
    controlPlayback();
}

void PlayerGUI::controlPlayback()
{
    auto status = player->getStatus();
    switch (status)
    {
    case Ready:
        playButton.setEnabled(true);
        break;

    case Stopped:
        stopButton.setEnabled(false);
        playButton.setEnabled(true);
        break;

    case Playing:
        playButton.setEnabled(false);
        stopButton.setEnabled(true);
        break;

    }
}