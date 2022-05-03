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

    for (int i = 0; i < 3; i++)
    {
        setSlider(osc_octaveSlider[i], juce::Colours::whitesmoke, juce::Slider::SliderStyle::LinearVertical);
        setSlider(osc_fineSlider[i], juce::Colours::whitesmoke, juce::Slider::SliderStyle::LinearVertical);
        setSlider(osc_shapeSlider[i], juce::Colours::whitesmoke, juce::Slider::SliderStyle::LinearVertical);
        setSlider(osc_mixSlider[i], juce::Colours::whitesmoke, juce::Slider::SliderStyle::LinearVertical);

        setSlider(azimuthSlider[i], juce::Colours::whitesmoke, juce::Slider::SliderStyle::LinearVertical);
        setSlider(elevationSlider[i], juce::Colours::whitesmoke, juce::Slider::SliderStyle::LinearVertical);
        setSlider(distanceSlider[i], juce::Colours::whitesmoke, juce::Slider::SliderStyle::LinearVertical);
        
        setSlider(LFO_freqSlider[i], juce::Colours::whitesmoke, juce::Slider::SliderStyle::LinearVertical);
        setSlider(LFO_amtSlider[i], juce::Colours::whitesmoke, juce::Slider::SliderStyle::LinearVertical);

        addAndMakeVisible(staticAzimuthLFOButton[i]);
        staticAzimuthLFOButton[i].setButtonText("Static LFO Range");
        staticAzimuthLFOButton[i].addListener(this);
    }

    setSlider(attackSlider, juce::Colours::whitesmoke, juce::Slider::SliderStyle::LinearVertical);
    setSlider(decaySlider, juce::Colours::whitesmoke, juce::Slider::SliderStyle::LinearVertical);
    setSlider(sustainSlider, juce::Colours::whitesmoke, juce::Slider::SliderStyle::LinearVertical);
    setSlider(releaseSlider, juce::Colours::whitesmoke, juce::Slider::SliderStyle::LinearVertical);

    setSlider(filterCutoffSlider, juce::Colours::whitesmoke, juce::Slider::SliderStyle::LinearVertical);
    setSlider(filterResonanceSlider, juce::Colours::whitesmoke, juce::Slider::SliderStyle::LinearVertical);
    setSlider(filterEGAmtSlider, juce::Colours::whitesmoke, juce::Slider::SliderStyle::LinearVertical);


    addAndMakeVisible(oscMenu);
    oscMenu.addItemList({ "1", "2", "3" }, 1);
    oscMenu.addListener(this);
    oscMenu.setSelectedItemIndex(0, 1);
    oscMenu.setColour(juce::ComboBox::backgroundColourId, juce::Colours::white);
    oscMenu.setColour(juce::ComboBox::textColourId, juce::Colours::blue);
    oscMenu.setColour(juce::ComboBox::arrowColourId, juce::Colours::blue);
    oscMenu.setColour(juce::ComboBox::outlineColourId, juce::Colours::blue);


    osc1_azimuthSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC1_AZ", azimuthSlider[0]);
    osc1_elevationSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC1_EL", elevationSlider[0]);
    osc1_distanceSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC1_DIST", distanceSlider[0]);

    osc2_azimuthSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC2_AZ", azimuthSlider[1]);
    osc2_elevationSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC2_EL", elevationSlider[1]);
    osc2_distanceSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC2_DIST", distanceSlider[1]);

    osc3_azimuthSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC3_AZ", azimuthSlider[2]);
    osc3_elevationSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC3_EL", elevationSlider[2]);
    osc3_distanceSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "OSC3_DIST", distanceSlider[2]);

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

    filterCutoffSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "CUTOFF", filterCutoffSlider);
    filterResonanceSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "RESONANCE", filterResonanceSlider);
    filterEGAmtSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "FILTER_ENV", filterEGAmtSlider);

    LFO1_freqSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "LFO1_FREQ", LFO_freqSlider[0]);
    LFO2_freqSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "LFO2_FREQ", LFO_freqSlider[1]);
    LFO3_freqSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "LFO3_FREQ", LFO_freqSlider[2]);

    LFO1_amtSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "LFO1_AMT", LFO_amtSlider[0]);
    LFO2_amtSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "LFO2_AMT", LFO_amtSlider[1]);
    LFO3_amtSliderAttachment = std::make_unique<SliderAttachment>(valueTreeState, "LFO3_AMT", LFO_amtSlider[2]);



    osc1_staticAzimuthLFOButtonAttachment = std::make_unique<ButtonAttachment>(valueTreeState, "OSC1_AZ_LOCK", staticAzimuthLFOButton[0]);
    osc2_staticAzimuthLFOButtonAttachment = std::make_unique<ButtonAttachment>(valueTreeState, "OSC2_AZ_LOCK", staticAzimuthLFOButton[1]);
    osc3_staticAzimuthLFOButtonAttachment = std::make_unique<ButtonAttachment>(valueTreeState, "OSC3_AZ_LOCK", staticAzimuthLFOButton[2]);



    
    filterCutoffSlider.setRange(20, 20000, 1);
    filterCutoffSlider.setSkewFactor(0.3);

    filterEGAmtSlider.setRange(20, 10000, 1);
    filterEGAmtSlider.setSkewFactor(0.3);



    setSize (480, 400);


}

