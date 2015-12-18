#ifndef WAV_H
#define WAV_H
#include "FormatChunk.h"
#include "DataChunk.h"

class Wav
{
	unsigned int riffId;			//"RIFF"
	unsigned int chunkSize;			//fileLength - 8
	unsigned int riffFormat;		//"WAVE"

	FormatChunk* fmt;
	DataChunk* data;

public:
	Wav();
	~Wav();
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
	short getDataBlock(int index);
	void setDataBlock(short* newData);
	
	

};
#endif