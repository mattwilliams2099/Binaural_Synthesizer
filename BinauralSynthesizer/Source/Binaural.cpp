/*
  ==============================================================================

    Binaural.cpp
    Created: 21 Apr 2022 3:49:36pm
    Author:  Matthew Williams

  ==============================================================================
*/

#include "Binaural.h"

BinauralClass::BinauralClass(float samplerate)
    : sampleRate(samplerate) 
{
    setAzimuth(-45);
    setElevation(15);
    setDistance(1.0f);
}

float BinauralClass::process(float sample, int channel)
{
    count++;
    if (count == 5000)
    {
        incrementLFO();
        count = 0;
    }
    auto delayedSample = ITD.process(sample, channel);
    return ILD.process(delayedSample, channel);
    //return ILD.process(sample, channel);
    //return delayedSample;
}

void BinauralClass::setAzimuth(int newAzimuth)
{
    if (newAzimuth <= 0)
        azimuth = abs(newAzimuth);
    else
        azimuth = 360 - newAzimuth;
    ILD.setIndex(getCoordinates());
    ITD.setIndex(getCoordinates());
}

void BinauralClass::setElevation(int newElevation)
{
    elevation = newElevation;
    ILD.setIndex(getCoordinates());
    ITD.setIndex(getCoordinates());
}

void BinauralClass::setDistance(float newDistance)
{
    distance = newDistance;
    ITD.setDistance(distance);
}

int BinauralClass::getCoordinates()
{
    return (static_cast<int>(azimuth / 5) * 32) + elevation;
}

void BinauralClass::incrementLFO()
{
    LFO++;
    if (LFO == 179)
        LFO = -180;
    setAzimuth(LFO);
}