BinauralSynthesizerAudioProcessorEditor::~BinauralSynthesizerAudioProcessorEditor()
{
}

//==============================================================================
void BinauralSynthesizerAudioProcessorEditor::paint (juce::Graphics& g)
{

    g.setColour (juce::Colours::blue);
    g.fillAll();
}

void BinauralSynthesizerAudioProcessorEditor::resized()
{


    for (int i = 0; i < 3; i++)
    {
        osc_octaveSlider[i].setBounds(120, 20, 30, 150);
        osc_fineSlider[i].setBounds(150, 20, 30, 150);
        osc_shapeSlider[i].setBounds(180, 20, 30, 150);
        osc_mixSlider[i].setBounds(210, 20, 30, 150);

        azimuthSlider[i].setBounds(20, 20, 30, 150);
        elevationSlider[i].setBounds(50, 20, 30, 150);
        distanceSlider[i].setBounds(80, 20, 30, 150);

        LFO_freqSlider[i].setBounds(20, 190, 30, 150);
        LFO_amtSlider[i].setBounds(130, 190, 30, 150);

        staticAzimuthLFOButton[i].setBounds(50, 190, 80, 30);
    }

    attackSlider.setBounds(250, 20, 30, 150);
    decaySlider.setBounds(280, 20, 30, 150);
    sustainSlider.setBounds(310, 20, 30, 150);
    releaseSlider.setBounds(340, 20, 30, 150);

    filterCutoffSlider.setBounds(380, 20, 30, 150);
    filterResonanceSlider.setBounds(410, 20, 30, 150);
    filterEGAmtSlider.setBounds(440, 20, 30, 150);

    oscMenu.setBounds(10, 10, 50, 20);

    for (int i = 1; i < 3; i++)
    {
        osc_octaveSlider[i].setVisible(false);
        osc_fineSlider[i].setVisible(false);
        osc_shapeSlider[i].setVisible(false);
        osc_mixSlider[i].setVisible(false);

        azimuthSlider[i].setVisible(false);
        elevationSlider[i].setVisible(false);
        distanceSlider[i].setVisible(false);

        LFO_freqSlider[i].setVisible(false);
        LFO_amtSlider[i].setVisible(false);

        staticAzimuthLFOButton[i].setVisible(false);
    }
}

void BinauralSynthesizerAudioProcessorEditor::setSlider(juce::Slider& slider, juce::Colour colour, juce::Slider::SliderStyle style)
{
    addAndMakeVisible(slider);
    slider.setSliderStyle(style);
    //slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 10);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 10);

    slider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
    slider.setColour(juce::Slider::thumbColourId, colour);
    slider.setColour(juce::Slider::backgroundColourId, juce::Colours::white);
    slider.setColour(juce::Slider::trackColourId, juce::Colours::white);
}

void BinauralSynthesizerAudioProcessorEditor::comboBoxChanged(juce::ComboBox* comboBox)
{
    for(int i = 0; i < 3; i++)
    {
        osc_octaveSlider[i].setVisible(false);
        osc_fineSlider[i].setVisible(false);
        osc_shapeSlider[i].setVisible(false);
        osc_mixSlider[i].setVisible(false);   

        azimuthSlider[i].setVisible(false);
        elevationSlider[i].setVisible(false);
        distanceSlider[i].setVisible(false);

        LFO_freqSlider[i].setVisible(false);
        LFO_amtSlider[i].setVisible(false);

        staticAzimuthLFOButton[i].setVisible(false);

    }
    
    int itemIndex = oscMenu.getSelectedItemIndex();
    osc_octaveSlider[itemIndex].setVisible(true);
    osc_fineSlider[itemIndex].setVisible(true);
    osc_shapeSlider[itemIndex].setVisible(true);
    osc_mixSlider[itemIndex].setVisible(true);
    azimuthSlider[itemIndex].setVisible(true);
    elevationSlider[itemIndex].setVisible(true);
    distanceSlider[itemIndex].setVisible(true);
    LFO_freqSlider[itemIndex].setVisible(true);
    staticAzimuthLFOButton[itemIndex].getToggleState() == true ? LFO_amtSlider[itemIndex].setVisible(true) : LFO_amtSlider[itemIndex].setVisible(false);
    staticAzimuthLFOButton[itemIndex].setVisible(true);


}


void BinauralSynthesizerAudioProcessorEditor::buttonStateChanged(juce::Button* button)
{

}

void BinauralSynthesizerAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    for (int i = 0; i < 3; i++)
    {
        if (button == &staticAzimuthLFOButton[i] && staticAzimuthLFOButton[i].getToggleState() == true)
        {
            LFO_amtSlider[i].setVisible(true);
            break;
        }
        else if (button == &staticAzimuthLFOButton[i] && staticAzimuthLFOButton[i].getToggleState() == false)
        {
            LFO_amtSlider[i].setValue(359);
            LFO_amtSlider[i].setVisible(false);
            break;
        }
    }
}
