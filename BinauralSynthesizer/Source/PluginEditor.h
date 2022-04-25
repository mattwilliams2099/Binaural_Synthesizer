/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
class BinauralSynthesizerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    BinauralSynthesizerAudioProcessorEditor (BinauralSynthesizerAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~BinauralSynthesizerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BinauralSynthesizerAudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& valueTreeState;

    juce::Slider elevationSlider;
    juce::Slider azimuthSlider;
    juce::Slider distanceSlider;
    std::unique_ptr<SliderAttachment> elevationSliderAttachment;
    std::unique_ptr<SliderAttachment> azimuthSliderAttachment;
    std::unique_ptr<SliderAttachment> distanceSliderAttachment;

    void setSlider(juce::Slider& slider, juce::Colour colour, juce::Slider::SliderStyle style);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BinauralSynthesizerAudioProcessorEditor)
};
