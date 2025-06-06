/*
  ==============================================================================

    WaveformDisplay.h
    Created: 2 Sep 2022 9:55:42am
    Author:  dmitrii.diachkov

  ==============================================================================
*/
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class WaveformDisplay    : public Component, 
                           public ChangeListener
{
public:
    WaveformDisplay( AudioFormatManager & 	formatManagerToUse,
                    AudioThumbnailCache & 	cacheToUse );
    ~WaveformDisplay();

    void paint (Graphics&) override;
    void resized() override;

    void changeListenerCallback (ChangeBroadcaster *source) override;

    void loadURL(URL audioURL);

    /** set the relative position of the playhead*/
    void setPositionRelative(double pos);
    void mouseDrag(const MouseEvent& e) override;
    void setTransportSource(AudioTransportSource* newSource);
 

private:
    AudioThumbnail audioThumb;
    AudioTransportSource* transportSource = nullptr;
    bool fileLoaded; 
    double position;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
