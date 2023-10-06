/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 6 Sep 2023 5:31:10pm
    Author:  Hrc

  ==============================================================================
*/
// here are my parts of code
#include <JuceHeader.h>
#include <string>
#include "PlaylistComponent.h"
#include <time.h>
 
//==============================================================================

PlaylistComponent::PlaylistComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    //trackTitles.push_back("Track 1");
    //trackTitles.push_back("Track 2");
    //trackTitles.push_back("Track 3");
    //trackTitles.push_back("Track 4");
    //trackTitles.push_back("Track 5");
    //trackTitles.push_back("Track 6");
    //trackTitles.push_back("Track 7");
    //trackTitles.push_back("Track 8");
    
    // here are my parts of code
    //creates columns for the playlist component
    tableComponent.getHeader().addColumn("Track title", 1, 300);
    tableComponent.getHeader().addColumn("Duration(hhmmss)", 2, 100);
    tableComponent.getHeader().addColumn("Load into", 3, 150);
    tableComponent.getHeader().addColumn("Load into", 4, 150);
    //adding and making visible for the playlist table component, buttons and search input. Also adding listeners for buttons and search input
    tableComponent.setModel(this);
    // here are my parts of code
    addAndMakeVisible(tableComponent);
    addAndMakeVisible(libraryLoadButton);
    addAndMakeVisible(librarySearch);
    libraryLoadButton.addListener(this);
    formatManager.registerBasicFormats();
    librarySearch.addListener(this);
    // here are my parts of code
    //creates a text file named playlist.txt and inserts a placeholder "0" as to which deckGUI to be put into. This is for loading playlist files into either deck 1 or 2
    std::ofstream myfile("playlist.txt");
    myfile << stdstring << std::endl << "0" << std::endl;
    myfile.close();

    //creats a text file named PlaylistHistory.txt, which stores the current playlist audio file URLs so that the playlist data persists when reopening
    std::ifstream file("PlaylistHistory.txt");
    std::string str;
    std::vector<std::string> lines;
    while (std::getline(file, str))
    {
        lines.push_back(str);
    }
    // here are my parts of code
    //If text file contains audio file URLs, add each line into existing files array
    for (int i = 0; i < lines.size(); ++i) {
        existingFiles.push_back(lines[i]);
    }

    //If there are existing files before
    if (existingFiles.size() != 0) {

        //adds existing files into my files
        for (int i = 0; i < existingFiles.size(); ++i) {
            myFiles.add(juce::File{ existingFiles[i] });

        }

        for (int i = 0; i < myFiles.size(); ++i) { //for every file, get the file name and duration and prepares them for reading

            fileName = juce::URL::removeEscapeChars(juce::URL{ myFiles[i] }.getFileName()); //gets file name
            fileNames.add(fileName); //adds file name into filenames array, to be displayed in playlist table component
            juce::AudioFormatReader* reader = formatManager.createReaderFor(myFiles[i]); //creates reader for each file
            duration = reader->lengthInSamples / reader->sampleRate; //gets duration of the file by dividing length by sample rate
            myFilesDuration.add(duration); //adds duration into duration array to be displayed in playlist table component

        }
        tableComponent.updateContent(); //updates the table component to display the file names and duration
    }


}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    // here are my parts of code
    g.fillAll (juce::Colours::darkorange);   // clear the background

    g.setColour (juce::Colours::darkorange);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::red);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text

}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    //tableComponent.setBounds(0, 0, getWidth(), getHeight());
    double rowH = getHeight() / 7;
    libraryLoadButton.setBounds(0, 0, getWidth() / 2, rowH);
    librarySearch.setBounds(getWidth() / 2, 0, getWidth() / 2, rowH);
    tableComponent.setBounds(0, rowH, getWidth(), getHeight());
    // here are my parts of code
    //playlist header columns
    tableComponent.getHeader().setColumnWidth(1, (getWidth() / 8) * 3);
    tableComponent.getHeader().setColumnWidth(2, getWidth() / 8);
    tableComponent.getHeader().setColumnWidth(3, (getWidth() / 8) * 2);
    tableComponent.getHeader().setColumnWidth(4, (getWidth() / 8) * 2);
    
    tableComponent.setColour(juce::ListBox::backgroundColourId, juce::Colours::darkorange);
    // here are my parts of code
    //search bar
    librarySearch.setTextToShowWhenEmpty("Search for tracks...", juce::Colours::orange);
    librarySearch.setFont(20.0f);


    
}

