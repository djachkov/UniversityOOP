/*
  ==============================================================================

    LibraryComponent.cpp
    Created: 2 Sep 2022 2:38:18pm
    Author:  dmitrii.diachkov

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LibraryComponent.h"

//==============================================================================
LibraryComponent::LibraryComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(&loadButton);
    loadButton.setButtonText("Open file");
    loadButton.onClick = [this] { loadButtonClicked(); };
}

LibraryComponent::~LibraryComponent()
{
}

void LibraryComponent::paint (juce::Graphics& g)
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
    g.drawText ("LibraryComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void LibraryComponent::loadButtonClicked()
{

    auto fileChooserFlags =
        FileBrowserComponent::openMode |
        FileBrowserComponent::canSelectFiles;
    chooser = std::make_unique<juce::FileChooser>("Select a Wave file to play...",
        juce::File{},
        "*.wav;*.mp3");
    chooser -> launchAsync(fileChooserFlags, [this](const FileChooser& fileChooser)
        {
            auto file = fileChooser.getResult();
            trackTitles.push_back(file);
            std::cout << trackTitles.size() << std::endl;
            //player->loadURL(URL{ chooser.getResult() });
            //// and now the waveformDisplay as well
            //waveformDisplay.loadURL(URL{ chooser.getResult() });
        });
 
}
bool LibraryComponent::isInterestedInFileDrag(const StringArray& files)
{
    std::cout << "CustomGUI::isInterestedInFileDrag" << std::endl;
    return true;
}

void LibraryComponent::filesDropped(const StringArray& files, int x, int y)
{
    std::cout << "CustomGUI::filesDropped" << std::endl;
}
void LibraryComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto area = getLocalBounds();

    loadButton.setBounds(area.removeFromTop(20));

}
