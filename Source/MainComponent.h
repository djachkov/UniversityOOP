#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "CustomGUI.h"
#include "LayoutComponent.h"
#include "PlaylistComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
     
    PlaylistComponent playlistComponent;
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{100}; 

    DJAudioPlayer player1{formatManager};
    CustomGUI deckGUI1{&player1, formatManager, thumbCache}; 
    LayoutComponent layout; 

    DJAudioPlayer player2{formatManager};
    CustomGUI deckGUI2{&player2, formatManager, thumbCache}; 

    MixerAudioSource mixerSource; 
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
