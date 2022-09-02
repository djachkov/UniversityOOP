/*
  ==============================================================================

    LibraryComponent.h
    Created: 2 Sep 2022 2:38:18pm
    Author:  dmitrii.diachkov

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LibraryComponent  : public juce::Component,
                          public FileDragAndDropTarget
{
public:
    LibraryComponent();
    ~LibraryComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;
private:

    std::vector<juce::File> trackTitles;
    TextButton loadButton{ "LOAD" };
    std::unique_ptr<juce::FileChooser> chooser;
    void loadButtonClicked();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LibraryComponent)
};
