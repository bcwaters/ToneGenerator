#ifndef WAVLOADER_H
#define WAVLOADER_H
#include <fstream>
#include "Wav.h"

class WavLoader
{
	std::istream::streampos size;
	char * wavInMemory;
	unsigned char* convertedHeaderData;
	bool fileOpened = false;
	RiffChunk* riff;
	FormatChunk* fmt;
	DataChunk *data;

public:
	Wav* loadWav( char* fileName);
	char* getBits();
	unsigned int getTestInfo();
private:
	void openFile(char* fileName);
	void loadRiffChunk();
	void loadFmtChunk();
	void loadDataChunk();

};

#endif