/*
  ==============================================================================

    ITD.cpp
    Created: 21 Apr 2022 3:50:00pm
    Author:  Matthew Williams

  ==============================================================================
*/

#include "ITD.h"

ITDClass::ITDClass(float samplerate) : sampleRate(samplerate)
{
    samplePeriod = 1.0f / sampleRate;
}

float ITDClass::process(float sample, int channel)
{
    return delayLine.delayProcess(sample, channel) * distanceCoefficient[channel];
}
/*
void ITDClass::setDelay(float az, float el, float dist)
{
    float distance_long = sqrt(pow(dist * cos(az), 2) + pow((abs(dist * sin(az)) + 0.075f), 2));
    float distance_short = sqrt(pow(dist * cos(az), 2) + pow((abs(dist * sin(az)) - 0.075f), 2));
    float delay_long = distance_long / 340.29f;
    float delay_short = distance_short / 340.29f;
    if (azimuth < M_PI)
    {
        //delayTime[0] = delay_short;
        delayLine.setDelayLength(round(delay_short / samplePeriod), 0);
        //delayTime[1] = delay_long;
        delayLine.setDelayLength(round(delay_long / samplePeriod), 1);
        distanceCoefficient[0] = pow((1 / distance_short), 2);
        distanceCoefficient[1] = pow((1 / distance_long), 2);
    }
    else
    {
        //delayTime[1] = delay_short;
        //delayTime[0] = delay_long;
        delayLine.setDelayLength(round(delay_short / samplePeriod), 1);
        delayLine.setDelayLength(round(delay_long / samplePeriod), 0);
        distanceCoefficient[0] = pow((1 / distance_long), 2);
        distanceCoefficient[1] = pow((1 / distance_short), 2);
    }
    //delayLine.setDelayLength(round(delayTime[0] / samplePeriod), 0);
    //delayLine.setDelayLength(round(delayTime[1] / samplePeriod), 1);
}*/

void ITDClass::setDelay()
{
    float distance_long = sqrt(pow((distance * coordinatesDatabase[index][0]) + 0.075, 2) + pow ((distance * coordinatesDatabase[index][1]), 2) + pow ((distance * coordinatesDatabase[index][2]), 2));
    float distance_short = sqrt(pow((distance * coordinatesDatabase[index][0]) - 0.075, 2) + pow((distance * coordinatesDatabase[index][1]), 2) + pow((distance * coordinatesDatabase[index][2]), 2));
    float delay_long = distance_long / 340.29f;
    float delay_short = distance_short / 340.29f;
    if (index < 1152)
    {
        delayLine.setDelayLength(round(delay_short / samplePeriod), 0);
        delayLine.setDelayLength(round(delay_long / samplePeriod), 1);
        distanceCoefficient[0] = pow((1 / distance_short), 2);
        distanceCoefficient[1] = pow((1 / distance_long), 2);
    }
    else
    {
        delayLine.setDelayLength(round(delay_short / samplePeriod), 1);
        delayLine.setDelayLength(round(delay_long / samplePeriod), 0);
        distanceCoefficient[0] = pow((1 / distance_long), 2);
        distanceCoefficient[1] = pow((1 / distance_short), 2);
    }
}

void ITDClass::loadCoordinateDatabase()
{
    std::ifstream coordinatesFile[3];
    coordinatesFile[0].open("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/x_coordinates.txt");
    coordinatesFile[1].open("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/y_coordinates.txt");
    coordinatesFile[2].open("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/z_coordinates.txt");

    for (int i = 0; i < 3; i++)
    {
        int n = 0;
        if (coordinatesFile[i].is_open())
        {
            while (coordinatesFile[i] >> coordinatesDatabase[n][i])
            {
                n++;
            }
            coordinatesFile[i].close();
        }
    }
   
}

void ITDClass::setIndex(int newIndex)
{
    index = newIndex;
    setDelay();
}

void ITDClass::setDistance(float newDistance)
{
    distance = newDistance;
    setDelay();
}