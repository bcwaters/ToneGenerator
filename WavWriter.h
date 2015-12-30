#ifndef WAVWRITER_H
#define WAVWRITER_H
#include <fstream>
#include "Wav.h"


class WavWriter
{
	std::ofstream testFile;

public:
	void writeData(Wav* _wavToWrite);
	void writeInt(unsigned int input);
	void writeShortData(Wav* _wavToWrite);
	void writeUnsignedCharData(Wav* _wavToWrite);
	void writeWav(Wav * waveToWrite, int tempCode);
	void writeShort(short  input);
	void writeUnsignedChar(unsigned char  input);
};

#endif