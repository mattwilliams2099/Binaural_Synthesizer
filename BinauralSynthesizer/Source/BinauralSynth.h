
#pragma once
#include "JuceHeader.h"
#include "Voice.h"
#include "LFO.h"
#define NUM_VOICES 2
class BinauralSynthClass
{
private:
    LFOClass azimuthLFO[3];
    VoiceClass voices{ sampleRate };
    float sampleRate;
    void handleMidiEvent(const juce::MidiMessage& midiEvent);
    void render(juce::AudioBuffer<float>& buffer, int startSample, int endSample);
    int activeNoteID[NUM_VOICES] = { 0, 0 };
public:

    BinauralSynthClass(float samplerate);
    BinauralSynthClass() = default;
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);
    void prepareToPlay(double samplerate);

    void setAzimuth(int newValue, int oscNumber)
    {
        voices.setAzimuth(newValue, oscNumber);
    }

    void setLFOOffset(int newValue, int oscNumber)
    {
        azimuthLFO[oscNumber].setOffset(newValue);

    }
    void setElevation(int newValue, int oscNumber)
    {
        voices.setElevation(newValue, oscNumber);
    }

    void setDistance(float newValue, int oscNumber)
    {
        voices.setDistance(newValue, oscNumber);
    }

    void setOscShape(int newValue, int oscNumber)
    {
        //for(VoiceClass voice : voices)
        voices.setOscShape(newValue, oscNumber);
    }

    void setOscMix(float newOscMixAmt, int oscNumber)
    {
        voices.setOscMix(newOscMixAmt, oscNumber);
    }

    void setOscFineFreq(float newValue, int oscNumber)
    {
        voices.setOscFine(newValue, oscNumber);
    }

    void setOscOctave (float newValue, int oscNumber)
    {
        voices.setOscOct (newValue, oscNumber);
    }

    void setLFOFreq(float newValue, int oscNumber)
    {
        azimuthLFO[oscNumber].setFrequency(newValue);
    }

    void setLFOAmt(float newValue, int oscNumber)
    {
        azimuthLFO[oscNumber].setRange(newValue);
    }

    void setStaticLFO(bool isStatic, int oscNumber)
    {
        if (isStatic == true)
            azimuthLFO[oscNumber].setShape(LFOClass::triangle);
        else
            azimuthLFO[oscNumber].setShape(LFOClass::sawDown);
    }

    void setFilter (float newCutoff, float newResonance)
    {
        //for (VoiceClass voice : voices)
        voices.setFilter (newCutoff, newResonance);
    }

    void setAmpAttack (int newValue)
    {
        //for (VoiceClass voice : voices)
        voices.setAmpAttack (newValue);
    }

    void setAmpDecay (int newValue)
    {
        //for (VoiceClass voice : voices)
        voices.setAmpDecay (newValue);
    }

    void setAmpSustain (float newValue)
    {
        //for (VoiceClass voice : voices)
        voices.setAmpSustain (newValue);
    }

    void setAmpRelease (int newValue)
    {
        //for (VoiceClass voice : voices)
        voices.setAmpRelease (newValue);
    }

    void setFilterEGAmt (float newEnvAmt)
    {
        voices.setFilterEGAmt(newEnvAmt);
    }

};