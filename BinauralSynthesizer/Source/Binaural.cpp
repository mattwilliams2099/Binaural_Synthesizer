/*
  ==============================================================================

    Binaural.cpp
    Created: 21 Apr 2022 3:49:36pm
    Author:  Matthew Williams

  ==============================================================================
*/

#include "Binaural.h"

BinauralClass::BinauralClass(float samplerate = 48000.0f)
    : sampleRate(samplerate) 
{
}


float BinauralClass::process(float sample, int channel)
{
    auto delayedSample = ITD.process(sample, channel);
    return ILD.process(delayedSample, channel);
}

void BinauralClass::setAzimuth(int newAzimuth)
{
    azimuth = newAzimuth + 180;
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