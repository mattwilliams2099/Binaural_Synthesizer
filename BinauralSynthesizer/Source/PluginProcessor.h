/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "BinauralSynth.h"

//==============================================================================
/**
*/
class BinauralSynthesizerAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    BinauralSynthesizerAudioProcessor();
    ~BinauralSynthesizerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    //BinauralClass binaural;
    BinauralSynthClass synthesizer;
    juce::AudioProcessorValueTreeState parameters;
    //std::atomic<float>* azimuthParameter = nullptr;
    //std::atomic<float>* elevationParameter = nullptr;
    //std::atomic<float>* distanceParameter = nullptr;

    std::atomic<float>* osc1_azimuthParameter = nullptr;
    std::atomic<float>* osc1_elevationParameter = nullptr;
    std::atomic<float>* osc1_distanceParameter = nullptr;

    std::atomic<float>* osc2_azimuthParameter = nullptr;
    std::atomic<float>* osc2_elevationParameter = nullptr;
    std::atomic<float>* osc2_distanceParameter = nullptr;

    std::atomic<float>* osc3_azimuthParameter = nullptr;
    std::atomic<float>* osc3_elevationParameter = nullptr;
    std::atomic<float>* osc3_distanceParameter = nullptr;

    std::atomic<float>* osc1_octaveParameter = nullptr;
    std::atomic<float>* osc1_fineParameter = nullptr;
    std::atomic<float>* osc1_shapeParameter = nullptr;
    std::atomic<float>* osc1_mixParameter = nullptr;

    std::atomic<float>* osc2_octaveParameter = nullptr;
    std::atomic<float>* osc2_fineParameter = nullptr;
    std::atomic<float>* osc2_shapeParameter = nullptr;
    std::atomic<float>* osc2_mixParameter = nullptr;

    std::atomic<float>* osc3_octaveParameter = nullptr;
    std::atomic<float>* osc3_fineParameter = nullptr;
    std::atomic<float>* osc3_shapeParameter = nullptr;
    std::atomic<float>* osc3_mixParameter = nullptr;

    std::atomic<float>* attackParameter = nullptr;
    std::atomic<float>* decayParameter = nullptr;
    std::atomic<float>* sustainParameter = nullptr;
    std::atomic<float>* releaseParameter = nullptr;

    std::atomic<float>* filterCutoffParameter = nullptr;
    std::atomic<float>* filterResonanceParameter = nullptr;
    std::atomic<float>* filterEGAmtParameter = nullptr;

    std::atomic<float>* LFO1_freqParameter = nullptr;
    std::atomic<float>* LFO2_freqParameter = nullptr;
    std::atomic<float>* LFO3_freqParameter = nullptr;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BinauralSynthesizerAudioProcessor)


};
