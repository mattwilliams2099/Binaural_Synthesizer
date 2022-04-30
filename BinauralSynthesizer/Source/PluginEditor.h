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

    juce::Slider elevationSlider[3];
    juce::Slider azimuthSlider[3];
    juce::Slider distanceSlider[3];
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

    juce::Slider LFO_freqSlider[3];

    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    juce::Slider filterCutoffSlider;
    juce::Slider filterResonanceSlider;
    juce::Slider filterEGAmtSlider;

    juce::ComboBox oscMenu;

    std::unique_ptr<SliderAttachment> osc1_elevationSliderAttachment;
    std::unique_ptr<SliderAttachment> osc1_azimuthSliderAttachment;
    std::unique_ptr<SliderAttachment> osc1_distanceSliderAttachment;

    std::unique_ptr<SliderAttachment> osc2_elevationSliderAttachment;
    std::unique_ptr<SliderAttachment> osc2_azimuthSliderAttachment;
    std::unique_ptr<SliderAttachment> osc2_distanceSliderAttachment;

    std::unique_ptr<SliderAttachment> osc3_elevationSliderAttachment;
    std::unique_ptr<SliderAttachment> osc3_azimuthSliderAttachment;
    std::unique_ptr<SliderAttachment> osc3_distanceSliderAttachment;

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

    std::unique_ptr<SliderAttachment> filterCutoffSliderAttachment;
    std::unique_ptr<SliderAttachment> filterResonanceSliderAttachment;
    std::unique_ptr<SliderAttachment> filterEGAmtSliderAttachment;

    std::unique_ptr<SliderAttachment> LFO1_freqSliderAttachment;
    std::unique_ptr<SliderAttachment> LFO2_freqSliderAttachment;
    std::unique_ptr<SliderAttachment> LFO3_freqSliderAttachment;

    void setSlider(juce::Slider& slider, juce::Colour colour, juce::Slider::SliderStyle style);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BinauralSynthesizerAudioProcessorEditor)
};
