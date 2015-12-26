#ifndef WAVWRITER_H
#define WAVWRITER_H
#include <fstream>
#include "Wav.h"


class WavWriter
{
	std::ofstream testFile;

public:
	void writeInt(unsigned int input);
	void writeShort(short input);
	void writeUnsignedChar(unsigned char  input);
	void writeWav(Wav * waveToWrite, int tempCode);
};

#endif