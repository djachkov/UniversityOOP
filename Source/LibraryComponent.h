/*
  ==============================================================================

    LibraryComponent.h
    Created: 2 Sep 2022 2:38:18pm
    Author:  dmitrii.diachkov

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "TrackComponent.h"
#include "Player.h"

//==============================================================================
/*
*/
class LibraryComponent : public juce::Component,
    public FileDragAndDropTarget
{
public:
    LibraryComponent(Player* _player1, Player* _player2, AudioFormatManager& formatManager);
    ~LibraryComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;
    void searchTracks(String filter);
    void setVisibleTracks();
    void resetVisibleTracks();
    void loadLibrary();
    void saveLibrary();
    void addNewFile(File file);
private:
    Player* player1;
    Player* player2;
    File savedLibrary;
    TextEditor search;
    TextButton searchButton;
    std::vector<File> audioFiles;
    std::vector<File> filteredFiles;

    OwnedArray<TrackComponent> libraryTracks;
    AudioFormatManager& formatManager;
    
    TextButton loadButton{ "LOAD" };
    std::unique_ptr<FileChooser> chooser;
    void loadButtonClicked();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LibraryComponent)
};
