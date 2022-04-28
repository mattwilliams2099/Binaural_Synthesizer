/*
  ==============================================================================

    Voice.h
    Created: 12 Apr 2022 2:12:07pm
    Author:  Matthew Williams

  ==============================================================================
*/

#pragma once
#include "Oscillator.h"
#include "ADSR.h"
#include "Filter.h"
#include "Binaural.h"

#define NUM_OSCILLATORS 3
class VoiceClass
{

public:
    BinauralClass binaural;
    VoiceClass(float samplerate);
    VoiceClass() = default;
    float voiceProcess(int channel);
    void newNote(int midiNote);
    void noteRelease();
    bool isPlaying();
    void setSampleRate(float newValue);
    void prepareToPlay();

    void setOscShape(int newValue, int oscNumber) 
    { 
        oscillator[0][oscNumber].setWaveShape(static_cast<OscillatorClass::shape>(newValue)); 
        oscillator[1][oscNumber].setWaveShape(static_cast<OscillatorClass::shape>(newValue));
    }
    
    void setOscFine(float newValue, int oscNumber) 
    { 
        oscillator[0][oscNumber].setFineFreq(newValue); 
        oscillator[1][oscNumber].setFineFreq(newValue);
    }

    void setOscOct(int newValue, int oscNumber)
    { 
        oscillator[0][oscNumber].setOctave(newValue);
        oscillator[1][oscNumber].setOctave(newValue);
    }

    void setFilter(float newCutoff, float newResonance) { LPF.setLowPassCo(newCutoff, newResonance); }

    void setAmpAttack(int newValue) 
    { 
        ampEnvelope[0].setAttack(newValue); 
        ampEnvelope[1].setAttack(newValue);
    }

    void setAmpDecay(int newValue) 
    { 
        ampEnvelope[0].setDecay(newValue); 
        ampEnvelope[1].setDecay(newValue);
    }

    void setAmpSustain(float newValue) 
    {   
        ampEnvelope[0].setSustain(newValue); 
        ampEnvelope[1].setSustain(newValue); 
    }
    
    void setAmpRelease(int newValue) 
    { 
        ampEnvelope[0].setRelease(newValue); 
        ampEnvelope[1].setRelease(newValue);
    }

    void setOscMix(float newOscMixAmt, int osc)
    {
        oscMix[osc] = newOscMixAmt;
    }

private:
    OscillatorClass oscillator[2][NUM_OSCILLATORS]{ sampleRate };
    ADSRClass ampEnvelope[2]{ sampleRate };
    FilterClass LPF{ sampleRate };
    float midiNoteToHz(int midiNote);
    float sampleRate;
    float oscMix[NUM_OSCILLATORS];

};
