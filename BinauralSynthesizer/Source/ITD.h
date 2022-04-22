/*
  ==============================================================================

    ITD.h
    Created: 21 Apr 2022 3:50:00pm
    Author:  Matthew Williams

  ==============================================================================
*/

#pragma once
#define _USE_MATH_DEFINES
#include "DelayLine.h"
#include <cmath>
class ITDClass
{
private: 
    DelayLineClass delayLine;
    void setDelay(float az, float el, float dist);
    float azimuth;
    float elevation;
    float distance;
    float distanceCoefficient[2];
    float sampleRate;
    float samplePeriod;
public:
    ITDClass(float sampleRate = 48000);
    float process(float sample, int channel);

    void setAzimuth(float newAzimuth);
    void setElevation();
    void setDistance();
};