int PlaylistComponent::getNumRows() { //get number of rows in playlist by getting the size of the file names
    return fileNames.size();
}

void PlaylistComponent::paintRowBackground(juce::Graphics& g,
                    int rowNumber,
                    int width,
                    int height,
                    bool rowIsSelected) {
        if (rowIsSelected) {
            g.fillAll(juce::Colours::mediumvioletred);
        } else {
            g.fillAll(juce::Colours::orangered);
        }
}

void PlaylistComponent::paintCell(juce::Graphics& g,
                    int rowNumber,
                    int columnId,
                    int width,
                    int height,
                    bool rowIsSelected) {

        if (columnId == 1) {//column 1 shows the file name of the audio file
            g.drawText(fileNames[rowNumber], 
                2, 0,
                width - 4, height,
                juce::Justification::centredLeft,
                true);
        }
        // here are my parts of code
        if (columnId == 2) {// column 2 shows the file's duration, in the format of hh:mm:ss
            std::time_t seconds(myFilesDuration[rowNumber]);
            tm* p = gmtime(&seconds);
            std::string hhmmss;
            std::string hours;
            std::string mins;
            std::string secs;
            //converting file duration from double into seconds and then into hours, minutes and seconds
            if (p->tm_hour < 10) {
                hours = "0" + std::to_string(p->tm_hour);
            }
            else {
                hours = std::to_string(p->tm_hour);
            }
            if (p->tm_min < 10) {
                mins = "0" + std::to_string(p->tm_min);
            }
            else {
                mins = std::to_string(p->tm_min);
            }
            if (p->tm_sec < 10) {
                secs = "0" + std::to_string(p->tm_sec);
            }
            else {
                secs = std::to_string(p->tm_sec);
            }

            hhmmss = hours + ":" + mins + ":" + secs;
            g.drawText(hhmmss,
                2, 0,
                width - 4, height,
                juce::Justification::centredLeft,
                true);
        }

}

juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
                            int columnId,
                            bool isRowSelected,
                            Component* existingComponentToUpdate) 
{
    // here are my parts of code
    if (columnId == 3) {//column 3 is a button that loads the audio file into deck 1
        if (existingComponentToUpdate == nullptr) {
            juce::TextButton* btn = new juce::TextButton{ "Player 1" }; //creates button with deck 1 as the text
            juce::String id{ std::to_string(rowNumber) };
            btn->setComponentID(id); //set component id to button for identifying which button was clicked
            btn->addListener(this); //adding listener to the button
            existingComponentToUpdate = btn;
            btn->onClick = [this] {loadFileIntoDeck1(); }; //loadFileIntoDeck1() runs when button is clicked
        }
    }
    if (columnId == 4) {//column 4 is a button that loads the audio file into deck 2
        if (existingComponentToUpdate == nullptr) {
            juce::TextButton* btn = new juce::TextButton{ "Player 2" }; //creates button with deck 2 as the text
            juce::String id{ std::to_string(rowNumber) };
            btn->setComponentID(id);
            btn->addListener(this); 
            existingComponentToUpdate = btn;
            btn->onClick = [this] {loadFileIntoDeck2(); }; //loadFileIntoDeck2() runs when button is clicked
        }
    }
    

    
    return existingComponentToUpdate;
    
}


