/*
  ==============================================================================

    Binaural.cpp
    Created: 21 Apr 2022 3:49:36pm
    Author:  Matthew Williams

  ==============================================================================
*/

#include "Binaural.h"

float BinauralClass::process(float sample, int channel)
{
    auto delayedSample = ITD.process(sample, channel);
    return ILD.process(delayedSample, channel);
}

void BinauralClass::setAzimuth(int newAzimuth)
{
    newAzimuth += 180;
    ILD.setAzimuth(newAzimuth);
    ITD.setAzimuth(static_cast<float>(newAzimuth));
}