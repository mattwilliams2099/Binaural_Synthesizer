/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BinauralSynthesizerAudioProcessorEditor::BinauralSynthesizerAudioProcessorEditor (BinauralSynthesizerAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSlider(azimuthSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(elevationSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(distanceSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);


    azimuthSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "AZ", azimuthSlider);
    elevationSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "EL", elevationSlider);
    distanceSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "DIST", distanceSlider);



    setSize (400, 300);


}

BinauralSynthesizerAudioProcessorEditor::~BinauralSynthesizerAudioProcessorEditor()
{
}

//==============================================================================
void BinauralSynthesizerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)


    g.setColour (juce::Colours::white);
    g.fillAll();
}

void BinauralSynthesizerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    azimuthSlider.setBounds(20, 20, 30, 150);
    elevationSlider.setBounds(50, 20, 30, 150);
    distanceSlider.setBounds(80, 20, 30, 150);

}

void BinauralSynthesizerAudioProcessorEditor::setSlider(juce::Slider& slider, juce::Colour colour, juce::Slider::SliderStyle style)
{
    addAndMakeVisible(slider);
    slider.setSliderStyle(style);
    //slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 10);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 10);

    slider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
    slider.setColour(juce::Slider::thumbColourId, colour);
    slider.setColour(juce::Slider::backgroundColourId, juce::Colours::black);
    slider.setColour(juce::Slider::trackColourId, juce::Colours::black);
}