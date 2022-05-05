#include "DelayLine.h"

DelayLineClass::DelayLineClass()
{
	setDelayLength(20, 0);
	setDelayLength(20, 1);
	clearDelayLine();
}

void DelayLineClass::setDelayLength(int delay, int channel)
{
	delayLength[channel] = delay;
	readIndex[channel] = writeIndex[channel] - delayLength[channel];
	if (readIndex[channel] < 0)
		readIndex[channel] += BUFFER_LENGTH;
}

float linearInterpolate(float lowerBound, float upperBound, float fraction)
{
	int intFraction = fraction;
	float frac = fraction - intFraction;
	return ((1 - frac) * lowerBound) + (frac * upperBound);
}

void DelayLineClass::writeToBuffer(float sample, int channel)
{
	circBuffer[writeIndex[channel]][channel] = sample;
	writeIndex[channel]++;
	if (writeIndex[channel] == BUFFER_LENGTH)
		writeIndex[channel] = 0;
}

float DelayLineClass::readFromBuffer(int channel)
{
	float delayedSample = circBuffer[readIndex[channel]][channel];
	readIndex[channel]++;
	if (readIndex[channel] == BUFFER_LENGTH)
		readIndex[channel] = 0;
	return delayedSample;
}

float DelayLineClass::delayProcess(float sample, int channel)
{
	writeToBuffer(sample, channel);
	return readFromBuffer(channel);
}

void DelayLineClass::clearDelayLine()
{
	for (int ch = 0; ch < 2; ch++)
	{
		for (int i = 0; i < BUFFER_LENGTH; i++)
		{
			circBuffer[i][ch] = 0.0f;
		}
	}
}