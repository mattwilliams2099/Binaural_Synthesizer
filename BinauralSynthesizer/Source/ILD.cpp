/*
  ==============================================================================

    ILD.cpp
    Created: 21 Apr 2022 3:50:27pm
    Author:  Matthew Williams

  ==============================================================================
*/

#include "ILD.h"

ILDClass::ILDClass(float samplerate) : sampleRate(samplerate)
{
    loadAmplitudeDatabase();
}


float ILDClass::process(float sample, int channel)
{
    float output = 0.0f;
    for (int i = 0; i < 4; i++)
    {
        output += (bandPassFilter[i].filterProcess(sample, channel) * amplitudes[amplitudeIndex][i][channel]);
    }
    return(output);
}

void ILDClass::setAzimuth(int newAzimuth)
{

}





void ILDClass::loadAmplitudeDatabase()
{
    std::ifstream subAmplitudesLeftFile("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/subBandAmplitudes_left.txt");
    std::ifstream subAmplitudesRightFile("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/subBandAmplitudes_right.txt");
    std::ifstream lowAmplitudesLeftFile("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/lowBandAmplitudes_left.txt");
    std::ifstream lowAmplitudesRightFile("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/lowBandAmplitudes_right.txt");
    std::ifstream midAmplitudesLeftFile("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/midBandAmplitudes_left.txt");
    std::ifstream midAmplitudesRightFile("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/midBandAmplitudes_right.txt");
    std::ifstream highAmplitudesLeftFile("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/highBandAmplitudes_left.txt");
    std::ifstream highAmplitudesRightFile("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/highBandAmplitudes_right.txt");
    //if (!file_amps)
     //   file_test = 666;
    int n = 0; 
    if (subAmplitudesLeftFile.is_open())
    {
        while (subAmplitudesLeftFile >> amplitudes[n][0][0])
        {
            n++;
        }
        subAmplitudesLeftFile.close();
    }
    n = 0;
    if (subAmplitudesRightFile.is_open())
    {
        while (subAmplitudesRightFile >> amplitudes[n][0][1])
        {
            n++;
        }
        subAmplitudesRightFile.close();
    }
    n = 0;
    if (lowAmplitudesLeftFile.is_open())
    {
        while (lowAmplitudesLeftFile >> amplitudes[n][1][0])
        {
            n++;
        }
        lowAmplitudesLeftFile.close();
    }
    n = 0;
    if (lowAmplitudesRightFile.is_open())
    {
        while (lowAmplitudesRightFile >> amplitudes[n][1][1])
        {
            n++;
        }
        lowAmplitudesRightFile.close();
    }
    n = 0;
    if (midAmplitudesLeftFile.is_open())
    {
        while (midAmplitudesLeftFile >> amplitudes[n][2][0])
        {
            n++;
        }
        midAmplitudesLeftFile.close();
    }
    n = 0;
    if (midAmplitudesRightFile.is_open())
    {
        while (midAmplitudesRightFile >> amplitudes[n][2][1])
        {
            n++;
        }
        midAmplitudesRightFile.close();
    }
    n = 0;
    if (highAmplitudesLeftFile.is_open())
    {
        while (highAmplitudesLeftFile >> amplitudes[n][3][0])
        {
            n++;
        }
        highAmplitudesLeftFile.close();
    }
    n = 0;
    if (highAmplitudesRightFile.is_open())
    {
        while (highAmplitudesRightFile >> amplitudes[n][3][1])
        {
            n++;
        }
        highAmplitudesRightFile.close();
    }
}