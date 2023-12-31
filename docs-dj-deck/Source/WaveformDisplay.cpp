/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 6 Sep 2023 5:31:10pm
    Author:  Hrc

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"
 
//==============================================================================
WaveformDisplay::WaveformDisplay(juce::AudioFormatManager& formatManagerToUse,
                                 juce::AudioThumbnailCache& cacheToUse) 
                                    : audioThumb(1000,formatManagerToUse,cacheToUse),
                                      fileLoaded(false),
                                      position(0)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    // here are my parts of code
    g.fillAll(juce::Colours::yellow);   // clear the background

    g.setColour (juce::Colours::blueviolet);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(juce::Colours::deeppink);
    if (fileLoaded) {
        audioThumb.drawChannel(g,
            getLocalBounds(),
            0,
            audioThumb.getTotalLength(),
            0,
            1.0f);
        g.setColour(juce::Colours::greenyellow);
        g.drawRect(position * getWidth(), 0, getWidth() / 30, getHeight());
    } else {
        g.setFont(20.0f);
        g.drawText("File need to load...", getLocalBounds(),
            juce::Justification::centred, true);   // draw some placeholder text
    }

    
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void WaveformDisplay::loadURL(juce::URL audioURL) {
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster* source) {
    repaint();
}

void WaveformDisplay::setPositionRelative(double pos) {
    if (pos != position) {
        position = pos;
        repaint();
    }
    
}


