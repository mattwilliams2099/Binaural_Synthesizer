/*
  ==============================================================================

    Voice.cpp
    Created: 12 Apr 2022 2:12:07pm
    Author:  Matthew Williams

  ==============================================================================
*/

#include "Voice.h"

VoiceClass::VoiceClass(float samplerate) : sampleRate(samplerate)
{
    //sampleRate = samplerate;

}

float VoiceClass::voiceProcess(int channel)
{
    float oscOutput = 0;
    for (int i = 0; i < NUM_OSCILLATORS; i++)
    {
        oscOutput += oscillator[channel][i].oscillatorProcess()* oscMix[i];
    }
    //float filterOutput = LPF.filterProcess((oscOutput * 0.3), channel);
    float ampOutput = oscOutput * ampEnvelope[channel].ADSRProcess();
    float binauralOutput = binaural.process(ampOutput, channel);
    return binauralOutput;
}

void VoiceClass::newNote(int midiNote)
{
    auto frequencyHz = midiNoteToHz(midiNote);
    for (int channel = 0; channel < 2; channel++)
    {
        for (int osc = 0; osc < NUM_OSCILLATORS; osc++)
        {
            oscillator[channel][osc].setFrequency(frequencyHz);
        }
        ampEnvelope[channel].keyDown();
    }
    //oscillator[0].setFrequency(frequencyHz);
    //oscillator[1].setFrequency(frequencyHz);
    //oscillator[2].setFrequency(frequencyHz);
    //ampEnvelope.keyDown();
}

float VoiceClass::midiNoteToHz(int midiNote)
{
    return 400.0f * std::powf(2.0f, (midiNote - 69.0f) / 12.0f);
}

void VoiceClass::noteRelease()
{
    ampEnvelope[0].keyUp();
    ampEnvelope[1].keyUp();

    /*
    for (int channel = 0; channel < 2; channel++)
    {
        for (int osc = 0; osc < NUM_OSCILLATORS; osc++)
        {
            oscillator[channel][osc].stop();
        }
    }
    */
}

bool VoiceClass::isPlaying()
{
    //return oscillator[0][0].isPlaying();
    return ampEnvelope[0].isActive();
}

void VoiceClass::prepareToPlay()
{

}

void VoiceClass::setSampleRate(float newValue)
{
    sampleRate = newValue;
    for (int channel = 0; channel < 2; channel++)
    {
        for (int osc = 0; osc < NUM_OSCILLATORS; osc++)
        {
            oscillator[channel][osc].setSampleRate(sampleRate);
        }
        ampEnvelope[channel].setSampleRate(sampleRate);
    }
    //oscillator[0].setSampleRate(sampleRate);
    //oscillator[1].setSampleRate(sampleRate);
    //oscillator[2].setSampleRate(sampleRate);
    LPF.setSampleRate(sampleRate);
}