void PlaylistComponent::buttonClicked(juce::Button* button) 
{
    // here are my parts of code
    if (button == &libraryLoadButton) {//If button is clicked and matchs the library load button
        //lets the user choose for one or multiple files at once
        juce::FileChooser choosers{ "Select for file(s) to add to the library...", juce::File() , "*.mp3;*.wav;*.aiff" }; 

        if (choosers.browseForMultipleFilesToOpen()) {
            myFiles = choosers.getResults(); //myFiles is an array of files
            for (int i = 0; i < myFiles.size(); ++i) { //for loop repeats for myFiles size

                if (existingFiles.size() != 0 || i == 0) { //if there are existing files, or it is the first iteration of the loop
                    for (int j = 0; j < existingFiles.size(); ++j) { //loops through number of times based on how many existing files there is
                        if (myFiles[i].getFullPathName().toStdString() == existingFiles[j]) { //loops through the existing files, if any matches, do not add the index
                            DBG("There are duplicates");

                            //creates alert window alerting user they have added a duplicate file, and it will not be added
                            juce::AlertWindow alertDuplicate("Duplicate file added", "Duplicated file " + juce::URL::removeEscapeChars(juce::URL{ myFiles[i] }.getFileName()) + " has not been added", juce::MessageBoxIconType::InfoIcon);
                            alertDuplicate.addButton("Continue",0);
                            alertDuplicate.setUsingNativeTitleBar(true);

                            int result = alertDuplicate.runModalLoop();

                            duplicateIndex = i; //taking note of which file index is a duplicated
                            break;
                        } 
                    }
                    if (i != duplicateIndex) { //If the file is not a duplicated file index, add the file
                        fileName = juce::URL::removeEscapeChars(juce::URL{ myFiles[i] }.getFileName()); //get the file name and adds them to the fileNames array for display
                        fileNames.add(fileName);
                        juce::AudioFormatReader* reader = formatManager.createReaderFor(myFiles[i]);
                        duration = reader->lengthInSamples / reader->sampleRate; //gets duration of the file by dividing the length in samples by the sample rate
                        myFilesDuration.add(duration); //adds duration into myFilesDuration, which is used in paint cell
                        DBG(fileNames[i]);
                        DBG(duration);

                        existingFiles.push_back(myFiles[i].getFullPathName().toStdString()); //file path is added to the existingFiles array

                    }
                    
                }              

            }


            std::ofstream history("PlaylistHistory.txt"); //Opens PlaylistHistory.txt file

            for (int i = 0; i < existingFiles.size(); ++i) { //For each file in existingFiles
                history << existingFiles[i] << std::endl; //Writes the added file path into the text file
            }
            history.close(); //closes the text file


            tableComponent.updateContent();


        }

    }
     
 

    rowclicked = button->getComponentID().getDoubleValue(); //gets which row(file) the user has clicked, used for deleting or adding files into deck 1/2


}

void PlaylistComponent::textEditorTextChanged(juce::TextEditor& editor) { //Search bar input
    
    searchInput = librarySearch.getText(); //Gets the text which the user has typed in the search bar

    for (int i = 0; i < fileNames.size(); ++i) {//Loops through all the files names of existing files
        if (fileNames[i].containsWholeWord(searchInput) && searchInput != "") { // Matches the user's search input with any of the file names
            tableComponent.selectRow(i, false, true); //Selects the row which has a match
        }
    }
    
}

// here are my parts of code
void PlaylistComponent::loadFileIntoDeck1() { //only runs when user clicks on "Deck 1" button on the file
    for (int i = 0; i < myFiles.size(); ++i) { //Loops through myFiles
        juce::AudioFormatReader* reader = formatManager.createReaderFor(myFiles[i]); //creates reader for the file
        if (rowclicked == i) { //Matches the row(file) which the user clicked to be added into Deck 1
            DBG("loadintodeck1");
            DBG(myFiles[i].getFileName());
            DBG(reader->getFormatName());
            fileToDeckGUI = myFiles[i].getFullPathName();//Gets the path of the file
            stdstring = fileToDeckGUI.toStdString();//Converts the path from juce string into std string
            std::replace(stdstring.begin(), stdstring.end(), '\\', '/');//Replaces all \ in path to /, as reading the path into a file requires back slash"/"
            DBG(stdstring);

            std::ofstream myfile("playlist.txt");//Opens text file named playlist.txt
            myfile << stdstring << std::endl << "1" << std::endl; //writes the path of the file, and "1" into the text file, indicating loading into deck 1
            myfile.close(); //closes the text file
        }
    }
}
// here are my parts of code
void PlaylistComponent::loadFileIntoDeck2() { //only runs when user clicks on "Deck 2" button on the file
    for (int i = 0; i < myFiles.size(); ++i) { 
        juce::AudioFormatReader* reader = formatManager.createReaderFor(myFiles[i]);
        if (rowclicked == i) {
            DBG("loadintodeck2");
            DBG(myFiles[i].getFileName());
            DBG(reader->getFormatName());
            fileToDeckGUI = myFiles[i].getFullPathName();
            stdstring = fileToDeckGUI.toStdString();
            std::replace(stdstring.begin(), stdstring.end(), '\\', '/');
            DBG(stdstring);
            std::ofstream myfile("playlist.txt");
            myfile << stdstring << std::endl << "2" << std::endl; //writes the path of the file, and "2" into the text file, indicating loading into deck 2
            myfile.close();

            
        }
    }
}






