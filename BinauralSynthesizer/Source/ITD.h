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
#include <iostream>
#include <fstream>
class ITDClass
{
private: 
    DelayLineClass delayLine;
    void setDelay();
    float distance;
    float distanceCoefficient[2];
    float sampleRate;
    float samplePeriod;
    void loadCoordinateDatabase();
    float coordinatesDatabase[2304][3];
    int index;

public:
    ITDClass(float sampleRate = 48000);
    float process(float sample, int channel);
    void setIndex(int newIndex);
    void setDistance(float newDistance);
};