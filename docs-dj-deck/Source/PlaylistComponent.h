/*
  ==============================================================================

    PlaylistComponent.h
    Created: 6 Sep 2023 5:31:10pm
    Author:  Hrc

  ==============================================================================
*/

#pragma once
// here are my parts of code
#include <JuceHeader.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream> 
#include <ostream>

 
//==============================================================================
/*
*/
// here are my parts of code
class PlaylistComponent  : public juce::Component,
                           public juce::TableListBoxModel,
                           public juce::Button::Listener,
                           public juce::TextEditor::Listener
{
public:
    PlaylistComponent();
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    int getNumRows() override;

    void paintRowBackground(juce::Graphics &,
                            int rowNumber,
                            int width,
                            int height,
                            bool rowIsSelected) override;

    void paintCell(juce::Graphics &,
                   int rowNumber,
                   int columnId,
                   int width,
                   int height,
                   bool rowIsSelected) override;

    Component* refreshComponentForCell(int rowNumber,
                                       int columnId,
                                       bool isRowSelected,
                                       Component* existingComponentToUpdate) override;
    void buttonClicked(juce::Button* button) override;
    void textEditorTextChanged(juce::TextEditor& editor) override;
    void loadFileIntoDeck1(); //Loads playlist files into the deckGUI component, indicating as deck 1
    void loadFileIntoDeck2(); //Loads playlist files into the deckGUI component, indicating as deck 2
    juce::String fileToDeckGUI;
    std::string stdstring;
    
    


private:
    // here are my parts of code
    juce::AudioFormatManager formatManager;
    juce::Array<juce::File> myFiles;
    std::vector <std::string > existingFiles;
    double duration;
    juce::String fileName;
    juce::Array<double> myFilesDuration;
    juce::Array<juce::String> fileNames;
    juce::TableListBox tableComponent;
    juce::TextButton libraryLoadButton{ "Load songs to library" };
    bool historyClicked = false;
    int duplicateIndex = -1;
    juce::TextButton libraryDeck1;
    juce::TextButton libraryDeck2;
    juce::TextEditor librarySearch{ "Search your track" };
    juce::String searchInput;
    
    double rowclicked;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
