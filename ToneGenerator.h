#ifndef TONEGENERATOR_H
#define TONEGENERATOR_H

#include <forward_list>
#include "Wav.h"
#include "Tone.h"

class ToneGenerator
{
	std::forward_list<Tone> toneList{};
	int listSize = 0;
	unsigned int encodingLength = 0;

public:
	void makeTone(int frequency, int startTime, short duration);
	void AddToneDataToWav(Wav* targetWav);
	void clearToneGenerator();

private:
	unsigned char* generateToneData(unsigned int _byteRate, int dataType);
	void updateEncodingLength(Tone* toneRecieved, unsigned int _byteRate);
};

#endif