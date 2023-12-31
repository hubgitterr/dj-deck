/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include <iostream>

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize(800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired(juce::RuntimePermissions::recordAudio)
        && !juce::RuntimePermissions::isGranted(juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
                                    [&](bool granted) { setAudioChannels(granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels(0, 2);
    }

    /*playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    volSlider.setRange(0.0, 1.0);
    posSlider.setRange(0.0, 1.0);*/

    //adds and makes the 2 deckGUIs visible on top
    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);

    //adds the playlist compoment at the bottom
    addAndMakeVisible(playlistComponent);

    //registers basic formats for the audio files
    formatManager.registerBasicFormats();

    // here are my parts of code
    //Timer loops every 500ms, checks whether user added an audio file from playlist into a deckGUI
    startTimer(500);
    
}
 
MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}


//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()

    //ugasio
    //phase = 0.0;
    //dphase = 0.0001;

    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);

}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)

    //transportSource.getNextAudioBlock(bufferToFill);
    //resampleSource.getNextAudioBlock(bufferToFill);
    
    mixerSource.getNextAudioBlock(bufferToFill);
}


void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    player1.releaseResources();
    player2.releaseResources();
    mixerSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // here are my parts of code
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::lightyellow);
    /*g.setColour(juce::Colours::lightyellow);
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour(juce::Colours::lightyellow);*/

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    
    deckGUI1.setBounds(0, 0, getWidth() / 2, getHeight()/2);
    deckGUI2.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight()/2);
    playlistComponent.setBounds(0, getHeight()/2, getWidth(), getHeight() / 2);

    // DBG("This is a test . resized.");
}


void MainComponent::buttonClicked(juce::Button* button) {

}

void MainComponent::sliderValueChanged(juce::Slider* slider) {

}

//Function loops every 500ms, checks whether user has loaded a playlist audio file into a deckGUI
void MainComponent::timerCallback() { 

    // here are my parts of code
    std::ifstream file("playlist.txt"); //Opens playlist.txt
    std::string str;
    std::vector<std::string> lines;
    while (std::getline(file, str)) //Reads the lines in playlist.txt
    {
        lines.push_back(str);
    }
    //If the user added a song from playlist into deckGUI playlist.txt will contain the audio file URL and a number indicating which deckGUI the user selected
    if (std::stoi(lines[1]) == 1) { //If user selects deck 1, line 2 will show 1
        deckGUI1.playlistToDeckGUI(); //plays audio file in deckGUI1
        std::ofstream myfile("playlist.txt");
        myfile << "" << std::endl << "0" << std::endl; //Changes line 2 from "1" to "0" which resets playlist.txt file and stops the timer from looping endlessly
        myfile.close(); //closes file
    }
    else if (std::stoi(lines[1]) == 2) { //If user selects deck 2, line 2 will show 2
        deckGUI2.playlistToDeckGUI(); //plays audio file in deckGUI2
        std::ofstream myfile("playlist.txt");
        myfile << "" << std::endl << "0" << std::endl; //Changes line 2 from "2" to "0" which resets playlist.txt file and stops the timer from looping endlessly
        myfile.close(); //closes file
    }
    
}







