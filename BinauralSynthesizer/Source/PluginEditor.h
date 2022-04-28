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
class BinauralSynthesizerAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                 public juce::ComboBox::Listener
{
public:
    BinauralSynthesizerAudioProcessorEditor (BinauralSynthesizerAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~BinauralSynthesizerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void comboBoxChanged(juce::ComboBox* comboBox) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BinauralSynthesizerAudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& valueTreeState;

    juce::Slider elevationSlider;
    juce::Slider azimuthSlider;
    juce::Slider distanceSlider;
    /*
    juce::Slider osc1_octaveSlider;
    juce::Slider osc1_fineSlider;
    juce::Slider osc1_shapeSlider;
    juce::Slider osc1_mixSlider;

    juce::Slider osc2_octaveSlider;
    juce::Slider osc2_fineSlider;
    juce::Slider osc2_shapeSlider;
    juce::Slider osc2_mixSlider;
    */
    juce::Slider osc_octaveSlider[3];
    juce::Slider osc_fineSlider[3];
    juce::Slider osc_shapeSlider[3];
    juce::Slider osc_mixSlider[3];

    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    juce::ComboBox oscMenu;

    std::unique_ptr<SliderAttachment> elevationSliderAttachment;
    std::unique_ptr<SliderAttachment> azimuthSliderAttachment;
    std::unique_ptr<SliderAttachment> distanceSliderAttachment;

    std::unique_ptr<SliderAttachment> osc1_octaveSliderAttachment;
    std::unique_ptr<SliderAttachment> osc1_fineSliderAttachment;
    std::unique_ptr<SliderAttachment> osc1_shapeSliderAttachment;
    std::unique_ptr<SliderAttachment> osc1_mixSliderAttachment;

    std::unique_ptr<SliderAttachment> osc2_octaveSliderAttachment;
    std::unique_ptr<SliderAttachment> osc2_fineSliderAttachment;
    std::unique_ptr<SliderAttachment> osc2_shapeSliderAttachment;
    std::unique_ptr<SliderAttachment> osc2_mixSliderAttachment;

    std::unique_ptr<SliderAttachment> osc3_octaveSliderAttachment;
    std::unique_ptr<SliderAttachment> osc3_fineSliderAttachment;
    std::unique_ptr<SliderAttachment> osc3_shapeSliderAttachment;
    std::unique_ptr<SliderAttachment> osc3_mixSliderAttachment;

    std::unique_ptr<SliderAttachment> attackSliderAttachment;
    std::unique_ptr<SliderAttachment> decaySliderAttachment;
    std::unique_ptr<SliderAttachment> sustainSliderAttachment;
    std::unique_ptr<SliderAttachment> releaseSliderAttachment;



    void setSlider(juce::Slider& slider, juce::Colour colour, juce::Slider::SliderStyle style);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BinauralSynthesizerAudioProcessorEditor)
};
