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
LibraryComponent::LibraryComponent(Player* _player1, Player* _player2, AudioFormatManager& formatManager) : player1(_player1), player2(_player2), formatManager(formatManager)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    loadLibrary();
    filteredFiles = audioFiles;
    setVisibleTracks();
    addAndMakeVisible(&loadButton);
    addAndMakeVisible(search);
    addAndMakeVisible(searchButton);
    search.setTitle("Search");
    searchButton.setButtonText("Search");
    loadButton.setButtonText("Open file");
    loadButton.onClick = [this] { loadButtonClicked(); };
    searchButton.onClick = [this] { searchTracks(search.getText()); };
    std::cout << "Inthecomp\n";
}

LibraryComponent::~LibraryComponent()
{
}
void LibraryComponent::addNewFile(File file)
{
    bool added = false;
    for (File oldFile : audioFiles) {
        if (file.getFileName().compare(oldFile.getFileName()) == 0) { 
            added = true; 
            DBG("FILE EXISTS IN THE LIBRARY");
        }
    }
    if (!added) {
        audioFiles.push_back(file);
    }   
}
void LibraryComponent::paint(juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(juce::Colours::white);
    g.setFont(14.0f);
    g.drawText("LibraryComponent", getLocalBounds(),
        juce::Justification::centred, true);   // draw some placeholder text
}

void LibraryComponent::loadButtonClicked()
{
    std::cout << "Adding file" << std::endl;
    auto fileChooserFlags =
        FileBrowserComponent::openMode |
        FileBrowserComponent::canSelectFiles;
    chooser.reset(new FileChooser("Select track", File::getSpecialLocation(File::userMusicDirectory),
        "*.wav;*.mp3", false));

    chooser->launchAsync(fileChooserFlags, [this](const FileChooser& fileChooser)
        {
            std::cout << "Choose  " << std::endl;
            auto file = fileChooser.getResult();
            std::cout << "Chosen:  " << file.getFileName() << std::endl;
            addNewFile(file);
            saveLibrary();
            //
            
            //player->loadURL(URL{ chooser.getResult() });
            //// and now the waveformDisplay as well
            //waveformDisplay.loadURL(URL{ chooser.getResult() });
        });

   
}
void LibraryComponent::loadLibrary()
{
    formatManager.registerBasicFormats();
    savedLibrary = File::getCurrentWorkingDirectory().getChildFile("library.txt");
    savedLibrary.create();
    std::unique_ptr<FileInputStream> input(savedLibrary.createInputStream());
    while (!input->isExhausted())
    {
        String savedFile = input->readNextLine();
        DBG(savedFile);
        File track(savedFile);
        if (track.exists()) {
            addNewFile(track);
        }
    }
}
void LibraryComponent::saveLibrary()
{
    savedLibrary.replaceWithText("");
    for (File file : audioFiles) {
        savedLibrary.appendText(file.getFullPathName() + "\n");
    }
}

void LibraryComponent::resetVisibleTracks()
{
    for (auto& displayedTrack : libraryTracks) {
        removeChildComponent(displayedTrack);
    }
    libraryTracks.clear();
    resized();
}
void LibraryComponent::setVisibleTracks()
{   
    for (File& track : filteredFiles) {
        auto* visibleTrack = new TrackComponent(player1, player2, track, formatManager);
        addAndMakeVisible(libraryTracks.add(visibleTrack));
    }
    resized();
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

void LibraryComponent::searchTracks(String filter)
{
    DBG("searching");
    std::cout << "Applying filter: " << filter << std::endl;
    filteredFiles.clear();
    if (filter.length() < 1) {
        filteredFiles = audioFiles;
    }
    else {
        // Copy file to the filtered vector IF the filename contains the filter string [using lambda function to check the condition]
        std::copy_if(audioFiles.begin(), audioFiles.end(), std::back_inserter(filteredFiles), [filter](File track) {return track.getFileName().contains(filter); });
    }
    resetVisibleTracks();
    setVisibleTracks();
}

void LibraryComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto area = getLocalBounds();
    auto track = area.getHeight() / 10;

    loadButton.setBounds(area.removeFromTop(20));
    auto searchArea = area.removeFromTop(20);
    searchButton.setBounds(searchArea.removeFromRight(60));
    search.setBounds(searchArea.removeFromRight(searchArea.getWidth()));

    area.removeFromTop(20);
    auto margin = 5;
    for (auto* t : libraryTracks)\
    {
        auto index = libraryTracks.indexOf(t);

        t->setBounds(area.removeFromTop(track).reduced(margin));
    }

}
