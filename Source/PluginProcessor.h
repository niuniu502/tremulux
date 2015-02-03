/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"
const int numMods = 2;

//==============================================================================
/**
*/



class TremuluxAudioProcessor  : public AudioProcessor{
public:
    //==============================================================================
    TremuluxAudioProcessor();
    ~TremuluxAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    int getNumParameters() override;
    float getParameter (int index) override;
    void setParameter (int index, float newValue) override;

    const String getParameterName (int index) override;
    const String getParameterText (int index) override;

    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    typedef enum {
        MOD_RATE1 = 0,
        MOD_RATE_DIAL1,
        MOD_DEPTH1,
        MOD_SYNC_BUTTON1,
        MOD_SYNC1,
        
        MOD_RATE2,
        MOD_RATE_DIAL2,
        MOD_DEPTH2,
        MOD_SYNC_BUTTON2,
        MOD_SYNC2,
        
        MIX,
        NUM_PARAMS
    } PARAMS;
    
    typedef enum {
        OFF = 0,
        
        TWO_BARS,
        ONE_BAR,
        HALF,
        DOTTED_QUARTER,
        QUARTER,
        TRIPLET_QUARTER,
        DOTTED_EIGHTH,
        EIGHTH,
        TRIPLET_EIGHTH,
        DOTTED_SIXTEENTH,
        SIXTEENTH,
        TRIPLET_SIXTEENTH,
        
        NUM_SYNC_OPTIONS
    } SYNC_OPTIONS;

    const float freqDialRange = (NUM_SYNC_OPTIONS - 1) / 10.0;
    const float oneOverFreqDialRange = 1.0 / freqDialRange;
    const float minFreeRate = 0.1, maxFreeRate = 20.0;
    
private:
    float mix;

    unsigned int modInterp;
    float modRateDials[numMods];
    float modRateTargets[numMods];
    float modRates[numMods];
    void updateSyncedRates(const bool force = false);
    

    float calcSyncedRate(const int mode, const int modID);
    float calcRate(const float freqDialValue, const int modID);
    
    float modDepthTargets[numMods];

    Wavetable<float> sineTable;
    Oscillator<float> mods[numMods];
    
    AudioPlayHead *transport;
    juce::AudioPlayHead::CurrentPositionInfo transportInfo;


    float syncFactors[NUM_SYNC_OPTIONS];
    unsigned int modSyncButtons[numMods];
    SYNC_OPTIONS modSyncs[numMods];
    float lastBPM;
    unsigned int lastTimeSigDenominator, lastTimeSigNumerator;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TremuluxAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
