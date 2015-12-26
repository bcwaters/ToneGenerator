#ifndef WAV_H
#define WAV_H
#include "FormatChunk.h"
#include "DataChunk.h"
#include "RiffChunk.h"

class Wav
{
	
	RiffChunk* riff;
	FormatChunk* fmt;
	DataChunk* data;

public:
	Wav();
	~Wav();
	Wav(RiffChunk* _riff, FormatChunk* _fmt, DataChunk* _data);
	//MAIN RIFF CHUNK
	unsigned int getRiffId();
	unsigned int getChunkSize();
	unsigned int getRiffFormat();
	//FMT CHUNK
	unsigned int getFmt();
	unsigned int getFmtLength();
	unsigned short getFmtType();
	unsigned short getNumberOfChannels();
	unsigned int getSampleRate();
	unsigned int getByteRate();
	unsigned short getBlockAlign();
	unsigned short getBitsPerSample();
	//DATA CHUNK
	unsigned int getDataId();
	unsigned int getDataSize();
	void setDataSize(unsigned int newSize);
	short getDataBlock(int index);
	unsigned char getReadDataBlock(int index);
	void setDataBlock(short* newData);
};
#endif