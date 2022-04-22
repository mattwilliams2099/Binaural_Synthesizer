/*
  ==============================================================================

    Binaural.h
    Created: 21 Apr 2022 3:49:36pm
    Author:  Matthew Williams

  ==============================================================================
*/

#pragma once
#include "ILD.h"
#include "ITD.h"
class BinauralClass
{
private:
    ILDClass ILD { sampleRate };
    ITDClass ITD { sampleRate };
    float azimuth;
    float elevation;
    float distance;
    float sampleRate;
public:
    BinauralClass(float samplerate = 48000.0f) : sampleRate(samplerate) {};
    float process(float sample, int channel);
    void setAzimuth(int newAzimuth);
    void setElevation(float newElevation);
    void setDistance(float newDistance);
};