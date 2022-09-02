/*
  ==============================================================================

    CustomGUI.cpp
    Created: 2 Sep 2022 9:46:55am
    Author:  dmitrii.diachkov

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomGUI.h"

//==============================================================================
CustomGUI::CustomGUI(DJAudioPlayer* _player, 
                AudioFormatManager & 	formatManagerToUse,
                AudioThumbnailCache & 	cacheToUse
           ) : player(_player), 
               waveformDisplay(formatManagerToUse, cacheToUse)
{

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
       
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);

    addAndMakeVisible(waveformDisplay);


    playButton.addListener(this);
    stopButton.addListener(this);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);


    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 100.0);
    posSlider.setRange(0.0, 1.0);

    startTimer(500);


}

CustomGUI::~CustomGUI()
{
    stopTimer();
}

void CustomGUI::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("CustomGUI", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void CustomGUI::resized()
{
    double rowH = getHeight() / 8; 
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);  
    volSlider.setBounds(0, rowH * 2, getWidth(), rowH);
    speedSlider.setBounds(0, rowH * 3, getWidth(), rowH);
    posSlider.setBounds(0, rowH * 4, getWidth(), rowH);
    waveformDisplay.setBounds(0, rowH * 5, getWidth(), rowH * 2);

}

void CustomGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        player->start();
    }
     if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->stop();

    }
    //   if (button == &loadButton)
    //{
    //    auto fileChooserFlags = 
    //    FileBrowserComponent::canSelectFiles;
    //    fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
    //    {
    //        player->loadURL(URL{chooser.getResult()});
    //        // and now the waveformDisplay as well
    //        waveformDisplay.loadURL(URL{chooser.getResult()}); 
    //    });
    //}
    // if (button == &loadButton)
    // {
    //     FileChooser chooser{"Select a file..."};
    //     if (chooser.browseForFileToOpen())
    //     {
    //         player->loadURL(URL{chooser.getResult()});
    //         waveformDisplay.loadURL(URL{chooser.getResult()});
            
    //     }


    // }
}

void CustomGUI::sliderValueChanged (Slider *slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
    
}

bool CustomGUI::isInterestedInFileDrag (const StringArray &files)
{
  std::cout << "CustomGUI::isInterestedInFileDrag" << std::endl;
  return true; 
}

void CustomGUI::filesDropped (const StringArray &files, int x, int y)
{
  std::cout << "CustomGUI::filesDropped" << std::endl;
  if (files.size() == 1)
  {
    player->loadURL(URL{File{files[0]}});
  }
}

void CustomGUI::timerCallback()
{
    //std::cout << "CustomGUI::timerCallback" << std::endl;
    waveformDisplay.setPositionRelative(
            player->getPositionRelative());
}


    

