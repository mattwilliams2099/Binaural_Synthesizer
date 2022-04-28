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
    /*
    setSlider(osc1_octaveSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(osc1_fineSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(osc1_shapeSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(osc1_mixSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);

    setSlider(osc2_octaveSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(osc2_fineSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(osc2_shapeSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(osc2_mixSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    */

    for (int i = 0; i < 3; i++)
    {
        setSlider(osc_octaveSlider[i], juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
        setSlider(osc_fineSlider[i], juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
        setSlider(osc_shapeSlider[i], juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
        setSlider(osc_mixSlider[i], juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    }

    setSlider(attackSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(decaySlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(sustainSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(releaseSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);

    addAndMakeVisible(oscMenu);
    oscMenu.addItemList({ "1", "2", "3" }, 1);
    oscMenu.addListener(this);
    oscMenu.setSelectedItemIndex(0, 1);

    azimuthSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "AZ", azimuthSlider);
    elevationSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "EL", elevationSlider);
    distanceSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "DIST", distanceSlider);
    /*
    osc1_octaveSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC1_OCT", osc1_octaveSlider);
    osc1_fineSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC1_FINE", osc1_fineSlider);
    osc1_shapeSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC1_SHP", osc1_shapeSlider);
    osc1_mixSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC1_MIX", osc1_mixSlider);

    osc2_octaveSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC2_OCT", osc2_octaveSlider);
    osc2_fineSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC2_FINE", osc2_fineSlider);
    osc2_shapeSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC2_SHP", osc2_shapeSlider);
    osc2_mixSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC2_MIX", osc2_mixSlider);
    */

    osc1_octaveSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC1_OCT", osc_octaveSlider[0]);
    osc1_fineSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC1_FINE", osc_fineSlider[0]);
    osc1_shapeSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC1_SHP", osc_shapeSlider[0]);
    osc1_mixSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC1_MIX", osc_mixSlider[0]);

    osc2_octaveSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC2_OCT", osc_octaveSlider[1]);
    osc2_fineSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC2_FINE", osc_fineSlider[1]);
    osc2_shapeSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC2_SHP", osc_shapeSlider[1]);
    osc2_mixSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC2_MIX", osc_mixSlider[1]);

    osc3_octaveSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC3_OCT", osc_octaveSlider[2]);
    osc3_fineSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC3_FINE", osc_fineSlider[2]);
    osc3_shapeSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC3_SHP", osc_shapeSlider[2]);
    osc3_mixSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC3_MIX", osc_mixSlider[2]);

    attackSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "ATTACK", attackSlider);
    decaySliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "DECAY", decaySlider);
    sustainSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "SUSTAIN", sustainSlider);
    releaseSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "RELEASE", releaseSlider);


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


    for (int i = 0; i < 3; i++)
    {
        osc_octaveSlider[i].setBounds(120, 20, 30, 150);
        osc_fineSlider[i].setBounds(150, 20, 30, 150);
        osc_shapeSlider[i].setBounds(180, 20, 30, 150);
        osc_mixSlider[i].setBounds(210, 20, 30, 150);
    }
    /*
    osc1_octaveSlider.setBounds(120, 20, 30, 150);
    osc1_fineSlider.setBounds(150, 20, 30, 150);
    osc1_shapeSlider.setBounds(180, 20, 30, 150);
    osc1_mixSlider.setBounds(210, 20, 30, 150);

    osc2_octaveSlider.setBounds(120, 20, 30, 150);
    osc2_fineSlider.setBounds(150, 20, 30, 150);
    osc2_shapeSlider.setBounds(180, 20, 30, 150);
    osc2_mixSlider.setBounds(210, 20, 30, 150);
    */
    attackSlider.setBounds(250, 20, 30, 150);
    decaySlider.setBounds(280, 20, 30, 150);
    sustainSlider.setBounds(310, 20, 30, 150);
    releaseSlider.setBounds(340, 20, 30, 150);

    oscMenu.setBounds(20, 20, 50, 20);


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

void BinauralSynthesizerAudioProcessorEditor::comboBoxChanged(juce::ComboBox* comboBox)
{
    for(int i = 0; i < 3; i++)
    {
        osc_octaveSlider[i].setVisible(false);
        osc_fineSlider[i].setVisible(false);
        osc_shapeSlider[i].setVisible(false);
        osc_mixSlider[i].setVisible(false);   
    }
    

    int itemIndex = oscMenu.getSelectedItemIndex();
    osc_octaveSlider[itemIndex].setVisible(true);
    osc_fineSlider[itemIndex].setVisible(true);
    osc_shapeSlider[itemIndex].setVisible(true);
    osc_mixSlider[itemIndex].setVisible(true);

}