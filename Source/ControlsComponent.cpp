/*
  ==============================================================================

    ControlsComponent.cpp
    Created: 2 Sep 2022 2:33:17pm
    Author:  dmitrii.diachkov

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ControlsComponent.h"

//==============================================================================
ControlsComponent::ControlsComponent(Player* _player1, Player* _player2)
    : player1(_player1),
      player2(_player2)
{

    addAndMakeVisible(volSlider1);
    addAndMakeVisible(speedSlider1);
    addAndMakeVisible(volSlider2);
    addAndMakeVisible(speedSlider2);

    volSlider1.setSliderStyle(Slider::LinearHorizontal);
    volSlider2.setSliderStyle(Slider::LinearHorizontal);    
    speedSlider1.setSliderStyle(Slider::LinearHorizontal);
    speedSlider2.setSliderStyle(Slider::LinearHorizontal);

    volSlider1.setTextValueSuffix(" Volume");
    volSlider2.setTextValueSuffix(" Volume");
    speedSlider1.setTextValueSuffix(" Speed");
    speedSlider2.setTextValueSuffix(" Speed");

    volSlider1.setNumDecimalPlacesToDisplay(1);
    volSlider2.setNumDecimalPlacesToDisplay(1);
    speedSlider1.setNumDecimalPlacesToDisplay(1);
    speedSlider2.setNumDecimalPlacesToDisplay(1);

    volSlider1.addListener(this);
    speedSlider1.addListener(this);
    volSlider2.addListener(this);
    speedSlider2.addListener(this);


    volSlider1.setRange(0.0, 1.0);
    volSlider2.setRange(0.0, 1.0);
    speedSlider1.setRange(0.1, 100.0);
    speedSlider2.setRange(0.1, 100.0);

}

ControlsComponent::~ControlsComponent()
{
}

void ControlsComponent::paint (juce::Graphics& g)
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
    g.drawText ("ControlsComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}
void ControlsComponent::sliderValueChanged(Slider* slider)
{
    if (slider == &volSlider1)
    {
        player1->setGain(slider->getValue());
    }

    if (slider == &speedSlider1)
    {
        player1->setSpeed(slider->getValue());
    }

   
    if (slider == &volSlider2)
    {
        player2->setGain(slider->getValue());
    }

    if (slider == &speedSlider2)
    {
        player2->setSpeed(slider->getValue());
    }

 

}
void ControlsComponent::resized()
{
    auto area = getLocalBounds();
    auto areaLeft = area.removeFromLeft(area.getWidth() / 2);
    auto areaRight = area.removeFromLeft(area.getWidth() / 2);
    auto row = area.getHeight() / 6;
    volSlider1.setBounds(areaLeft.removeFromTop(row));
    speedSlider1.setBounds(areaLeft.removeFromTop(row));

    volSlider2.setBounds(areaRight.removeFromTop(row));
    speedSlider2.setBounds(areaRight.removeFromTop(row));
    
}
