/*
  ==============================================================================

    DeckGUI.h
    Created: 6 Sep 2023 5:31:10pm
    Author:  Hrc

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "PlaylistComponent.h"
 
//==============================================================================
/*
*/

// here are my parts of code
class DeckGUI  : public juce::Component, 
                 public juce::Button::Listener, 
                 public juce::Slider::Listener,
                 public juce::FileDragAndDropTarget,
                 public juce::Timer
{
public:
    DeckGUI(DJAudioPlayer* player,
            juce::AudioFormatManager & formatManagerToUse,
            juce::AudioThumbnailCache & cacheToUse);
    ~DeckGUI();    

    void paint (juce::Graphics&) override;
    void resized() override;

    /** implement Button::Listener*/
    void buttonClicked(juce::Button*) override;

    /** implement Slider::Listener*/
    void sliderValueChanged(juce::Slider* slider) override;

    bool isInterestedInFileDrag(const juce::StringArray &files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;

    // here are my parts of code
    void timerCallback() override; //Timer function which is used to check whether user has selected whether to loop or not
    void playlistToDeckGUI(); // This function reads which audio file the user has selected to be added into either Deck 1 or 2

private:
    // here are my parts of code
    juce::TextButton playButton{ "PLAY" };
    juce::TextButton stopButton{ "STOP" };
    juce::TextButton loadButton{ "LOAD" };

    juce::ToggleButton loopButton{ "LOOP" };
    juce::TextEditor trackName;
    juce::String mtrackName;

    juce::Label volSliderLabel;
    juce::Label speedSliderLabel;

    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;

    DJAudioPlayer* player;
    WaveformDisplay waveformDisplay;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)

};
